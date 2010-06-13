/*
 *   Copyright (C) 2004 - 2010 by Alexander Saal <alex.saal@gmx.de>
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

#ifndef SEARCH_H
#define SEARCH_H

#include "ui_search.h>"

#include <QWidget>

namespace asaal {

  class Search : public QWidget, private Ui::UiSearchBase {

      Q_OBJECT
      Q_CLASSINFO("Author", "Alexander Saal")
      Q_CLASSINFO("eMail", "alex.saal@gmx.de")
      Q_CLASSINFO("Date", "2010/07/03")

    public:
      Search( QWidget *parentWidget = 0 );
  };
}

#endif // SEARCH_H
