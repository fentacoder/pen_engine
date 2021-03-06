/*************************************************************************************************
 Copyright 2021 Jamar Phillip

Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
*************************************************************************************************/
#pragma once
#include <iostream>
#include "../../src/ops/matrices/mat.h"

namespace pen {
	namespace ai {
		class Weight {
			/*Each Weight contains the matrices for a given layer*/
		public:
			int numPrevLayerNodes;
			int numCurrLayerNodes;
			pen::Mat* weights;
			pen::Mat* weightGrads;
			pen::Mat* bias;
			pen::Mat* biasGrads;
		public:
			Weight();
			Weight(int userNumPrevLayerNodes, int userNumCurrLayerNodes);
			~Weight();
		};
	}
}