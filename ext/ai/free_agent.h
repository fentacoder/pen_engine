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
#include "agent.h"
#include "replay_buffer.h"
#include "../../src/ops/matrices/mat.h"
#include "../../src/objects/containers/map.h"

namespace pen {
	namespace ai {
		class FreeAgent : public pen::ai::Agent {
			/*FreeAgent is based on learning within an infinite state environment*/
		private:
			pen::Mat prevState;
			long numActions;
			int numStateParams;
			pen::ai::Action* prevAction;
			pen::ai::Action** actions;
			Weight* weights;
			/*Number of hidden layers including the output layer*/
			int numLayers;
			float betaM;
			float betaV;
			float preferenceFactor;
			pen::Mat* mHat;
			pen::Mat* vHat;
			pen::ai::ReplayBuffer* replayBuffer;
		public:
			FreeAgent();
			FreeAgent(const std::string& path, pen::ai::Action** userActions, int numActions);
			~FreeAgent();
			void Init(pen::Mat* userInitialState);
			void Init(pen::ai::Action** userActions, pen::ai::Weight* userWeights, pen::Mat* userInitialState, int userNumLayers, long userNumActions, int userNumEpisodes, float userEpsilon = 0.0001f, float userStepSize = 0.1f);
			void Step(pen::Mat state, float reward);
			void Save(const std::string& path);
			void Load(const std::string& path, pen::ai::Action** userActions, long userNumActions);
			Weight* GetWeights();
			int GetLayers();
		private:
			pen::Mat ComputeActionValues(pen::Mat* input);
			void UpdateWeights(Weight* weights, int numLayers);
			pen::Mat Softmax(pen::Mat* actionValues);
			pen::Mat TDError(pen::Mat* states, pen::Mat* nextStates, pen::Mat* actionsMat, pen::Mat* rewards, pen::Mat* terminals);
			void TDUpdate(pen::Mat* states, pen::Mat* delta);
			void Optimize(pen::ai::ReplayBufferData* experiences);
			pen::ai::Action* ChoosePolicy(pen::Mat* s);
			int WeightedRand(pen::Mat* vec);
			pen::Mat* ParseMatrix(std::string input);
			std::string FormatMatrix(pen::Mat* mat, char character);
		};
	}
}