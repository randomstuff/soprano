/*
 * This file is part of Soprano Project
 *
 * Copyright (C) 2008 Sebastian Trueg <trueg@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "virtuosobackendtest.h"

#include <soprano.h>

#include <QtTest/QtTest>

Soprano::VirtuosoBackendTest::VirtuosoBackendTest()
    : m_modelCnt( 0 )
{
}


Soprano::Model* Soprano::VirtuosoBackendTest::createModel()
{
    const Soprano::Backend* b = Soprano::discoverBackendByName( "virtuosobackend" );
    if ( b ) {
        BackendSettings settings;
        QString dirName( "soprano_virtuoso_backend_test_model_" );
#ifdef Q_OS_WIN
        QString tmp = qgetenv("TEMP");
#else
        QString tmp = "/tmp";
#endif
        QDir tmpDir( tmp );
        while ( tmpDir.exists( dirName + QString::number( m_modelCnt ) ) )
            ++m_modelCnt;
        dirName += QString::number( m_modelCnt );
        tmpDir.mkdir( dirName );
        settings << BackendSetting( BackendOptionStorageDir, tmp + QDir::separator() + dirName );
//         settings << BackendSetting( BackendOptionHost, "localhost" );
//         settings << BackendSetting( BackendOptionPort, 1111 );
//         settings << BackendSetting( BackendOptionUsername, "dba" );
//         settings << BackendSetting( BackendOptionPassword, "dba" );
        Model* m = b->createModel( settings );
        m_settingsHash.insert( m, settings );
        return m;
    }
    return 0;
}


void Soprano::VirtuosoBackendTest::deleteModel( Soprano::Model* m )
{
    const Soprano::Backend* b = Soprano::discoverBackendByName( "virtuosobackend" );
    if ( b ) {
        
#ifdef Q_OS_WIN
        // We need to shut down the server before we can remove the test files
        // However we don't have access to the controller, so use reflection to trigger the shutdown
        // It's quite ugly I know, but it's ok for the unit tests imho
        QObject* controller = m->findChild<QObject*>( "virtuoso_controller" );
        if ( controller ) {
            QMetaObject::invokeMethod( controller, "shutdown" );
        }
#endif
        
        b->deleteModelData( m_settingsHash[m] );
        
#ifdef Q_OS_WIN
        QString tmp = qgetenv("TEMP");
#else
        QString tmp = "/tmp";
#endif
        QDir tmpDir( tmp );
        tmpDir.rmdir( settingInSettings( m_settingsHash[m], BackendOptionStorageDir ).value().toString().section( QDir::separator(), -1 ) );
        m_settingsHash.remove( m );
    }
    delete m;
}

QTEST_MAIN( Soprano::VirtuosoBackendTest )

#include "virtuosobackendtest.moc"
