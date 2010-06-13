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

#include "dosboxinifile.h"
#include "profilesettings.h"

using namespace asaal;

ProfileSettings::ProfileSettings( QWidget *parent )
  : QWidget(parent) {

  setupUi(this);
}

void ProfileSettings::setProfile( const QString &profileName, const QString &profileFile ) {

  mProfileName.clear();
  mProfileName = profileName;

  mProfileFile.clear();
  mProfileFile = profileFile;

  initializeSettings();

  QString mWindowTitle = windowTitle();
  mWindowTitle = mWindowTitle.append(" [%1]").arg(mProfileName);
  setWindowTitle(mWindowTitle);
  mWindowTitle.clear();
}

void ProfileSettings::slotReset() {
}

void ProfileSettings::slotSave() {
}

void ProfileSettings::slotAbort() {
}

void ProfileSettings::initializeSettings() {

  DOSBoxConfiguration *dosboxConfig = 0;
  if( mProfileFile.isEmpty() ) {

    dosboxConfig = DOSBoxIniFile::defaultConfiguration();
  }
  else {

    dosboxConfig = DOSBoxIniFile::read(mProfileFile);
  }

  if( !dosboxConfig ) {
    // Now we set the configuration
  }

  if( dosboxConfig )
    delete dosboxConfig;
  dosboxConfig = 0;
}
