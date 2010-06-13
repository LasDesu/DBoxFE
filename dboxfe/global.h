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

#ifndef DBOXFE_GLOBAL_H
#define DBOXFE_GLOBAL_H

#include <QPixmap>
#include <QList>
#include <QString>

/* DFend Reloaded Templates */
#define DFendReloadedTemplateFile "template.xml"

/* DOSBox defines */
#define DOSBoxVersion "0.74"
#define DOSBoxUrl "http://www.dosbox.com"
#define DOSBoxGameDatabaseUrl "http://www.dosbox.com/game_database.xml"
#define DOSBoxGameDatabaseXml "game_database.xml"
#define DOSBoxGameDatabaseFile "dosbox.sdb3"

/* DBoxFE defines */
#define DBoxFEProduct "DBoxFE"
#define DBoxFEProductVersion 2
#define DBoxFEProductCompany "Alexander Saal"
#define DBoxFEVersion "0.9.74"
#define DBoxFEConfigFile "dboxfe.xml"
#define DBoxFEProfileFile "profiles.xml"

#if defined(Q_OS_WIN) || defined(Q_OS_WIN32)
  #undef DBoxFEConfigDirectory
  #define DBoxFEConfigDirectory "/.dboxfe"
#elif defined(Q_WS_MAC) || defined(Q_OS_MAC) || defined(Q_WS_MAC64) || defined(Q_WS_MACX) || defined(Q_OS_MACX)
  #undef DBoxFEConfigDirectory
  #define DBoxFEConfigDirectory "/Library/Application Support/DBoxFE"
#elif defined(Q_OS_UNIX)
  #undef DBoxFEConfigDirectory
  #define DBoxFEConfigDirectory "/.dboxfe"
#endif

namespace asaal {

  struct DOSBoxInfo {

    QString mVersion;
    int mCompPercent;
  };

  struct DOSBoxGame {

    QString mTitle;
    QString mYear;
    QString mSoftwareHouse;
    QString mLink;
    QList< DOSBoxInfo* > mInfo;
  };

  struct SdlSection {

    bool mFullScreen;
    bool mFullDouble;
    QString mFullResolution;
    QString mWindowResolution;
    QString mOutput;
    bool mAutolock;
    int mSensitivity;
    bool mWaitOnError;
    QString mPriority;
    QString mMapperFile;
    bool mUseScanCodes;
  };

  struct DosboxSection {

    QString mLanguage;
    QString mMachine;
    QString mCaptures;
    int mMemsize;
  };

  struct RenderSection {

    int mFrameSkip;
    bool mAspect;
    QString mScaler;
  };

  struct CpuSection {

    QString mCore;
    QString mCpuType;
    QString mCycles;
    int mCycleUp;
    int mCycleDown;
  };

  struct MixerSection {

    bool mNosound;
    int mRate;
    int mBlockSize;
    int mPreBuffer;
  };

  struct MdiSection {

    QString mMpu401;
    QString mMidiDevice;
    QString mMidiConfig;
  };

  struct SBlasterSection {

    QString mSBType;
    int mSBBase;
    int mIrq;
    int mDma;
    int mHdma;
    bool mSBMixer;
    QString mOplMode;
    QString mOplEmu;
    int mOplRate;
  };

  struct GusSection {

    bool mGus;
    int mGusRate;
    int mGusBase;
    int mGusIrq;
    int mGusDma;
    QString mUltraDir;
  };

  struct SpeakerSection {

    bool mPcSpeaker;
    int mPcRate;
    QString mTandy;
    int mTandyRate;
    bool mDisney;
  };

  struct JoystickSection {

    QString mJoystickType;
    bool mTimed;
    bool mAutoFire;
    bool mSwap34;
    bool mButtonwrap;
  };

  struct SerialSection {

    QString mSerial1;
    QString mSerial2;
    QString mSerial3;
    QString mSerial4;
  };

  struct DosSection {

    bool mXms;
    bool mEms;
    bool mUmb;
    QString mKeyboardLayout;
  };

  struct IpxSection {

    bool mIpx;
  };

  struct DOSBoxConfiguration {

    SdlSection *sdl;
    DosboxSection *dosbox;
    RenderSection *render;
    CpuSection *cpu;
    MixerSection *mixer;
    MdiSection *mdi;
    SBlasterSection *soundBlaster;
    GusSection *gus;
    SpeakerSection *speaker;
    JoystickSection *joystick;
    SerialSection *serial;
    DosSection *dos;
    IpxSection *ipx;
    QStringList autoexec;
  };

  struct DBoxFEProfile {

    QString mName;
    QString mShortDescription;
    QString mGenre;
    bool mIsFavorite;
    QString mFile;
    QPixmap *mIcon;
    QPixmap *mScreenshot;
    DOSBoxConfiguration *dosboxConfiguration;
  };

  struct DBoxFEConfiguration {

    QString mProfilePath;
    QList<DBoxFEProfile*> mProfiles;
    bool mHideWindow;

    QString mDosboxBinary;
    QString mDosboxVersion;
    bool mStartKeyMapper;
    int mDatabseUpdateInterval;
    int mDFendUpdateInterval;
  };
}

#endif // DBOXFE_GLOBAL_H
