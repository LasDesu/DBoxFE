#/*
#*   Copyright (C) 2004 - 2009 by Alexander Saal <alex.saal@gmx.de>
#*
#*   This program is free software; you can redistribute it and/or modify
#*   it under the terms of the GNU General Public License as published by
#*   the Free Software Foundation; either version 3 of the License, or (at
#*   your option) any later version.
#*
#*   This program is distributed in the hope that it will be useful, but
#*   WITHOUT ANY WARRANTY; without even the implied warranty of
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#*   GNU General Public License for more details.
#*
#*   You should have received a copy of the GNU General Public License
#*   along with this program; if not, write to the Free Software Foundation,
#*   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#*
#*   --------------------------------------------------------------------------
#*   The files in this project include file comes from the follow project:
#*   OSDaB Project (http://osdab.42cows.org)
#*   --------------------------------------------------------------------------
#*/

DEPENDPATH += $$PWD
DEPENDPATH += $$PWD/Zip

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Zip

SOURCES += $$PWD/base64.cpp
HEADERS += $$PWD/base64.h

SOURCES += $$PWD/md5hash.cpp
HEADERS += $$PWD/md5hash.h

SOURCES += $$PWD/unzip.cpp
HEADERS += $$PWD/unzip.h
HEADERS += $$PWD/unzip_p.h

SOURCES += $$PWD/xmlpreferences.cpp
HEADERS += $$PWD/xmlpreferences.h
HEADERS += $$PWD/xmlpreferences_p.h

SOURCES += $$PWD/xmlwriter.cpp
HEADERS += $$PWD/xmlwriter.h
HEADERS += $$PWD/xmlwriter_p.h

SOURCES += $$PWD/zip.cpp
HEADERS += $$PWD/zipentry_p.h
HEADERS += $$PWD/zip.h
HEADERS += $$PWD/zip_p.h

unix {
  DEPENDPATH += /usr/include/libxml2
  INCLUDEPATH += /usr/include/libxml2

  LIBS += -lxml2 -lz
}

win32 {
  LIBS += -llibxml2 -lzlib
}
