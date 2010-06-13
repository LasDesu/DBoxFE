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

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "ui_preferences.h"

#include <QDialog>

namespace asaal {

  class Preferences : public QDialog, private Ui::UiPreferenceBase {

      Q_OBJECT
      Q_CLASSINFO("Author", "Alexander Saal")
      Q_CLASSINFO("eMail", "alex.saal@gmx.de")
      Q_CLASSINFO("Date", "2010/07/03")

    public:
      Preferences( QWidget *parent = 0 );

    private slots:
      void slotReset();
      void slotCancel();
      void slotSave();

      void slotSwitchSettings();

    private:
      void defaultSettings();

    protected:
      void changeEvent( QEvent *event );


  };
}

#endif // PREFERENCES_H
