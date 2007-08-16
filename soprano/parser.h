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

#ifndef SOPRANO_PARSER_H
#define SOPRANO_PARSER_H

#include "plugin.h"
#include "soprano_export.h"

#include <QtCore/QObject>

class QTextStream;
class QUrl;


namespace Soprano
{
    class StatementIterator;

    /**
     * Different types of RDF serialization.
     */
    // FIXME: what about the used charsets? Should we and if so, how should we include them?
    enum RdfSerialization {
	SERIALIZATION_UNKNOWN = 0x0,   /**< The serialization is unknown. */
	SERIALIZATION_RDF_XML = 0x1,   /**< Standard RDF/XML serialization */
	SERIALIZATION_N3 = 0x2,        /**< Notation 3: http://www.w3.org/DesignIssues/Notation3 */
	SERIALIZATION_N_TRIPLES = 0x4, /**< N-Triples as defined by W3: http://www.w3.org/TR/rdf-testcases/#ntriples */
	SERIALIZATION_TURTLE = 0x8,    /**< Turtle - Terse RDF Triple Language: http://www.dajobe.org/2004/01/turtle/ */
	SERIALIZATION_TRIG = 0x10,     /**< TriG - Turtle + Named Graphs: http://sites.wiwiss.fu-berlin.de/suhl/bizer/TriG/ */
	SERIALIZATION_USER = 0x20      /**< The user type can be used to introduce unknown RDF serializations by name */
    };
    Q_DECLARE_FLAGS(RdfSerializations, RdfSerialization)

    /**
     * \return The mimetype of serialization or an empty string is serialization is SERIALIZATION_UNKNOWN
     */
    SOPRANO_EXPORT QString serializationMimeType( RdfSerialization serialization );

    /**
     * Parse a mimetype and match it to the RdfSerialization enum.
     * \return the RdfSerialization type that matches mimetype or SERIALIZATION_UNKNOWN if the mimetype 
     * could not be parsed.
     */
    SOPRANO_EXPORT RdfSerialization mimeTypeToSerialization( const QString& mimetype );

    /**
     * \brief Soprano::Parser defines the interface for a Soprano RDF parser plugin.
     *
     * Each parser plugin may support multiple RDF serializations (supportedSerializations()).
     * 
     * To create a new parser plugin simply create a class that implements this interface
     * and is derived from QObject. Then use the Q_INTERFACES macro to define that it
     * is in fact a Backend plugin and export the plugin via the Q_EXPORT_PLUGIN2 macro.
     *
     * \code
     * class MyBackend : public QObject, public Soprano::Parser
     * {
     *   Q_OBJECT
     *   Q_INTERFACES(Soprano::Parser)
     *
     *  public:
     *   StatementIterator parseStream( QTextStream* stream, const QUrl& baseUri, RdfSerialization serialization = SERIALIZATION_UNKNOWN, const QString& userSerialization = QString() ) const;
     * };
     * \endcode
     *
     * In the implementation file export the plugin so it can be picked up by the
     * plugin loading framework:
     *
     * \code
     * Q_EXPORT_PLUGIN2(soprano_mybackend, MyBackend)
     * \endcode
     *
     * \author Daniele Galdi <daniele.galdi@gmail.com><br>Sebastian Trueg <trueg@kde.org>
     */
    class SOPRANO_EXPORT Parser : public Plugin
    {
    public:
	virtual ~Parser();

	/**
	 * The serialiazation types supported by this parser.
	 * \return A combination of RdfSerialization types. If
	 * the list contains SERIALIZATION_USER the parser 
	 * supports additional RDF serialiazations not
	 * officially supported by %Soprano.
	 */
	virtual RdfSerializations supportedSerializations() const = 0;

	/**
	 * A parser can support additional RDF serializations that are not defined in RdfSerialization.
	 * In that case supportedSerializations() has to include SERIALIZATION_USER.
	 *
	 * The default implementation returns an empty list.
	 *
	 * \return A list of supported user RDF serializations.
	 */
	virtual QStringList supportedUserSerializations() const;

	/**
	 * \return \p true if the parser is able to parse RDF data encoded
	 * in serialization s, \p false otherwise.
	 */
	bool supportsSerialization( RdfSerialization s ) const;

	/**
	 * Parse an RDF model which has been serialized in a file,
	 * using the supplied baseURI to resolve any relative URI references.
	 *
	 * The default implementation simply calls parseStream() on an opened
	 * QFile instance.
	 *
	 * \param filename The name (path) of the file to parse
	 * \param baseUri The base URI to be used for relative references.
	 * \param serialization The serialization used in the file.
	 * \param userSerialization If serialization is set to SERIALIZATION_USER this parameter specifies the
	 *       serialization to use. It allows the extension of the %Soprano Parser interface with new
	 *       RDF serializations that are not officially supported by %Soprano.
	 *
	 * \return An iterator that iterates over the result statements.
	 */
	virtual StatementIterator parseFile( const QString& filename, const QUrl& baseUri, RdfSerialization serialization, const QString& userSerialization = QString() ) const;

	/**
	 * Parse an RDF model which has been serialized into a string,
	 * using the supplied baseURI to resolve any relative URI references.
	 *
	 * The default implementation simply calls parseStream().
	 *
	 * \param data The serialized RDF string.
	 * \param baseUri The base URI to be used for relative references.
	 * \param serialization The serialization used for the string data.
	 * \param userSerialization If serialization is set to SERIALIZATION_USER this parameter specifies the
	 *       serialization to use. It allows the extension of the %Soprano Parser interface with new
	 *       RDF serializations that are not officially supported by %Soprano.
	 *
	 * \return An iterator that iterates over the result statements.
	 */
	virtual StatementIterator parseString( const QString& data, const QUrl& baseUri, RdfSerialization serialization, const QString& userSerialization = QString() ) const;

	/**
	 * Read a serialized RDF model from a test stream,
	 * using the supplied baseURI to resolve any relative URI references.
	 *
	 * \param stream The text stream to read the serialized RDF data from.
	 * \param baseUri The base URI to be used for relative references.
	 * \param serialization The serialization used for the string data from the stream.
	 * \param userSerialization If serialization is set to SERIALIZATION_USER this parameter specifies the
	 *       serialization to use. It allows the extension of the %Soprano Parser interface with new
	 *       RDF serializations that are not officially supported by %Soprano.
	 *
	 * \return An iterator that iterates over the result statements.
	 */ 
	virtual StatementIterator parseStream( QTextStream* stream, const QUrl& baseUri, RdfSerialization serialization, const QString& userSerialization = QString() ) const = 0;

	/**
	 * Serialize a list of statements.
	 *
	 * \param it An iterator containing the statements to be serialized.
	 * \param stream The stream the serialized data should be written to.
	 * \param serialization The encoding to be used.
	 * \param userSerialization If serialization is set to SERIALIZATION_USER this parameter specifies the
	 *       serialization to use. It allows the extension of the %Soprano Parser interface with new
	 *       RDF serializations that are not officially supported by %Soprano.
	 *
	 * \return \p true if the %serialization was successful,  false otherwise.
	 */
	virtual bool serialize( StatementIterator it, QTextStream* stream, RdfSerialization serialization, const QString& userSerialization = QString() ) const = 0;

    protected:
	Parser( const QString& name );

    private:
	class Private;
	Private* const d;
    };
}

Q_DECLARE_OPERATORS_FOR_FLAGS(Soprano::RdfSerializations)

Q_DECLARE_INTERFACE(Soprano::Parser, "org.soprano.plugins.Parser/1.0")

#endif // SOPRANO_PARSER_H

