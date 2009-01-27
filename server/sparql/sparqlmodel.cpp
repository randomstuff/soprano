/*
 * This file is part of the Soprano Project.
 *
 * Copyright (C) 2007 Rajeev J Sebastian <rajeev.sebastian@gmail.com>
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

#include "sparqlmodel.h"
#include "sparqlqueryresult.h"
#include "sparqlprotocol.h"

#include "queryresultiterator.h"
#include "statementiterator.h"
#include "nodeiterator.h"
#include "sopranotypes.h"
#include "parser.h"
#include "pluginmanager.h"

#include <QtCore/QDebug>


Q_DECLARE_METATYPE(Soprano::Error::ErrorCode)
Q_DECLARE_METATYPE(Soprano::StatementIterator)
Q_DECLARE_METATYPE(Soprano::NodeIterator)
Q_DECLARE_METATYPE(Soprano::QueryResultIterator)


namespace {
    QString statementToConstructGraphPattern( const Soprano::Statement& s, bool withContext = false )
    {
        QString query;

        if ( withContext ) {
            query += "graph ";
            if ( s.context().isValid() ) {
                query += s.context().toN3();
            }
            else {
                query += "?g";
            }
            query += " { ";
        }

        if ( s.subject().isValid() ) {
            query += s.subject().toN3() + ' ';
        }
        else {
            query += "?s ";
        }

        if ( s.predicate().isValid() ) {
            query += s.predicate().toN3() + ' ';
        }
        else {
            query += "?p ";
        }

        if ( s.object().isValid() ) {
            query += s.object().toN3();
        }
        else {
            query += "?o";
        }

        if ( withContext ) {
            query += " }";
        }

        return query;
    }

        class StatementIteratorQueryResultBackend : public Soprano::QueryResultIteratorBackend
    {
    public:
        StatementIteratorQueryResultBackend( Soprano::StatementIterator it )
            : QueryResultIteratorBackend(),
              m_iterator( it ) {
        }

        bool next() {
            return m_iterator.next();
        }

        Soprano::BindingSet current() const {
            return Soprano::BindingSet();
        }

        Soprano::Statement currentStatement() const {
            return m_iterator.current();
        }

        Soprano::Node binding( const QString& ) const {
            return Soprano::Node();
        }

        Soprano::Node binding( int ) const {
            return Soprano::Node();
        }

        int bindingCount() const {
            return 0;
        }

        QStringList bindingNames() const {
            return QStringList();
        }

        bool isGraph() const {
            return true;
        }

        bool isBinding() const {
            return false;
        }

        bool isBool() const {
            return false;
        }

        bool boolValue() const {
            return false;
        }

        void close() {
            m_iterator.close();
        }

    private:
        Soprano::StatementIterator m_iterator;
    };

    Soprano::QueryResultIterator iteratorFromData( const QByteArray& data )
    {
        // try parsing the response
        bool ok = false;
        Soprano::Client::SparqlParser::Sparql queryResult = Soprano::Client::SparqlParser::Sparql::parseByteArray( data, &ok );

        // seems to be a binding or boolean result
        if ( ok ) {
            return new Soprano::Client::SparqlQueryResult( queryResult );
        }

        // try parsing it as graph
        else if ( const Soprano::Parser* parser = Soprano::PluginManager::instance()->discoverParserForSerialization( Soprano::SerializationRdfXml ) ) {
            Soprano::StatementIterator it = parser->parseString( data, QUrl(), Soprano::SerializationRdfXml );
            if ( it.isValid() ) {
                // graph result
                return new StatementIteratorQueryResultBackend( it );
            }
        }

        return Soprano::QueryResultIterator();
    }

    enum CommandType {
        ErrorCodeCommand,
        QueryCommand,
        ListStatementsCommand,
        ListNodesCommand,
        BooleanCommand
    };

    class Command {
    public:
        Soprano::Util::AsyncResult* result;
        int id;
        CommandType commandType;
    };
}


class Soprano::Client::SparqlModel::Private
{
public:
    SparqlProtocol* client;
    QHash<int, Command> commands;
};


Soprano::Client::SparqlModel::SparqlModel( const QString& endpoint,
                                           quint16 port,
                                           const QString& user,
                                           const QString& password )
    : Soprano::Model(),
      d( new Private() )
{
    d->client = new SparqlProtocol( this );
    d->client->setHost( endpoint, port );
    d->client->setUser( user, password );
    connect( d->client, SIGNAL( requestFinished( int, bool, const QByteArray& ) ),
             this, SLOT( slotRequestFinished( int, bool, const QByteArray& ) ) );
}


Soprano::Client::SparqlModel::~SparqlModel()
{
    d->client->cancel();
    delete d;
}


void Soprano::Client::SparqlModel::setHost( const QString& hostname, quint16 port )
{
    d->client->setHost( hostname, port );
}


void Soprano::Client::SparqlModel::setUser( const QString& userName, const QString& password )
{
    d->client->setUser( userName, password );
}


void Soprano::Client::SparqlModel::setPath( const QString& path )
{
    d->client->setPath( path );
}


// QString Soprano::Client::SparqlModel::host() const
// {
//     return
// }


// quint16 Soprano::Client::SparqlModel::port() const
// {
// }


// QString Soprano::Client::SparqlModel::userName() const
// {
// }


// QString Soprano::Client::SparqlModel::password() const
// {
// }


Soprano::Error::ErrorCode Soprano::Client::SparqlModel::addStatement( const Statement& statement )
{
    if( !statement.isValid() ) {
        setError( "Cannot add invalid statement.", Error::ErrorInvalidArgument );
        return Error::ErrorInvalidArgument;
    }

    // FIXME: what if the context is not defined?
    if ( !statement.context().isValid() ) {
        setError( "No support for the default context.", Error::ErrorInvalidArgument );
        return Error::ErrorInvalidArgument;
    }

    // FIXME: This looks like SPARUL. How can we know if its supported?
    QString insert = QString("INSERT INTO %1").arg( statementToConstructGraphPattern( statement, true ) );
    d->client->blockingQuery( insert );

    setError( d->client->lastError() );

    return Error::convertErrorCode( d->client->lastError().code() );
}


Soprano::NodeIterator Soprano::Client::SparqlModel::listContexts() const
{
    QueryResultIterator r = executeQuery("select distinct ?g where { graph ?g {?s ?p ?o}}", Query::QueryLanguageSparql, QString());
    return r.iterateBindings("g");
}


bool Soprano::Client::SparqlModel::containsStatement( const Statement& statement ) const
{
    // fail on invalid statements
    if ( !statement.isValid() ) {
        setError( "Cannot call containsStatement on invalid statements", Error::ErrorInvalidArgument );
        return false;
    }

    QString query;
    if ( statement.context().isValid() ) {
        query = QString( "ask { %1 }" ).arg( statementToConstructGraphPattern( statement, true ) );
    }
    else {
        // an empty context means the default context, i.e. no context set
        query = QString( "ask { %1 . OPTIONAL { %2 } . FILTER(!bound(?g)) . }" )
                .arg( statementToConstructGraphPattern( statement, false ) )
                .arg( statementToConstructGraphPattern( statement, true ) );
    }
    return executeQuery( query, Query::QueryLanguageSparql ).boolValue();
}


bool Soprano::Client::SparqlModel::containsAnyStatement( const Statement& statement ) const
{
    QString query = QString( "ask { %1 }" ).arg( statementToConstructGraphPattern( statement, true ) );
    return executeQuery( query, Query::QueryLanguageSparql ).boolValue();
}


Soprano::QueryResultIterator Soprano::Client::SparqlModel::executeQuery( const QString& query, Query::QueryLanguage language, const QString& userQueryLanguage ) const
{
    if ( language != Query::QueryLanguageSparql ) {
        setError( "Unsupported query language: " + Query::queryLanguageToString( language, userQueryLanguage ), Error::ErrorInvalidArgument );
    }
    else {
        QByteArray response = d->client->blockingQuery( query );
        setError( d->client->lastError() );

        if( !lastError() && !response.isEmpty() ) {
            return iteratorFromData( response );
        }
    }

    // client returned error
    return QueryResultIterator();
}


Soprano::StatementIterator Soprano::Client::SparqlModel::listStatements( const Statement& partial ) const
{
    // we cannot use a construct query due to missing graph support
    QString query = QString( "select * where { %1 }" ).arg( statementToConstructGraphPattern( partial, true ) );
    qDebug() << "List Statements Query" << query;
    return executeQuery( query, Query::QueryLanguageSparql )
        .iterateStatementsFromBindings( partial.subject().isValid() ? QString() : QString( 's' ),
                                        partial.predicate().isValid() ? QString() : QString( 'p' ),
                                        partial.object().isValid() ? QString() : QString( 'o' ),
                                        partial.context().isValid() ? QString() : QString( 'g' ),
                                        partial );
}


Soprano::Error::ErrorCode Soprano::Client::SparqlModel::removeStatement( const Statement& statement )
{
    if ( !statement.context().isValid() ) {
        setError( "No support for the default context.", Error::ErrorInvalidArgument );
        return Error::ErrorInvalidArgument;
    }

    // FIXME: SPARUL?
    QString query = QString( "delete from %2" ).arg( statementToConstructGraphPattern( statement, true ) );
    d->client->blockingQuery( query );
    setError( d->client->lastError() );
    return Error::convertErrorCode( d->client->lastError().code() );
}


Soprano::Error::ErrorCode Soprano::Client::SparqlModel::removeAllStatements( const Statement& statement )
{
    if ( statement.isValid() && statement.context().isValid() ) {
        return removeStatement( statement );
    }
    else {
        Q_UNUSED(statement);
        setError( "No removeAllStatements support.", Error::ErrorNotSupported );
        return Error::ErrorNotSupported;
    }
}


int Soprano::Client::SparqlModel::statementCount() const
{
    setError( "No statement count supported.", Error::ErrorNotSupported );
    return -1;
}


bool Soprano::Client::SparqlModel::isEmpty() const
{
    setError( "No isEmpty support.", Error::ErrorNotSupported );
    return false;
}


Soprano::Node Soprano::Client::SparqlModel::createBlankNode()
{
    setError( "Creating blank nodes not supported.", Error::ErrorNotSupported );
    return Node();
}


Soprano::Util::AsyncResult* Soprano::Client::SparqlModel::executeQueryAsync( const QString& query,
                                                                             Query::QueryLanguage language,
                                                                             const QString& userQueryLanguage ) const
{
    Util::AsyncResult* result = Util::AsyncResult::createResult();
    Command cmd;
    cmd.result = result;
    cmd.commandType = QueryCommand;
    cmd.id = d->client->query( query );
    d->commands[cmd.id] = cmd;
    return result;
}


void Soprano::Client::SparqlModel::slotRequestFinished( int id, bool error, const QByteArray& data )
{
    if ( d->commands.contains( id ) ) {
        Command cmd = d->commands[id];
        if ( error ) {
            cmd.result->setResult( QVariant(), d->client->lastError() );
        }
        else {
            switch( cmd.commandType ) {
            case QueryCommand:
                cmd.result->setResult( QVariant::fromValue( iteratorFromData( data ) ), Error::Error() );
                break;
            default:
                Q_ASSERT( 0 );
            }
        }
        d->commands.remove( id );
    }
}

#include "sparqlmodel.moc"
