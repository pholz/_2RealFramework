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

#include "datatypes/_2RealPoint.h"

namespace _2Real
{
	std::istream & operator>>( std::istream &in, Point &point )
	{
		in >> point.m_X >> point.m_Y >> point.m_Z >> point.m_Label >> point.m_Id;
		return in;
	}

	std::ostream & operator<<( std::ostream &out, Point const& point )
	{
		out << point.m_X << " " << point.m_Y << " " << point.m_Z << " " << point.m_Label << " " << point.m_Id;
		return out;
	}
}