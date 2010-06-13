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

#ifndef DATABASE_H
#define DATABASE_H

#include "global.h"

#include <QObject>
#include <QSqlDatabase>


namespace asaal {

  class DOSBoxDatabase : public QObject {

      Q_OBJECT

      Q_CLASSINFO("Author", "Alexander Saal")
      Q_CLASSINFO("eMail", "alex.saal@gmx.de")
      Q_CLASSINFO("Date", "2010/08/03")

    public:
      DOSBoxDatabase( QObject *parent = 0 );

      bool openConnection();
      bool closeConnection();

      void updateGames( const QString &gameDatabaseXml );
      DOSBoxGame *dosboxGame( const QString &gameName );

    signals:
      void percentage( double percent );
      void messageReceived( const QString &message );

    protected:

    private:
      bool m_connectionIsOpen;
      QSqlDatabase m_dosboxDatabase;

      void insertGame( const DOSBoxGame *dosboxGame );
      void initializeDatabase();
  };
}

#endif // DATABASE_H
