#/*
# *   Copyright (C) 2004 - 2010 by Alexander Saal <alex.saal@gmx.de>
# *
# *   This program is free software; you can redistribute it and/or modify
# *   it under the terms of the GNU General Public License as published by
# *   the Free Software Foundation; either version 3 of the License, or (at
# *   your option) any later version.
# *
# *   This program is distributed in the hope that it will be useful, but
# *   WITHOUT ANY WARRANTY; without even the implied warranty of
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *   GNU General Public License for more details.
# *
# *   You should have received a copy of the GNU General Public License
# *   along with this program; if not, write to the Free Software Foundation,
# *   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# */

#ifndef DFENDTEMPLATE_H
#define DFENDTEMPLATE_H

#include "global.h"

#include <QObject>

namespace asaal {

  class DFendTemplate {

      Q_CLASSINFO("Author", "Alexander Saal")
      Q_CLASSINFO("eMail", "alex.saal@gmx.de")
      Q_CLASSINFO("Date", "2010/20/03")

    public:
      static DOSBoxConfiguration *read( const QString &profileName );

    private:
      static QString dfendTemplateFile( const QString &profileName );
  };
}

#endif // DFENDTEMPLATE_H
