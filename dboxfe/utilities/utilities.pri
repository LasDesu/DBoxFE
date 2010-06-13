#/*
# *
# * Copyright (C) 2004 - 2010 Alexander Saal. All rights reserved.
# * Contact: Alexander Saal (alex.saal@gmx.de)
# *
# * This file is part of the DBoxFE.
# *
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or (at
# * your option) any later version.
# *
# * This program is distributed in the hope that it will be useful, but
# * WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program; if not, write to the Free Software Foundation,
# * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# *
# */

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += dfendtemplate.h
SOURCES += dfendtemplate.cpp

HEADERS += dosboxdatabase.h
SOURCES += dosboxdatabase.cpp

HEADERS += dosboxinifile.h
SOURCES += dosboxinifile.cpp

HEADERS += dosboxupdater.h
SOURCES += dosboxupdater.cpp

HEADERS += dboxfesettings.h
SOURCES += dboxfesettings.cpp

#/*
# *   Copyright (C) 2009 Morgan Leborgne. All rights reserved.
# *
# *   The QProgressIndicator class lets an application display a
# *   progress indicator to show that a lengthy task is under way.
# *   Will work at any size.
# *
# *   This program is free software; you can redistribute it and/or modify
# *   it under the terms of the GNU Lesser General Public License as published by
# *   the Free Software Foundation; either version 3 of the License, or (at
# *   your option) any later version.
# *
# *   This program is distributed in the hope that it will be useful, but
# *   WITHOUT ANY WARRANTY; without even the implied warranty of
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *   GNU Lesser General Public License for more details.
# */

INCLUDEPATH += $$PWD/QProgressIndicator
DEPENDPATH += $$PWD/QProgressIndicator
HEADERS += QProgressIndicator.h
SOURCES += QProgressIndicator.cpp

# /****************************************************************************
# ** xmlwriter / xmlpreferences
# ** Last updated [dd/mm/yyyy]: 28/01/2007
# **
# ** Class for XML file generation.
# **
# ** Copyright (C) 2007 Angius Fabrizio. All rights reserved.
# **
# ** The following files are part of the OSDaB project (http://osdab.sourceforge.net/).
# **
# ** This file may be distributed and/or modified under the terms of the
# ** GNU General Public License version 2 as published by the Free Software
# ** Foundation and appearing in the file LICENSE.GPL included in the
# ** packaging of this file.
# **
# ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
# **
# ** See the file LICENSE.GPL that came with this software distribution or
# ** visit http://www.gnu.org/copyleft/gpl.html for GPL licensing information.
# **
# **********************************************************************/

INCLUDEPATH += $$PWD/XmlWriter
DEPENDPATH += $$PWD/XmlWriter
SOURCES += xmlwriter.cpp
HEADERS += xmlwriter_p.h
HEADERS += xmlwriter.h

INCLUDEPATH += $$PWD/XmlPreferences
DEPENDPATH += $$PWD/XmlPreferences
SOURCES += xmlpreferences.cpp
HEADERS += xmlpreferences_p.h
HEADERS += xmlpreferences.h

INCLUDEPATH += $$PWD/Base64
DEPENDPATH += $$PWD/Base64
SOURCES += base64.cpp
HEADERS += base64.h

# Needs from files above this line
unix {
  DEPENDPATH += /usr/include/libxml2
  INCLUDEPATH += /usr/include/libxml2

  LIBS += -lxml2
}

win32 {
  LIBS += -llibxml2
}
