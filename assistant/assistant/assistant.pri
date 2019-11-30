#/*
#*   Copyright (C) 2008-2009 by Alexander Saal <alex.saal@gmx.de>
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
#*/

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(finishpage/finishpage.pri)
include(graphicpage/graphicpage.pri)
include(importexportpage/importexportpage.pri)
include(installpage/installpage.pri)
include(installprocesspage/installprocesspage.pri)
include(miscpage/miscpage.pri)
include(settingpage/settingpage.pri)
include(soundpage/soundpage.pri)
include(welcomepage/welcomepage.pri)

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/gamewizard.cpp
HEADERS += $$PWD/gamewizard.h
