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

#ifndef DOSBOXUPDATER_H
#define DOSBOXUPDATER_H

#include <QHttp>
#include <QThread>

class QDateTime;
class QFile;
class QTimer;

namespace asaal {

  class DOSBoxUpdater : public QThread {

      Q_OBJECT

    public:
      DOSBoxUpdater( QObject *parentObject = 0 );
      ~DOSBoxUpdater();

      void checkForUpdates( const int msec = 60000 );

    signals:
      void updateAvailable( const QString &databaseFile );
      void progressChanged( int total, int value );
      void errorOccurred( const QString &error );

    protected:
      void run();

    private:
      QHttp *mHttp;
      QFile *mHttpFile;

      int httpGetId;
      bool httpRequestAborted;

      QTimer *mUpdateTimer;


    private slots:
      void checkUpdates();

      void httpRequestFinished( int requestId, bool error );
      void readResponseHeader( const QHttpResponseHeader &responseHeader );
      void readDataReadProgress( int bytesRead, int totalBytes );
      void done( bool error );

  };
}

#endif // DOSBOXUPDATER_H
