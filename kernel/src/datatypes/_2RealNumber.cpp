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

#include "datatypes/_2RealNumber.h"
#include <limits>

namespace _2Real
{
	std::istream & operator>>( std::istream &in, Number &number )
	{
		in >> number.m_Val;
		return in;
	}

	std::ostream & operator<<( std::ostream &out, Number const& number )
	{
		out << number.m_Val;
		return out;
	}

	Number::Number() : m_Val( 0. ) {}
	Number::Number( const char c ) : m_Val( static_cast< double >( c ) ) {}
	Number::Number( const unsigned char c ) : m_Val( static_cast< double >( c ) ) {}
	Number::Number( const short s ) : m_Val( static_cast< double >( s ) ) {}
	Number::Number( const unsigned short s ) : m_Val( static_cast< double >( s ) ) {}
	Number::Number( const int i ) : m_Val( static_cast< double >( i ) ) {}
	Number::Number( const unsigned int i ) : m_Val( static_cast< double >( i ) ) {}
	Number::Number( const long l ) : m_Val( static_cast< double >( l ) ) {}
	Number::Number( const unsigned long l ) : m_Val( static_cast< double >( l ) ) {}
	Number::Number( const float f ) : m_Val( static_cast< double >( f ) ) {}
	Number::Number( const double d ) : m_Val( d ) {}

	Number::Number( Number const& src ) : m_Val( src.m_Val ) {}
	Number & Number::operator=( Number const& src ) { m_Val = src.m_Val; return *this; }
	bool Number::operator==( Number const& rhs ) const { return (m_Val == rhs.m_Val); }
	bool Number::operator!=( Number const& rhs ) const { return !(m_Val == rhs.m_Val); }
	bool Number::operator<( Number const& rhs ) const { return (m_Val < rhs.m_Val); }
	bool Number::operator>( Number const& rhs ) const { return (m_Val > rhs.m_Val); }
	bool Number::operator<=( Number const& rhs ) const { return (m_Val <= rhs.m_Val); }
	bool Number::operator>=( Number const& rhs ) const { return (m_Val >= rhs.m_Val); }

	Number Number::operator+( Number const& rhs ) const { return Number( m_Val + rhs.m_Val ); }
	Number Number::operator-( Number const& rhs ) const { return Number( m_Val - rhs.m_Val ); }
	Number Number::operator*( Number const& rhs ) const { return Number( m_Val * rhs.m_Val ); }
	Number Number::operator/( Number const& rhs ) const { return Number( m_Val / rhs.m_Val ); }

	Number & Number::operator+=( Number const& rhs ) { m_Val += rhs.m_Val; return *this; }
	Number & Number::operator-=( Number const& rhs ) { m_Val -= rhs.m_Val; return *this; }
	Number & Number::operator*=( Number const& rhs ) { m_Val *= rhs.m_Val; return *this; }
	Number & Number::operator/=( Number const& rhs ) { m_Val /= rhs.m_Val; return *this; }

	Number::operator char() const { return static_cast< char >( m_Val ); }
	Number::operator unsigned char() const { return static_cast< unsigned char >( m_Val ); }
	Number::operator short() const { return static_cast< short >( m_Val ); }
	Number::operator unsigned short() const { return static_cast< unsigned short >( m_Val ); }
	Number::operator int() const { return static_cast< int >( m_Val ); }
	Number::operator unsigned int() const { return static_cast< unsigned int >( m_Val ); }
	Number::operator long() const { return static_cast< long >( m_Val ); }
	Number::operator unsigned long() const { return static_cast< unsigned long >( m_Val ); }
	Number::operator float() const { return static_cast< float >( m_Val ); }
	Number::operator double() const { return m_Val; }
	
	const double Number::maxVal() { return std::numeric_limits<double>::max(); }
	const double Number::minVal() { return std::numeric_limits<double>::min(); }
}
