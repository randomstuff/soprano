/* This file is part of QRDF
 *
 * Copyright (C) 2006 Daniele Galdi <daniele.galdi@gmail.com>
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
 * You should have received a copy of the GNU Library General Public
 * License
 * along with this library; see the file COPYING.LIB.  If not, write
 * to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <QtGlobal>

#include "../src/Node.h"
#include "../src/Statement.h"
#include "../src/Model.h"

#include "../src/World.h"
#include "../src/RedlandModel.h"
#include "../src/RedlandModelFactory.h"

using namespace RDF;

int
main(int argc, char *argv[])
{
  World world;
  world.open();
   
  Node subject( QUrl("http://purl.org/net/dagnele/"), Node::TypeResource );
  Node predicate( QUrl("http://purl.org/dc/elements/1.1/creator"), Node::TypeResource );
  Node object( QString("Daniele Galdi"), Node::TypeLiteral );
  Statement st( subject, predicate, object );

  RedlandModelFactory factory(world);

  //RedlandModel model = factory.createMemoryModel( "test" );
  Model model = factory.createPersistentModel( "test" , "/tmp" );
  //model.add( st );
  //model.write( stdout );

  /* keep gcc -Wall happy */
  return(0);
}
