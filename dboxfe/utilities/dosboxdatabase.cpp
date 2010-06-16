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

#include "dosboxdatabase.h"

#include <QDesktopServices>
#include <QDir>
#include <QDomDocument>
#include <QDomNode>
#include <QFile>
#include <QSqlQuery>

using namespace asaal;

DOSBoxDatabase::DOSBoxDatabase( QObject *parent )
  : QObject(parent),
    m_connectionIsOpen(false) {

  initializeDatabase();
}

void DOSBoxDatabase::updateGames( const QString &gameDatabaseXml ) {

  if( gameDatabaseXml.isEmpty() )
    return;

  if( gameDatabaseXml.isEmpty() || gameDatabaseXml.isNull() ) {
    emit percentage(0);
    emit messageReceived(tr("No xml file was specified!"));
    return;
  }

  QFile file( gameDatabaseXml );

  if( !file.open( QIODevice::ReadOnly ) ) {
    emit percentage(0);
    emit messageReceived(tr("Cannot read XML file %1!").arg(gameDatabaseXml));
    return;
  }

  QDomDocument doc;

  doc.setContent( &file );
  file.close();

  QDomNode item = doc.documentElement().firstChild();
  int childCount = item.childNodes().count();

  int x = 0;

  while( !item.isNull() ) {

    if( item.isElement() && item.nodeName() == "game" ) {

      DOSBoxGame *dosboxGame = new DOSBoxGame;
      {
        QDomNode subitem = item.toElement().firstChild();
        while( !subitem.isNull() ) {

          if( subitem.toElement().tagName() == "title" )
            dosboxGame -> mTitle = subitem.toElement().text();

          else if( subitem.toElement().tagName() == "year" )
            dosboxGame -> mYear = subitem.toElement().text();

          else if( subitem.toElement().tagName() == "sw_house" )
            dosboxGame -> mSoftwareHouse = subitem.toElement().text();

          else if( subitem.toElement().tagName() == "link" )
            dosboxGame -> mLink = subitem.toElement().text();

          else if( subitem.toElement().tagName() == "dosbox" )	{

            QDomNode attrib = subitem.toElement().firstChild();
            DOSBoxInfo *dosboxInfo = 0;

            while( !attrib.isNull() ) 	{

              if( attrib.toElement().tagName() == "info" )	{

                dosboxInfo = new DOSBoxInfo;
                {
                  dosboxInfo -> mVersion = attrib.toElement().attribute( "version" );
                  dosboxInfo -> mCompPercent = attrib.toElement().attribute( "comp_percent" ).toInt();
                }
                dosboxGame -> mInfo.append(dosboxInfo);
              }
              attrib = attrib.nextSibling();
            }
          }
          subitem = subitem.nextSibling();
        }
      }
      insertGame(dosboxGame);

      x++;
      emit percentage(double(x*childCount)/100.0);
      emit messageReceived(tr("Import game %1").arg(dosboxGame -> mTitle));
    }
    item = item.nextSibling();
  }
}

DOSBoxGame *DOSBoxDatabase::dosboxGame( const QString &gameName ) {

  if( gameName.isEmpty() )
   return 0;

  DOSBoxGame *dosboxGame = 0;

  return dosboxGame;
}

bool DOSBoxDatabase::openConnection() {

  if( m_dosboxDatabase.isOpen() )
    return true;

  QString databaseName = QDir::homePath();
  databaseName.append(QString(DBoxFEConfigDirectory) + "/" + QString(DOSBoxGameDatabaseFile));

  m_dosboxDatabase = QSqlDatabase::addDatabase("QSQLITE");
  m_dosboxDatabase.setDatabaseName(databaseName);
  m_connectionIsOpen = m_dosboxDatabase.open();

  return m_connectionIsOpen;
}

bool DOSBoxDatabase::closeConnection() {

  if( m_dosboxDatabase.isOpen() ) {

    m_dosboxDatabase.close();
    m_connectionIsOpen = true;
  }
  return m_connectionIsOpen;
}

void DOSBoxDatabase::insertGame( const DOSBoxGame *dosboxGame ) {

  if( dosboxGame ) {
    if( m_connectionIsOpen ) {

    }
  }
}

void DOSBoxDatabase::initializeDatabase() {

  if( !m_dosboxDatabase.isOpen() )
    m_connectionIsOpen = openConnection();

  if( m_connectionIsOpen ) {

    QSqlQuery sqlQuery = QSqlQuery(m_dosboxDatabase);
    bool queryOk;
    m_dosboxDatabase.transaction();

    queryOk = sqlQuery.exec("create table if not exists `dosbox` ("
                            "`id` INT NOTNULL AUTOINCREMENT, "
                            "`url` NVARCHAR(45) NOTNULL, "
                            "`version` NVARCHAR(45) NOTNULL, "
                            "PRIMARY KEY (`id`), "
                            "UNIQUE INDEX `id_UNIQUE` (`id` ASC)"
                            ")"
                            );

    queryOk &= sqlQuery.exec("CREATE  TABLE IF NOT EXISTS `dosboxrl` ("
                             "  `gamesId` INT NOTNULL ,"
                             "  `dosboxId` INT NOTNULL ,"
                             "  PRIMARY KEY (`dosboxId`, `gamesId`) ,"
                             "  INDEX `fk_dosbox_dosbxId` (`dosboxId` ASC) ,"
                             "  INDEX `fk_dosbox_gamesId` (`gamesId` ASC) ,"
                             "  CONSTRAINT `fk_dosbox_dosbxId`"
                             "    FOREIGN KEY (`dosboxId`)"
                             "    REFERENCES `dosbox` (`id`)"
                             "    ON DELETE NO ACTION"
                             "    ON UPDATE NO ACTION,"
                             "  CONSTRAINT `fk_dosbox_gamesId`"
                             "    FOREIGN KEY (`gamesId`)"
                             "    REFERENCES `games` (`id`)"
                             "    ON DELETE NO ACTION"
                             "    ON UPDATE NO ACTION)"
                             );

    queryOk &= sqlQuery.exec("CREATE  TABLE IF NOT EXISTS `games` ("
                             "  `id` INT NOTNULL AUTOINCREMENT ,"
                             " `title` NVARCHAR(45) NOTNULL ,"
                             "  `year` NVARCHAR(45) NOTNULL ,"
                             "  `swhouse` NVARCHAR(45) NOTNULL ,"
                             "  `link` NVARCHAR(45) NOTNULL ,"
                             "  PRIMARY KEY (`id`) ,"
                             "  UNIQUE INDEX `id_UNIQUE` (`id` ASC) )"
                             );
    if( queryOk )
      m_dosboxDatabase.commit();
    else
      m_dosboxDatabase.rollback();

    sqlQuery.clear();
  }
}




