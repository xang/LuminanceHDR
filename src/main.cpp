/**
 * This file is a part of Luminance HDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2006,2007 Giuseppe Rota
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * @author Giuseppe Rota <grota@users.sourceforge.net>
 */

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QObject>

#include "Common/commandline.h"
#include "MainWindow/MainWindow.h"

#ifdef WIN32
#include <QMessageBox>
#include <windows.h>
#endif

int main( int argc, char ** argv )
{
    int rc=-1;

#ifndef Q_WS_MAC
    //CLI application
    // Do not try to run the CLI app on Mac -
    // FIXME: the problem is that some args are supplied when
    // running as a gui-app in Mac OS X, this messes up things.
    if (argc>1)
    {
        QCoreApplication cliApplication( argc, argv );
        QSettings _settings("Luminance", "Luminance");
        settings = &_settings;
        QTranslator translator;
        translator.load(QString("lang_") + LuminanceOptions::getInstance()->gui_lang, I18NDIR);
        cliApplication.installTranslator(&translator);
        CommandLineInterfaceManager cli( argc, argv );
        cliApplication.connect(&cli, SIGNAL(finishedParsing()), &cliApplication, SLOT(quit()));
        rc = cliApplication.exec();
        LuminanceOptions::deleteInstance();
        return rc;
    }
#endif

    //GUI application
#ifdef WIN32
    FreeConsole();
#endif
    Q_INIT_RESOURCE(icons);
    QApplication application( argc, argv );

#ifdef QT_DEBUG
    qDebug() << "i18n folder = " << I18NDIR;
    qDebug() << "QDir::currentPath() = " << QDir::currentPath();
    qDebug() << "QCoreApplication::applicationDirPath() = " << QCoreApplication::applicationDirPath();
#endif

    //QSettings _settings("Luminance", "Luminance");
    //settings = &_settings;
    settings = new QSettings("Luminance", "Luminance");

#ifdef WIN32
    bool found_DLL = false;
    foreach (QString path, application.libraryPaths())
    {
        if ( QFile::exists(path+"/imageformats/qjpeg4.dll") )
        {
            found_DLL = true;
        }
    }
    if (!found_DLL)
    {
        QMessageBox::critical(NULL,
                              QObject::tr("Aborting..."),
                              QObject::tr("Cannot find Qt's JPEG Plugin...<br>Please unzip the DLL package with the option \"use folder names\" activated."));
        return 1;
    }
#endif


    QTranslator guiTranslator;
    QTranslator qtTranslator;
    // 	qDebug( "Looking for i18n files in: " I18NDIR );
    qtTranslator.load(QString("qt_") + LuminanceOptions::getInstance()->gui_lang, I18NDIR);
    guiTranslator.load(QString("lang_") + LuminanceOptions::getInstance()->gui_lang, I18NDIR);
    application.installTranslator(&qtTranslator);
    application.installTranslator(&guiTranslator);
    MainWindow* MW = new MainWindow;
    //application.connect( &application, SIGNAL(lastWindowClosed()), &application, SLOT(quit()) );
    MW->show();
    rc = application.exec();
    LuminanceOptions::deleteInstance();
    return rc;
}

