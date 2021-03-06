/*
 * This file is part of Soprano Project.
 *
 * Copyright (C) 2007-2009 Sebastian Trueg <trueg@kde.org>
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

#ifndef _SOPRANO_SERVER_CLIENT_CONNECTION_H_
#define _SOPRANO_SERVER_CLIENT_CONNECTION_H_

#include "error.h"
#include "sopranotypes.h"
#include "socket.h"

#include <QtCore/QObject>
#include <QtCore/QList>


class QIODevice;

namespace Soprano {

    class Node;
    class Statement;
    class BindingSet;
    class BackendSetting;

    namespace Client {

        class ClientConnectionPrivate;

        /**
         * A ClientConnection is just a wrapper class over a socket, which can be used to send
         * commands over the socket. That is all it is.
         *
         */
        class ClientConnection : public QObject, public Error::ErrorCache
        {
            Q_OBJECT

        public:
            ClientConnection( QObject* parent = 0 );
            virtual ~ClientConnection();

            // Backend methods
            /**
             * Create a new Model and return its ID.
             */
            int createModel( const QString& name, const QList<BackendSetting>& );
            void removeModel( const QString& name );
            Soprano::BackendFeatures supportedFeatures();

            // Model methods
            Error::ErrorCode addStatement( int modelId, const Statement &statement );
            int listContexts( int modelId );
            int executeQuery( int modelId, const QString &query, Query::QueryLanguage type, const QString& userQueryLanguage );
            int listStatements( int modelId, const Statement &partial );
            Error::ErrorCode removeStatement( int modelId, const Statement &statement );
            Error::ErrorCode removeAllStatements( int modelId, const Statement &statement );
            int statementCount( int modelId );
            bool isEmpty( int modelId );
            bool containsStatement( int modelId, const Statement &statement );
            bool containsAnyStatement( int modelId, const Statement &statement );
            Node createBlankNode( int modelId );

            // Iterator methods
            bool iteratorNext( int id );
            Node nodeIteratorCurrent( int id );
            Statement statementIteratorCurrent( int id );
            BindingSet queryIteratorCurrent( int id );
            Statement queryIteratorCurrentStatement( int id );
            int queryIteratorType( int id );
            bool queryIteratorBoolValue( int id );

            void iteratorClose( int id );

            bool checkProtocolVersion();

            virtual bool connect() = 0;
            virtual bool disconnect() = 0;
            virtual bool isConnected() = 0;

        protected:
            /**
             * Returns the underlying socket that is used for communication.
             *
             * This should never return 0.
             */
            virtual Socket* getSocket() = 0;

        private:
            ClientConnectionPrivate* const d;
        };
    }
}

#endif
