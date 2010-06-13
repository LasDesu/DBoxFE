/*
 *   Copyright (C) 2010 by Alexander Saal <alex.saal@gmx.de>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or (at
 *   your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software Foundation,
 *   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "global.h"
#include "dosboxupdater.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QUrl>

using namespace asaal;

DOSBoxUpdater::DOSBoxUpdater( QObject *parentObject )
  : QThread(parentObject) {

  mUpdateTimer = new QTimer(this);

  mHttp = new QHttp(this);
  connect(mHttp, SIGNAL(requestFinished(int, bool)), this, SLOT(httpRequestFinished(int, bool)));
  connect(mHttp, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)), this, SLOT(readResponseHeader(const QHttpResponseHeader &)));
  connect(mHttp, SIGNAL(dataReadProgress(int, int)), this, SLOT(readDataReadProgress(int, int)));
  connect(mHttp, SIGNAL(done(bool)), this, SLOT(done(bool)));

  setPriority(QThread::NormalPriority);
}

DOSBoxUpdater::~DOSBoxUpdater() {

  if( mUpdateTimer ) {

    if( mUpdateTimer -> isActive() )
      mUpdateTimer -> stop();

    delete mUpdateTimer;
  }

  if( mHttp ) {

    if( mHttp -> hasPendingRequests() ) {
      mHttp -> clearPendingRequests();
      mHttp -> close();
    }
    mHttp -> abort();

    delete mHttp;
  }

  if( mHttpFile ) {

    if( mHttpFile -> isOpen() ) {
      mHttpFile -> close();
      mHttpFile -> flush();
    }

    delete mHttpFile;
  }
}

void DOSBoxUpdater::checkForUpdates( const int msec ) {

  if( mUpdateTimer -> isActive() )
    mUpdateTimer -> stop();

  mUpdateTimer -> start(msec);
}

void DOSBoxUpdater::run() {

  // Now we wait for finishing the current thread
  while( !isRunning() ) {
    break;
  }

  // disconnect current timer
  disconnect(mUpdateTimer, SIGNAL(timeout()), this, SLOT(checkUpdates()));

  // connect current timer again
  connect(mUpdateTimer, SIGNAL(timeout()), this, SLOT(checkUpdates()));
  mUpdateTimer -> start();
}

void DOSBoxUpdater::checkUpdates() {

  bool isUpdateAvailable = false;
  {
    QUrl url(DOSBoxGameDatabaseUrl);

    QString databaseXml = QDir::homePath();
    databaseXml.append(DBoxFEConfigDirectory);

    QDir dir(databaseXml);
    if( !dir.exists(databaseXml) )
      dir.mkdir(databaseXml);

    databaseXml.clear();

    databaseXml = QDir::homePath();
    databaseXml.append( QString("%1/%2").arg(DBoxFEConfigDirectory).arg(DOSBoxGameDatabaseXml) );

    if( QFile::exists(databaseXml) )
      QFile::remove(databaseXml);

    mHttpFile = new QFile(databaseXml);

    if ( !mHttpFile -> open( QIODevice::WriteOnly ) ) {

      emit errorOccurred(tr("Unable to update the file %1: %2.").arg(databaseXml).arg(mHttpFile -> errorString()));
      databaseXml.clear();
      delete mHttpFile;
      mHttpFile = 0;
      isUpdateAvailable = false;
    }

    if( isUpdateAvailable ) {

      mHttp -> setHost(url.host(), url.port() != -1 ? url.port() : 80);
      if( !url.userName().isEmpty() )
        mHttp -> setUser(url.userName(), url.password());

      httpRequestAborted = false;
      httpGetId = mHttp -> get( url.path(), mHttpFile );
    }

    if( isUpdateAvailable )
      emit updateAvailable(databaseXml);
  }
}

void DOSBoxUpdater::httpRequestFinished( int requestId, bool error ) {

  if( httpRequestAborted ) {

    if( mHttpFile ) {

      mHttpFile -> close();
      mHttpFile -> remove();
      delete mHttpFile;
      mHttpFile = 0;
    }

    return;
  }

  if( requestId != httpGetId )
    return;

  mHttpFile -> flush();
  mHttpFile -> close();

  if( error ) {

    emit errorOccurred(tr("Download failed: %1.").arg(mHttp -> errorString()));
    mHttpFile -> remove();
  }

  delete mHttpFile;
  mHttpFile = 0;
}

void DOSBoxUpdater::readResponseHeader( const QHttpResponseHeader &responseHeader ) {

  if( responseHeader.statusCode() != 200 ) {

    emit errorOccurred(tr("Download failed: %1.").arg(responseHeader.reasonPhrase()));
    httpRequestAborted = true;
    mHttp -> abort();
  }
}

void DOSBoxUpdater::readDataReadProgress( int bytesRead, int totalBytes ) {

  emit progressChanged( totalBytes, bytesRead );
}

void DOSBoxUpdater::done( bool error ) {

  if( error ) {

    emit errorOccurred( tr( "Error: %1." ).arg( mHttp -> errorString() ) );
    return;
  }

  if( mHttpFile ) {

    emit updateAvailable(mHttpFile -> fileName());

    delete mHttpFile;
    mHttpFile = 0;
  }
}
