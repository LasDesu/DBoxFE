#/*
#*   Copyright (C) 2004 - 2010 by Alexander Saal <alex.saal@gmx.de>
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

TEMPLATE = subdirs

sub_dboxfe.subdir = dboxfe
sub_dboxfe.depends =
SUBDIRS += sub_dboxfe

sub_tray.subdir = tray
sub_tray.depends = sub_dboxfe
SUBDIRS += sub_tray

sub_assistant.subdir = assistant
sub_assistant.depends = sub_dboxfe
SUBDIRS += sub_assistant
