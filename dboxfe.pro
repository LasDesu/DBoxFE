#***************************************************************************
#*   Copyright (C) 2006 by Alexander Saal                                  *
#*   alex.saal@gmx.de                                                      *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU General Public License as published by  *
#*   the Free Software Foundation; either version 2 of the License, or     *
#*   (at your option) any later version.                                   *
#*                                                                         *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU General Public License for more details.                          *
#*                                                                         *
#*   You should have received a copy of the GNU General Public License     *
#*   along with this program; if not, write to the                         *
#*   Free Software Foundation, Inc.,                                       *
#*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
#***************************************************************************

TEMPLATE = app
TARGET = bin/dboxfe
CONFIG += debug thread warn_on qt
QT += xml

DEPENDPATH += include res src ui 3rdparty
INCLUDEPATH += include 3rdparty
TRANSLATIONS = lng/dboxfe_de.ts

HEADERS += include/dboxfe.h \
           include/dboxfe_profile.h \
	   include/dboxfe_base.h \
	   include/dboxfe_splash.h \
           3rdparty/Base64.h \
           3rdparty/XMLWriter.h \
           3rdparty/XMLPreferences.h
	   
FORMS += ui/dboxfe.ui \
         ui/profile.ui \
	 ui/changelog.ui
	 
SOURCES += src/dboxfe.cpp \
           src/dboxfe_profile.cpp \
	   src/dboxfe_base.cpp \
	   src/dboxfe_splash.cpp \
	   src/main.cpp \
	   3rdparty/Base64.cpp \
	   3rdparty/XMLPreferences.cpp \
	   3rdparty/XMLWriter.cpp

RESOURCES += res/dboxfe.qrc

unix{
RCC_DIR = .unix/rcc
MOC_DIR += .unix/moc
OBJECTS_DIR += .unix/obj
UI_DIR += .unix/ui
}

win32{
RCC_DIR = win/rcc
MOC_DIR += win/moc
OBJECTS_DIR += win/obj
UI_DIR += win/ui
}
