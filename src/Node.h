/* 
 * This file is part of Soprano Project.
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
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef SOPRANO_NODE_H
#define SOPRANO_NODE_H

class QString;
class QUrl;

namespace Soprano
{

class Node
{
public:

  enum Type {
    Unknown = 0,
    Resource,
    Literal,
    Blank
  };

  /**
   * Default costructor. 
   * Represent an Empty node (type == Unknown).
   */
  Node();

  /**
   * Costructor for Resource node.
   */
  Node( const QUrl &uri );
  
  /**
   * Constructor for Literal or Blank node.
   *
   * \param value
   *        The value of a node. Represent a uri string if
   *        if type is Blank.
   * 
   * \param type
   *        The node type, "must" be Literal or Blank.
   */
  Node( const QString &value, Type type );
  
  Node( const Node &other );
  
  virtual ~Node();

  Node &operator=( const Node& other );
  bool operator==( const Node& other ) const;
  
  /**
   * \return The Node type.
   */
  Type type() const;

  /**
   * \return true if the Node is empty.
   */
  bool isEmpty() const;

  /**
   * \return true if the Node is a Resource,Literal or Blank.
   */
  bool isValid() const ;

  /**
   * \return true if the Node is a Literal.
   */
  bool isLiteral() const;

  /**
   * \return true if the Node is a Resource.
   */
  bool isResource() const;

  /**
   * \return true if the Node is a Blank node (anonymous).
   */
  bool isBlank() const;

  /**
   * \return The URI if the node is a Resource node. 
   *         An null QUrl otherwise.
   */
  const QUrl &uri() const;

  /**
   * \return The Literal value if the node is a Literal node. 
   *         An null QString otherwise.
   */
  const QString &literal() const;
  
  /**
   *\return The Blank value if the node is a Blank node. 
   *        An null QString otherwise.
   */
  const QString &blank() const;

private:
  class Private;
  Private *d;
};

}

#endif // SOPRANO_NODE_H
