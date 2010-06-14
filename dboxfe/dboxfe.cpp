/*
 *
 * Copyright (C) 2004 - 2010 Alexander Saal.
 * All rights reserved.
 * Contact: Alexander Saal (alex.saal@gmx.de)
 *
 * This file is part of DBoxFE.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "dboxfe.h"
#include "profilesettings.h"

#include <QEvent>

using namespace asaal;

DBoxFE::DBoxFE( QWidget *parent )
  : QMainWindow(parent),
    mPreference(0)
{

  setupUi(this);

  mStackedWidgetOption->setCurrentIndex(0);

  mPageWelcome->setMainWindow(this);
  mPageProfiles->setMainWindow(this);
}

DBoxFE::~DBoxFE() {

  // at first a empty de-constructor
}

void DBoxFE::slotNewProfile() {
}

void DBoxFE::slotShowProfiles() {

  mStackedWidgetOption->setCurrentIndex(1);
}

void DBoxFE::slotPreferences() {

//  if( !mPreference )
//    mPreference = new Preferences(this);
//
//#if defined(Q_WS_MAC) || defined(Q_WS_MACX) || defined(Q_WS_MAC64)
//  mPreference->setWindowFlags(Qt::Sheet);
//  mPreference->open();
//#else
//  mPreference->exec();
//#endif

  ProfileSettings *settings = new ProfileSettings();
  settings->setVisible(true);
}

void DBoxFE::slotDOSBoxGames() {
}

void DBoxFE::slotDOSBoxDatabaseUpdate() {
}

void DBoxFE::slotGoHome() {

  mStackedWidgetOption->setCurrentIndex(0);
}

void DBoxFE::changeEvent( QEvent *event ) {

  switch( event->type() ) {

    case QEvent::LanguageChange:

      retranslateUi(this);
      break;

    default:
      return;
  }
}
