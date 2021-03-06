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

#ifndef _INFERENCE_MODEL_TEST_H_
#define _INFERENCE_MODEL_TEST_H_

#include <QtCore/QObject>

namespace Soprano {
    class Model;
    namespace Inference {
    class InferenceModel;
    }
}

using namespace Soprano;
using namespace Soprano::Inference;


class InferenceModelTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void init();
    void testAddStatementSingle();
    void testAddStatementMulti();
    void testRemoveStatementsSingle();
    void testRemoveStatementsMulti();
    void testPerformInference();
    void testPerformInferenceMulti();
    void testClearInference();
    void testPerformance();
    void testParseRuleFile_data();
    void testParseRuleFile();
    void testParseRule();
    void testLiteralEffect();
    void cleanupTestCase();

private:
    Model* m_model;
    InferenceModel* m_infModel;
};

#endif
