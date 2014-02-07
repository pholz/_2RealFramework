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

namespace _2Real
{

	class UpdateCondition
	{

	public:

		UpdateCondition( const bool fulfilled ) : m_IsFulfilled( fulfilled ) {}
		virtual ~UpdateCondition() {}

		bool isFulfilled() const { Poco::ScopedLock< Poco::FastMutex > lock( m_Access ); return m_IsFulfilled; }
		void set( const bool fulfilled ) { Poco::ScopedLock< Poco::FastMutex > lock( m_Access ); m_IsFulfilled = fulfilled; }

	protected:

		mutable Poco::FastMutex		m_Access;
		bool						m_IsFulfilled;
		bool						m_IsOr;

	};

}