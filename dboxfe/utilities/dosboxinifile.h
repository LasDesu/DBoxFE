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

#ifndef INIFILE_H
#define INIFILE_H

#include "global.h"

#include <QObject>
#include <QSettings>

namespace asaal {

  class DOSBoxIniFile {

      Q_CLASSINFO("Author", "Alexander Saal")
      Q_CLASSINFO("eMail", "alex.saal@gmx.de")
      Q_CLASSINFO("Date", "2010/08/03")

    public:
      static DOSBoxConfiguration *read( const QString &file );
      static DOSBoxConfiguration *defaultConfiguration();
      static void write( const QString &file, const DOSBoxConfiguration *config );

    private:

      static void write( const DOSBoxConfiguration *config );
      static DOSBoxConfiguration* read();
      static SdlSection *sdlSection( QSettings &settings, bool defaultSettings );
      static DosboxSection *dosboxSection( QSettings &settings, bool defaultSettings );
      static RenderSection *renderSection( QSettings &settings, bool defaultSettings );
      static CpuSection *cpuSection( QSettings &settings, bool defaultSettings );
      static MixerSection *mixerSection( QSettings &settings, bool defaultSettings );
      static MdiSection *mdiSection( QSettings &settings, bool defaultSettings );
      static SBlasterSection *sblasterSection( QSettings &settings, bool defaultSettings );
      static GusSection *gusSection( QSettings &setting, bool defaultSettings );
      static SpeakerSection *speakerSection( QSettings &settings, bool defaultSettings );
      static JoystickSection *joystickSection( QSettings &settings, bool defaultSettings );
      static SerialSection *serialSection( QSettings &settings, bool defaultSettings );
      static DosSection *dosSection( QSettings &settings, bool defaultSettings );
      static IpxSection *ipxSection( QSettings &settings, bool defaultSettings );
      static QStringList autoexecSection( bool defaultSettings );
  };
}

#endif // INIFILE_H
