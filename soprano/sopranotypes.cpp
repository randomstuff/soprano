/* This file is part of Soprano
 *
 * Copyright (C) 2006 Daniele Galdi <daniele.galdi@gmail.com>
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

#include "sopranotypes.h"

#include <QtCore/QString>


QString Soprano::serializationMimeType( RdfSerialization serialization, const QString& userSerialization )
{
    switch( serialization ) {
    case SerializationRdfXml:
        return QString::fromLatin1( "application/rdf+xml" );
    case SerializationN3:
        return QString::fromLatin1( "text/rdf+n3" );
    case SerializationNTriples:
        return QString::fromLatin1( "text/plain" ); // FIXME: is this correct?
    case SerializationTurtle:
        return QString::fromLatin1( "application/x-turtle" );
    case SerializationTrig:
        return QString::fromLatin1( "application/x-trig" );
    case SerializationUser:
        return userSerialization;
    default:
        return QString();
    }
}


Soprano::RdfSerialization Soprano::mimeTypeToSerialization( const QString& mimetype )
{
    if ( mimetype == "application/rdf+xml" ||
         mimetype == "text/rdf" ) {
        return SerializationRdfXml;
    }
    else if ( mimetype == "application/rdf+n3" ||
              mimetype == "text/rdf+n3" ||
              mimetype == "text/n3" ) {
        return SerializationN3;
    }
    // FIXME: what about text/plain?
    else if ( mimetype == "application/n-triples" ) {
        return SerializationNTriples;
    }
    else if ( mimetype == "application/x-turtle" ||
              mimetype == "application/turtle") {
        return SerializationTurtle;
    }
    else if ( mimetype == "application/x-trig" ||
              mimetype == "application/trig") {
        return SerializationTrig;
    }
    return SerializationUnknown;
}


QString Soprano::Query::queryLanguageToString( QueryLanguage lang, const QString& userQueryLanguage )
{
    switch( lang ) {
    case QueryLanguageNone:
        return QLatin1String( "none" );
    case QueryLanguageSparql:
        return QLatin1String( "SPARQL" );
    case QueryLanguageRdql:
        return QLatin1String( "RDQL" );
    case QueryLanguageSerql:
        return QLatin1String( "SERQL" );
    default:
        return userQueryLanguage;
    }
}
