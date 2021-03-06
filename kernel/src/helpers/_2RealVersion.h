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

#include <string>
#include <sstream>

namespace _2Real
{
	class Version
	{

	public:

		Version();
		Version( unsigned int major, unsigned int minor, unsigned int revision );

		bool operator==( Version const& rhs );
		bool operator<( Version const& rhs );

		friend std::ostream& operator<<( std::ostream &out, Version const& version );

		std::string asString() const;

		unsigned int major() const;
		unsigned int minor() const;
		unsigned int revision() const;

	private:

		unsigned int		m_Major;
		unsigned int		m_Minor;
		unsigned int		m_Revision;

	};
}