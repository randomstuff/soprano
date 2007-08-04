/* 
 * This file is part of Soprano Project
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

#ifndef SOPRANO_BACKEND_REDLAND_MODEL_H
#define SOPRANO_BACKEND_REDLAND_MODEL_H

#define LIBRDF_MODEL_FEATURE_CONTEXTS "http://feature.librdf.org/model-contexts"

#include <QtCore/QtGlobal>
#include <QtCore/QTextStream>

#include <redland.h>

#include "storagemodel.h"
#include "statement.h"
#include "node.h"

namespace Soprano
{

    class QueryResultIterator;
    class StatementIterator;

    namespace Redland {

	class RedlandStatementIterator;
	class RedlandQueryResult;

	class RedlandModel: public Soprano::StorageModel
	    {
	    public:
		RedlandModel();

		RedlandModel( librdf_model *model, librdf_storage *storage );

		~RedlandModel();

		librdf_model *redlandModel() const;

		ErrorCode addStatement( const Statement &statement );

		virtual QList<Node> listContexts() const;

		bool containsStatements( const Statement &statement ) const;

		Soprano::QueryResultIterator executeQuery( const Query &query ) const;

		Soprano::StatementIterator listStatements( const Statement &partial ) const;

		ErrorCode removeStatements( const Statement &statement );

		int statementCount() const;

		ErrorCode write( QTextStream &os ) const;

		ErrorCode print() const;

	    private:
		class Private;
		Private *d;

		void removeIterator( RedlandStatementIterator* it ) const;
		void removeQueryResult( RedlandQueryResult* r ) const;

		ErrorCode removeStatement( const Statement& );

		friend class RedlandStatementIterator;
		friend class RedlandQueryResult;
	    }; 

    }
}

#endif // SOPRANO_BACKEND_REDLAND_MODEL_H

