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

#include "dboxfesettings.h"
#include "dosboxinifile.h"

#include "xmlpreferences.h"

#include <QDir>

using namespace asaal;

static void writeProfiles( const DBoxFEConfiguration *configuration );
static QList<DBoxFEProfile*> readProfiles( const QString &profilePath );

void DBoxFESettings::writeConfiguration( const DBoxFEConfiguration *configuration ) {

  if( configuration ) {
    XmlPreferences &xmlPreference = XmlPreferences::instance();
    bool configLoaded = xmlPreference.load(QString("%1/%2").arg(DBoxFEConfigDirectory).arg(DBoxFEConfigFile));
    if( configLoaded ) {

    }
    else {
      xmlPreference.setProductVersion(DBoxFEProductVersion);
      xmlPreference.setProductInfo(DBoxFEProductCompany, DBoxFEProduct);

      xmlPreference.setString("ProfilePath", configuration->mProfilePath, DBoxFEProduct);
      xmlPreference.setBool("HideWindow", configuration->mHideWindow, DBoxFEProduct);
      xmlPreference.setString("DOSBoxBinary", configuration->mDosboxBinary, DBoxFEProduct);
      xmlPreference.setString("DOSBoxVersion", configuration->mDosboxVersion, DBoxFEProduct);
      xmlPreference.setBool("KeyMapper", configuration->mStartKeyMapper, DBoxFEProduct);
      xmlPreference.setInt("DFendTemplateUpdateInterval", configuration->mDFendUpdateInterval, DBoxFEProduct);
      xmlPreference.setInt("DOSBoxDatabaseUpdateInterval", configuration->mDatabseUpdateInterval, DBoxFEProduct);

      writeProfiles(configuration);

      xmlPreference.save(QString("%1/%2").arg(DBoxFEConfigDirectory).arg(DBoxFEConfigFile));
    }
  }
}

DBoxFEConfiguration *DBoxFESettings::readConfiguration() {

  DBoxFEConfiguration *configuration = new DBoxFEConfiguration;

  XmlPreferences &xmlPreference = XmlPreferences::instance();
  xmlPreference.setProductVersion(DBoxFEProductVersion);
  xmlPreference.setProductInfo(DBoxFEProductCompany, DBoxFEProduct);
  bool configLoaded = xmlPreference.load(QString("%1/%2").arg(DBoxFEConfigDirectory).arg(DBoxFEConfigFile));
  if( configLoaded ) {

    configuration->mProfilePath = xmlPreference.getString("ProfilePath", DBoxFEProduct);
    if( configuration->mProfilePath.isNull() || configuration->mProfilePath.isEmpty() )
      configuration->mProfilePath = QString("%1/%2").arg(QDir::homePath()).arg(DBoxFEConfigDirectory);
    configuration->mHideWindow = xmlPreference.getBool("HideWindow", DBoxFEProduct);

    configuration->mDosboxBinary = xmlPreference.getString("DOSBoxBinary", DBoxFEProduct);
    configuration->mDosboxVersion = xmlPreference.getString("DOSBoxVersion", DBoxFEProduct);
    if( configuration->mDosboxVersion.isNull() || configuration->mDosboxVersion.isEmpty() )
      configuration->mDosboxVersion = QString(DOSBoxVersion);
    configuration->mStartKeyMapper = xmlPreference.getBool("KeyMapper", DBoxFEProduct);
    configuration->mDFendUpdateInterval = xmlPreference.getInt("DFendTemplateUpdateInterval", DBoxFEProduct);
    if(configuration->mDFendUpdateInterval <= 0)
      configuration->mDFendUpdateInterval = 60000;
    configuration->mDatabseUpdateInterval = xmlPreference.getInt("DOSBoxDatabaseUpdateInterval", DBoxFEProduct);
    if(configuration->mDatabseUpdateInterval <= 0)
      configuration->mDatabseUpdateInterval = 60000;

    configuration->mProfiles = readProfiles(configuration->mProfilePath);
  }
  else {

    configuration->mProfilePath = QString("%1/%2").arg(QDir::homePath()).arg(DBoxFEConfigDirectory);
    configuration->mHideWindow = true;
    configuration->mDosboxBinary = QString("");
    configuration->mDosboxVersion = QString(DOSBoxVersion);
    configuration->mStartKeyMapper = false;
    configuration->mDFendUpdateInterval = 60000;
    configuration->mDatabseUpdateInterval = 60000;
  }

  return configuration;
}

void writeProfiles( const DBoxFEConfiguration *configuration ) {

  if( !configuration )
    return;

  if( configuration->mProfiles.isEmpty() || configuration->mProfiles.count() <= 0 )
    return;

  XmlPreferences &xmlPreference = XmlPreferences::instance();
  xmlPreference.setProductVersion(DBoxFEProductVersion);
  xmlPreference.setProductInfo(DBoxFEProductCompany, DBoxFEProduct);

  foreach( const DBoxFEProfile *profile, configuration->mProfiles ) {
    if( profile ) {

      QString dosboxFile = configuration->mProfilePath;
      if( dosboxFile.isEmpty() || dosboxFile.isNull() )
        dosboxFile = QString("%1/%2").arg(QDir::homePath()).arg(DBoxFEConfigDirectory);

      dosboxFile.append(QString("/%1").arg(profile->mFile));
      DOSBoxIniFile::write(QString("/%1").arg(profile->mFile), profile->dosboxConfiguration);
      dosboxFile.clear();

      xmlPreference.setString("File", profile->mFile, profile->mName);
      xmlPreference.setString("ShortDescription", profile->mShortDescription, profile->mName);
      xmlPreference.setString("Genre", profile->mGenre, profile->mName);
      xmlPreference.setBool("IsFavorite", profile->mIsFavorite, profile->mName);

      xmlPreference.save(QString("%1/%2/%3").arg(QDir::homePath()).arg(DBoxFEConfigDirectory).arg(DBoxFEProfileFile));
    }
  }
}

QList<DBoxFEProfile*> readProfiles( const QString &profilePath ) {

  Q_UNUSED(profilePath)
  return QList<DBoxFEProfile*>();
}
