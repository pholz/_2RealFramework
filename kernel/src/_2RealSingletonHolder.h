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

#include "_2RealException.h"

#include "Poco/Mutex.h"

namespace _2Real
{

	/**
	*	singleton holder helper class
	*/

	template< typename T >
	class SingletonHolder
	{

	public:

		SingletonHolder() :
			m_Held(NULL)
		{
		}

		~SingletonHolder()
		{
			delete m_Held;
		}

		T* instance()
		{
			Poco::FastMutex::ScopedLock lock(m_Mutex);

			if (!m_Held)
			{
				m_Held = new T();
			}

			return m_Held;
		}

	private:

		T*					m_Held;
		Poco::FastMutex		m_Mutex;

	};

}