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

#include "_2RealAbstractUberBlockManager.h"

#include "Poco/Mutex.h"

namespace _2Real
{

	typedef std::list< AbstractUberBlock * >	BlockList;

	class NotOwnedAndUnordered : public AbstractBlockManager
	{

	public:

		NotOwnedAndUnordered(AbstractUberBlock &owner);
		~NotOwnedAndUnordered();

		void								clear();
		AbstractUberBlock &						getBlock(BlockIdentifier const& blockId);
		AbstractUberBlock const&				getBlock(BlockIdentifier const& blockId) const;
		void								addBlock(AbstractUberBlock &block);
		void								removeBlock(AbstractUberBlock &block);
		std::list< BlockIdentifier >		getCurrentBlockIds() const;

	private:

		mutable Poco::FastMutex				m_Access;
		BlockList							m_Blocks;

	};

}