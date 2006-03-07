/***************************************************************************
 *   Copyright (C) 2006 by Alexander Saal                                  *
 *   alex.saal@gmx.de                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "dboxfe.h"
#include "dboxfe_profile.h"
#include "dboxfe_base.h"
#include "XMLPreferences.h"

// QtGui Header
#include <QtGui/QFileDialog>
#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QDesktopWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QFileDialog>
#include <QtGui/QCursor>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QMenu>
#include <QtGui/QIcon>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>

// QtCore Header
#include <QtCore/QProcess>
#include <QtCore/QStringList>
#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QRect>
#include <QtCore/QIODevice>
#include <QtCore/QtDebug>


DBoxFE::DBoxFE(QWidget *parent, Qt::WFlags flags)
        : QWidget(parent, flags)
{

    ui.setupUi(this);

    // connection
    connect( ui.btnSaveGP, SIGNAL( clicked() ), this, SLOT( slotSaveGP() ) );
    connect( ui.btnRemoveGP, SIGNAL( clicked() ), this, SLOT( slotRemoveGP() ) );
    connect( ui.btnCreateGP, SIGNAL( clicked() ), this, SLOT( slotCreateGP() ) );
    connect( ui.btnStartDBox, SIGNAL( clicked() ), this, SLOT( slotStartDBox() ) );

    connect( ui.btnSnapDir, SIGNAL( clicked() ), this, SLOT( slotSnapDir() ) );
    connect( ui.btnLanguage, SIGNAL( clicked() ), this, SLOT( slotLanguage() ) );
    connect( ui.btnDbxStable, SIGNAL( clicked() ), this, SLOT( slotDbxStable() ) );
    connect( ui.btnDbxCvs, SIGNAL( clicked() ), this, SLOT( slotDbxCvs() ) );

    connect( ui.btnAutexecAdd, SIGNAL( clicked() ), this, SLOT( slotAutexecAdd() ) );
    connect( ui.btnAutexecRemove, SIGNAL( clicked() ), this, SLOT( slotAutexecRemove() ) );
    connect( ui.btnAutexecUpdate, SIGNAL( clicked() ), this, SLOT( slotAutexecUpdate() ) );
    connect( ui.btnAutexecDrive, SIGNAL( clicked() ), this, SLOT( slotAutexecDrive() ) );

    // itemChanged
    connect( ui.lwProfile, SIGNAL( itemClicked( QListWidgetItem* ) ), this, SLOT( slotListWidget( QListWidgetItem* ) ) );

    // windows title for the application
    appVersion = getAppVersion();

    titleLin = "DOSBox - Front End for Linux " + appVersion;
    titleWin = "DOSBox - Front End for Windows " + appVersion;
    titleMac = "DOSBox - Front End for Mac " + appVersion;

#ifdef Q_OS_WIN32

    setWindowTitle( titleWin );
    QApplication::setStyle( "windowsxp" );
#endif

#ifdef Q_OS_MACX

    setWindowTitle( titleMac );
#endif

#ifdef Q_OS_MAC9

    setWindowTitle( titleMac );
#endif

#ifdef Q_OS_UNIX

    setWindowTitle( titleLin );
#endif

    // center the application on desktop screen
    QDesktopWidget *desktop = qApp->desktop();
    const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
    int left = ( rect.width() - width() ) / 2;
    int top = ( rect.height() - height() ) / 2;
    setGeometry( left, top, width(), height() );
}

DBoxFE::~DBoxFE()
{}

/**
 * TODO Close event
 **/
void DBoxFE::closeEvent( QCloseEvent *e )
{
    switch( QMessageBox::information( this, winTitle(), "Would you realy quit?", "Yes", "No", 0, 1 ) )
    {
    case 0: // Yes clicked
	slotSaveGP(); /* Save profile list */
	e->accept(); /* accept the quit */
        break;
    case 1: // No clicked
	e->ignore();
	return;
        break;
    }
}

/**
 * TODO Initial DBoxFE
 **/
void DBoxFE::init()
{
    DB_BASE gpIni;

    QString file;
    file = QDir::homePath();
    file.append( "/.dboxfe/profile/profile.ini" );
    gpIni.readGPIni( file, ui.lwProfile );
}

/**
 * TODO Save game profile
 **/
void DBoxFE::slotSaveGP()
{
    XMLPreferences settGP( "DBoxFE", "Alexander Saal" );
    settGP.setVersion( getAppVersion() );
    
    QString file;
    file = QDir::homePath();
    file.append( "/.dboxfe/profile/profile.xml" );
    
    QStringList sList;

    for( int a = 0; a < ui.lwProfile->count(); ++a )
    {
        sList.append( ui.lwProfile->item( a )->text() );
    }
    
    settGP.setStringList( "Profile", "Name", sList );
    settGP.getStringList( "Profile", "Name" );
    settGP.save( file );
}

