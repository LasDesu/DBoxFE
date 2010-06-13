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

#include "dfendtemplate.h"
#include "dosboxinifile.h"

#include <QDir>
#include <QDomDocument>
#include <QDomNode>
#include <QFile>
#include <QSettings>

using namespace asaal;

DOSBoxConfiguration *DFendTemplate::read( const QString &profileName ) {

  if( profileName.isEmpty() )
    return DOSBoxIniFile::defaultConfiguration();

  QString dfendReloadedProfile = dfendTemplateFile(profileName);
  DOSBoxConfiguration *dosboxConfig = DOSBoxIniFile::read(dfendReloadedProfile);

  return dosboxConfig;
}

QString DFendTemplate::dfendTemplateFile( const QString &profileName ) {

  if( profileName.isEmpty() )
    return QString();

  QFile file(":/misc/dfend_reloaded_profiles");

  if( !file.open(QIODevice::ReadOnly) )
    return QString();

  QDomDocument doc;
  doc.setContent(&file);

  file.close();

  QString templateFile = QDir::homePath();

  QDomNode item = doc.documentElement().firstChild();
  while( !item.isNull() ) {

    if( item.isElement() && item.nodeName() == "profiles" ) {

      QDomNode subitem = item.toElement().firstChild();
      while( !subitem.isNull() ) {

        if( subitem.toElement().tagName() == "profile" ) {

          QString pName = subitem.toElement().attribute( "name" );
          QString searchName = QString(profileName);
          if( pName.toLower() == searchName.toLower() ) {
            pName = "";
            pName.clear();
            searchName = "";
            searchName.clear();

            templateFile.append(DBoxFEConfigDirectory);
            templateFile = templateFile + "/" + subitem.toElement().attribute("file");
            break;
          }
        }
        subitem = subitem.nextSibling();
      }
    }
    item = item.nextSibling();
  }

  return templateFile;
}



