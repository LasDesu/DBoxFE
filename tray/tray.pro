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
#*/

include(tray/tray.pri)
include(../3rdparty/3rdparty.pri)

# Qt 4 Settings
TEMPLATE = app
DESTDIR = ../bin
RESOURCES += resource/tray.qrc
CONFIG += build_all thread warn_on qt
QT += xml

# Config settings
CONFIG(debug, debug|release) {

  TARGET = dboxfetrayd
  RCC_DIR = ../build/dboxfetrayd/rcc
  MOC_DIR += ../build/dboxfetrayd/moc
  OBJECTS_DIR += ../build/dboxfetrayd/obj

} else {

  TARGET = dboxfetray
  RCC_DIR = ../build/dboxfetray/rcc
  MOC_DIR += ../build/dboxfetray/moc
  OBJECTS_DIR += ../build/dboxfetray/obj
  UI_DIR += ../build/dboxfetray/ui

  unix {
    QMAKE_POST_LINK = strip -s ../bin/dboxfetray
  }
}

# Windows settings
win32 {
  CONFIG += embed_manifest_exe
  RC_FILE = resource/tray.rc
  CONFIG -= console
}

# Mac settings
mac {
  QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
  CONFIG += x86 ppc
}