/**
 * TODO Create game profile file
 **/
void DBoxFE::slotCreateGP()
{    
    QListWidgetItem *gpItem = new QListWidgetItem;
    DBoxFE_Profile *dbfe_profile = new DBoxFE_Profile();

    if ( dbfe_profile->exec() == QDialog::Accepted )
    {
        gpItem->setText( dbfe_profile->ui.LEProfile->text() );
        ui.lwProfile->addItem( gpItem );
    }
}

/**
 * TODO Start dosbox with configuration file
 **/
void DBoxFE::slotStartDBox()
{

    gpItem = ui.lwProfile->currentItem();

    if ( gpItem == NULL )
    {
        QMessageBox::information( this, winTitle(), "Please select profile." );
        return;
    }

    gpTxt = gpItem->text();

    m_conf = QDir::homePath();
    m_conf.append( "/.dboxfe/" + gpTxt + ".conf" );

    if ( !QFile( m_conf ).exists() )
    {
        QMessageBox::information( this, winTitle(), "Configuration file not found!\n\n'" + m_conf + "'" );
        qDebug() << "DBoxFE Debug: Configuration file not found! " << m_conf;
        return;
    }

    if( ui.rbtnDBXStabel->isChecked() )
    {
        if( ui.LEDbxStabel->text().isEmpty() )
        {
            QMessageBox::information( this, winTitle(), "Can not start dosbox, no dosbox binary was selected.\nPlease choose dosbox binary." );
            ui.twDbx->setCurrentIndex( 1 );
            return;
        }
        start( ui.LEDbxStabel->text(), "-conf", m_conf );

    }
    else if( ui.rbtnDBXStabel->isChecked() )
    {
        if( ui.LEDbxCvs->text().isEmpty() )
        {
            QMessageBox::information( this, winTitle(), "Can not start dosbox, no dosbox binary was selected.\nPlease choose dosbox binary." );
            ui.twDbx->setCurrentIndex( 1 );
            return;
        }
        start(  ui.LEDbxCvs->text(), "-conf", m_conf );
    }
}

void DBoxFE::slotRemoveGP()
{
    gpItem = new QListWidgetItem;

    gpItem = ui.lwProfile->currentItem();

    if ( gpItem == NULL )
    {
        QMessageBox::information( this, winTitle(), "Please select profile to delet it!" );
        return;
    }

    gpTxt = gpItem->text();

    if( gpTxt.isEmpty() )
    {
        QMessageBox::information( this, winTitle(), "Please select profile for remove from list!" );
    }
    else
    {
	m_file = QDir::homePath();
	m_file.append( "/.dboxfe/" + gpTxt + ".conf" );
        QFile f( m_file );
	
        switch( QMessageBox::information( this, winTitle(), "Would you delete the profile and configuration file?\nIf you click 'No' only the profile from list will be removed.", "Yes", "No", "Cancel", 0, 2 ) )
        {
        case 0: // Yes clicked
	    delete ui.lwProfile->currentItem();
	    
	    if( f.exists() ){
		f.remove();
	    }
	    
            ui.lwOutPut->addItem( "Game Profile -> " + gpTxt + " was deleted" );
            ui.lwOutPut->addItem( "Game Profile -> " + f.fileName() + " was deleted" );
            ui.lwOutPut->update();
	    m_file = "";
            break;
        case 1: // No clicked but delete profile from list
            delete ui.lwProfile->currentItem();
            ui.lwOutPut->addItem( "Game Profile -> " + gpTxt + " was deleted" );
            ui.lwOutPut->update();
            break;
        case 2: // Cancel clicked or Escape pressed
            return;
            break;
        }
    }
}

/**
 * TODO Coose snapshot directory
 **/
void DBoxFE::slotSnapDir()
{

    qDebug( "void DBoxFE::slotSnapDir()" );
}

/**
 * TODO DOSBox language, eg.: german is my language :)
 **/
void DBoxFE::slotLanguage()
{

    QString strLng = QFileDialog::getOpenFileName( this, "Open language file", QDir::homePath(), "Language file (*.*)" );
    if ( strLng.isEmpty() )
        return;
    ui.LELanguage->setText( strLng );
}

/**
 * TODO Choose stabel binary of dosbox
 **/
