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

include(assistant/assistant.pri)
include(../base/base.pri)
include(../3rdparty/3rdparty.pri)

# Qt 4 Settings
TEMPLATE = app
DESTDIR	= ../bin

RESOURCES += resource/dboxfeassistant.qrc
RESOURCES += ../resource/templates.qrc
CONFIG += debug thread warn_on qt
QT += xml

# Config settings
CONFIG(debug, debug|release) {

  TARGET = dboxfeassistantd
  RCC_DIR = ../build/dboxfeassistantd/rcc
  MOC_DIR += ../build/dboxfeassistantd/moc
  OBJECTS_DIR += ../build/dboxfeassistantd/obj
  UI_DIR += ../build/dboxfeassistantd/ui

} else {

  TARGET = dboxfeassistant
  RCC_DIR = ../build/dboxfeassistant/rcc
  MOC_DIR += ../build/dboxfeassistant/moc
  OBJECTS_DIR += ../build/dboxfeassistant/obj
  UI_DIR += ../build/dboxfeassistant/ui

  unix {
    QMAKE_POST_LINK = strip -s ../bin/dboxfeassistant
  }
}

# Windows settings
win32 {
  CONFIG += embed_manifest_exe
  RC_FILE = resource/dboxfeassistant.rc
  CONFIG -= console
}

# Mac settings
mac {
  QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
  CONFIG += x86 ppc
}
