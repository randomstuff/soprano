/* 
 * This file is part of Soprano Project.
 *
 * Copyright (C) 2007-2008 Sebastian Trueg <trueg@kde.org>
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

#ifndef _SOPRANO_SERVER_DBUS_NODEITERATOR_INTERFACE_H_
#define _SOPRANO_SERVER_DBUS_NODEITERATOR_INTERFACE_H_

#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include "node.h"
#include "dbusabstractinterface.h"

Q_DECLARE_METATYPE(Soprano::Node)

namespace Soprano {

    class Node;

    namespace Client {
        class DBusNodeIteratorInterface: public DBusAbstractInterface
        {
            Q_OBJECT

        public:
            DBusNodeIteratorInterface( const QString& service, const QString& path, const QDBusConnection& connection, QObject *parent = 0 );
            ~DBusNodeIteratorInterface();

        public Q_SLOTS:
            inline QDBusReply<Soprano::Node> current()
            {
                QList<QVariant> argumentList;
                return callWithArgumentListAndBigTimeout(QDBus::Block, QLatin1String("current"), argumentList);
            }

            inline QDBusReply<bool> next()
            {
                QList<QVariant> argumentList;
                return callWithArgumentListAndBigTimeout(QDBus::Block, QLatin1String("next"), argumentList);
            }

            inline QDBusReply<void> close()
            {
                QList<QVariant> argumentList;
                return callWithArgumentListAndBigTimeout(QDBus::Block, QLatin1String("close"), argumentList);
            }
        };
    }
}

#endif