void DBoxFE::slotDbxStable()
{

    QString strDbxStabel = QFileDialog::getOpenFileName( this, "Open DOSBox stabel binary", QDir::currentPath(), "DOSBox binary (dosbox)" );

    if ( strDbxStabel.isEmpty() )
        return;

    ui.LEDbxStabel->setText( strDbxStabel );

    QProcess *p = new QProcess( this );
    p->start( strDbxStabel, QStringList() << "-version" );

    while( p->waitForFinished() )
        ui.LEDbxVersion->setText( QString( "DOSBox Version: " + p->readAll() ) );
}

/**
 * TODO Choose cvs binary of dosbox
 **/
void DBoxFE::slotDbxCvs()
{

    QString strDbxCVS = QFileDialog::getOpenFileName( this, "Open DOSBox CVS binary", QDir::currentPath(), "DOSBox binary (dosbox)" );

    if ( strDbxCVS.isEmpty() )
        return;

    ui.LEDbxCvs->setText( strDbxCVS );

    QProcess *p = new QProcess( this );
    p->start( strDbxCVS, QStringList() << "-version" );

    while( p->waitForFinished() )
        ui.LEDbxVersion->setText( QString( "DOSBox Version: " + p->readAll() ) );
}

/**
 * TODO Misc (Modem, Autoexec, Dos)
 **/
void DBoxFE::slotAutexecAdd()
{
    qDebug( "void DBoxFE::slotAutexecAdd()" );
}

/**
 * TODO Autoexec option
 **/
void DBoxFE::slotAutexecRemove()
{
    qDebug( "void DBoxFE::slotAutexecRemove()" );
}

/**
 * TODO Update autexec item in the list
 **/
void DBoxFE::slotAutexecUpdate()
{
    qDebug( "void DBoxFE::slotAutexecUpdate()" );
}

/**
 * Open the autexec drive, for automaunt in dosbox
 **/
void DBoxFE::slotAutexecDrive()
{
    qDebug( "void DBoxFE::slotAutexecDrive()" );
}

/**
 * Open the configuration file for selected profile
 **/
void DBoxFE::slotListWidget(QListWidgetItem* item)
{
    DB_BASE gpIni;

    QString file;
    file = QDir::homePath();
    file.append( "/.dboxfe/" + item->text() + ".conf" );

    //gpIni.readGPIni( file, ui.lwProfile  );
    gpIni.readDBConf( file, this );
}

/**
 * Function for start dosbox and read output
 **/
void DBoxFE::start( const QString& bin, const QString &param, const QString &conf )
{

    dBox = new QProcess(this);

    m_param.append( param );
    m_param.append( conf );

    dBox->start( bin, m_param );
    connect( dBox, SIGNAL( readyReadStandardOutput()), this, SLOT( readOutput() ) );
    connect( dBox, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( finish() ) );

    this->hide();

    ui.btnStartDBox->setEnabled( false );

    m_param.clear();
}

void DBoxFE::readOutput()
{
    while( dBox->canReadLine() )
    {
        m_result = dBox->readLine();
        ui.lwOutPut->addItem( "dosbox cmd output ->" + m_result.mid( m_result.indexOf( ":" ) + 1 ) );
        ui.lwOutPut->update();
    }
}

void DBoxFE::finish()
{
    this->show();
    ui.btnStartDBox->setEnabled( true );
}

void DBoxFE::contextMenuEvent ( QContextMenuEvent *ce  )
{
    QAction *remGP = new QAction( QIcon(":/pics/images/delete_16.png"), tr("&Remove profile"), ui.lwProfile );
    QAction *creGP = new QAction( QIcon(":/pics/images/documents_16.png"), tr("&Create profile"), ui.lwProfile );
    QAction *quit = new QAction( QIcon(":/pics/images/documents_16.png"), tr("&Quit"), ui.lwProfile );
    
    connect(remGP, SIGNAL(triggered()), this, SLOT(slotRemoveGP()));
    connect(creGP, SIGNAL(triggered()), this, SLOT(slotCreateGP()));
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));

    QMenu *menu = new QMenu( "<font color=darkblue><u><b>Game Profile Menu</b></u></font>", ui.lwProfile );
    menu->addAction( remGP );
    menu->addAction( creGP );
    menu->addSeparator();
    menu->addAction( quit );   
    menu->exec(ce->globalPos());

  
    // Qt 3 stuff :)
    /*Q3PopupMenu* contextMenu = new Q3PopupMenu( ui.lwProfile );
    Q_CHECK_PTR( contextMenu );
    QLabel *caption = new QLabel( "<font color=darkblue><u><b>Game Profile Menu</b></u></font>", this );
    caption->setAlignment( Qt::AlignCenter );
    contextMenu->insertItem( caption );
    contextMenu->insertItem( "remove Profile", this, SLOT( slotRemoveGP() ) );
    contextMenu->insertItem( "create Profile", this, SLOT( slotCreateGP() ) );
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;*/
}
