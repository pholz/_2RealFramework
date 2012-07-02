/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#pragma once

#include "helpers/_2RealPoco.h"

#include <list>

namespace _2Real
{

	class AbstractUberBlock;

	class SystemBlockManager
	{

	public:

		~SystemBlockManager();
		void						clearAll();
		void						clearBlockInstances();
		void						addBlock( AbstractUberBlock &block, const bool isContext );
		void						destroyBlock( AbstractUberBlock &block );

	private:

		typedef std::list< AbstractUberBlock * >	BlockList;

		// this is probably not necessary
		mutable Poco::FastMutex		m_BlockAccess;
		BlockList					m_Blocks;
		BlockList					m_ContextBlocks;

	};

}