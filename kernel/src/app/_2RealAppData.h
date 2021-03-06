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

#include "helpers/_2RealAny.h"

namespace _2Real
{
	class TimestampedData;

	namespace app
	{
		class AppData
		{

		public:

			AppData();
			AppData( TimestampedData const& data, std::string const& typeName, std::string const& longTypename, std::string const& name );

			const std::string getLongTypename() const;
			std::string const& getTypename() const;
			std::string const& getName() const;
			const std::string getDataAsString() const;

			template< typename T >
			bool isDatatype() const
			{
				return m_Data.isDatatype< T >();
			}

			template< typename T >
			T const& getData() const
			{
				T const& data = m_Data.extract< T >();
				return data;
			}

			template< typename T >
			void copyData( T &val )
			{
				T const& data = m_Data.extract< T >();
				val = data;
			}

		private:

			std::string		m_Name;
			Any				m_Data;
			std::string		m_Typename;
			std::string		m_LongTypename;

		};
	}
}
