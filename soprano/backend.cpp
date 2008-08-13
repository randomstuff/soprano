/*
 * This file is part of Soprano Project.
 *
 * Copyright (C) 2007 Sebastian Trueg <trueg@kde.org>
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

#include "backend.h"

#include <QtCore/QSharedData>


class Soprano::BackendSetting::Private : public QSharedData
{
public:
    Private( BackendOption option_ = BackendOptionNone,
             const QString& userOptionName_ = QString(),
             const QVariant& value_ = QVariant() )
        : option( option_ ),
          userOptionName( userOptionName_ ),
          value( value_ ) {
    }

    BackendOption option;
    QString userOptionName;
    QVariant value;
};


Soprano::BackendSetting::BackendSetting()
    : d( new Private() )
{
}


Soprano::BackendSetting::BackendSetting( BackendOption s )
    : d( new Private( s, QString(), true ) )
{
}


Soprano::BackendSetting::BackendSetting( BackendOption s, const QVariant& value )
    : d( new Private( s, QString(), value ) )
{
}


Soprano::BackendSetting::BackendSetting( const QString& userOption, const QVariant& value )
    : d( new Private( BackendOptionUser, userOption, value ) )
{
}


Soprano::BackendSetting::BackendSetting( const BackendSetting& other )
{
    d = other.d;
}


Soprano::BackendSetting::~BackendSetting()
{
}


Soprano::BackendSetting& Soprano::BackendSetting::operator=( const BackendSetting& other )
{
    d = other.d;
    return *this;
}


Soprano::BackendOption Soprano::BackendSetting::option() const
{
    return d->option;
}


QString Soprano::BackendSetting::userOptionName() const
{
    return d->userOptionName;
}


QVariant Soprano::BackendSetting::value() const
{
    return d->value;
}


void Soprano::BackendSetting::setValue( const QVariant& value )
{
    d->value = value;
}


Soprano::BackendSettings::BackendSettings()
    : QList<BackendSetting>()
{
}


Soprano::BackendSettings::BackendSettings( const BackendSettings& other )
    : QList<BackendSetting>( other )
{
}


Soprano::BackendSettings::BackendSettings( const BackendSetting& setting )
    : QList<BackendSetting>()
{
    append( setting );
}


Soprano::BackendSettings::BackendSettings( const QList<BackendSetting>& settings )
    : QList<BackendSetting>( settings )
{
}


bool Soprano::BackendSettings::hasOption( BackendOption option, const QString& userOptionName ) const
{
    QList<Soprano::BackendSetting>::const_iterator end = constEnd();
    for ( QList<Soprano::BackendSetting>::const_iterator it = constBegin(); it != end; ++it ) {
        const Soprano::BackendSetting& setting = *it;
        if ( setting.option() == option ) {
            if ( option == BackendOptionUser ) {
                if ( setting.userOptionName() == userOptionName )
                    return true;
            }
            else {
                return true;
            }
        }
    }
    return false;
}


Soprano::BackendSetting& Soprano::BackendSettings::setting( BackendOption option, const QString& userOptionName )
{
    QList<Soprano::BackendSetting>::iterator end = this->end();
    for ( QList<Soprano::BackendSetting>::iterator it = begin(); it != end; ++it ) {
        Soprano::BackendSetting& setting = *it;
        if ( setting.option() == option ) {
            if ( option == BackendOptionUser ) {
                if ( setting.userOptionName() == userOptionName )
                    return setting;
            }
            else {
                return setting;
            }
        }
    }
    static BackendSetting s_dummy;
    return s_dummy;
}


Soprano::BackendSetting Soprano::BackendSettings::setting( BackendOption option, const QString& userOptionName ) const
{
    QList<Soprano::BackendSetting>::const_iterator end = constEnd();
    for ( QList<Soprano::BackendSetting>::const_iterator it = constBegin(); it != end; ++it ) {
        const Soprano::BackendSetting& setting = *it;
        if ( setting.option() == option ) {
            if ( option == BackendOptionUser ) {
                if ( setting.userOptionName() == userOptionName )
                    return setting;
            }
            else {
                return setting;
            }
        }
    }
    return BackendSetting();
}


QVariant Soprano::BackendSettings::value( BackendOption option, const QString& userOptionName ) const
{
    return setting( option, userOptionName ).value();
}


class Soprano::Backend::Private
{
public:
};


Soprano::Backend::Backend( const QString& name )
    : Plugin( name ),
      d( new Private() )
{
}


Soprano::Backend::~Backend()
{
    delete d;
}


QStringList Soprano::Backend::supportedUserFeatures() const
{
    return QStringList();
}


bool Soprano::Backend::supportsFeatures( BackendFeatures features, const QStringList& userFeatureList ) const
{
    if ( !( supportedFeatures() & features ) ) {
        return false;
    }

    if ( features & BackendFeatureUser ) {
        for( QStringList::const_iterator it = userFeatureList.begin(); it != userFeatureList.end(); ++it ) {
            if( !supportedUserFeatures().contains( *it ) ) {
                return false;
            }
        }
    }

    return true;
}
