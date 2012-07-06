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

#include "app/_2RealInletHandle.h"
#include "app/_2RealOutletHandle.h"
#include "engine/_2RealEngineImpl.h"
#include "engine/_2RealAbstractUberBlock.h"
#include "engine/_2RealAbstractIOManager.h"

#define checkHandle( obj )\
	if ( obj == nullptr ) throw UninitializedHandleException( "inlet handle not initialized" );\

namespace _2Real
{
	namespace app
	{
		InletHandle::InletHandle() :
			Handle(),
			m_InletIO( nullptr )
		{
		}

		InletHandle::InletHandle( InletIO &inletIO ) :
			Handle( &inletIO ),
			m_InletIO( &inletIO )
		{
			m_InletIO->registerHandle( *this );
		}

		InletHandle::~InletHandle()
		{
			if ( isValid() ) m_InletIO->unregisterHandle( *this );
		}

		InletHandle::InletHandle( InletHandle const& other ) :
			Handle( other.m_InletIO ),
			m_InletIO( other.m_InletIO )
		{
			if ( isValid() ) m_InletIO->registerHandle( *this );
		}

		InletHandle& InletHandle::operator=( InletHandle const& other )
		{
			if ( this == &other )
			{
				return *this;
			}

			if ( isValid() )
			{
				m_InletIO->unregisterHandle( *this );
			}

			Handle::operator=( other );
			m_InletIO = other.m_InletIO;

			if ( isValid() )
			{
				m_InletIO->registerHandle( *this );
			}

			return *this;
		}

		AppData InletHandle::getCurrentInput() const
		{
			checkHandle( m_InletIO );
			TimestampedData data = m_InletIO->m_Inlet->getData();
			return AppData( data, m_InletIO->m_Inlet->getTypename(), m_InletIO->m_Inlet->getName() );
		}

		void InletHandle::linkTo( OutletHandle &outlet )
		{
			checkHandle( m_InletIO );
			EngineImpl::instance().createLink( *m_InletIO, *( outlet.m_OutletIO ) );
		}

		void InletHandle::unlinkFrom( OutletHandle &outlet )
		{
			checkHandle( m_InletIO );
			EngineImpl::instance().destroyLink( *m_InletIO, *( outlet.m_OutletIO ) );
		}

		void InletHandle::setUpdatePolicy( const InletHandle::InletUpdatePolicy p )
		{
			checkHandle( m_InletIO );
			if ( p == InletHandle::NEWER_DATA_SINGLE_WEIGHT )
			{
				m_InletIO->m_Inlet->getOwningUberBlock().updateWhenInletDataNew( *m_InletIO, true );
			}
			else if ( p == InletHandle::NEWER_DATA_GROUP_WEIGHT )
			{
				m_InletIO->m_Inlet->getOwningUberBlock().updateWhenInletDataNew( *m_InletIO, false );
			}
			else if ( p == InletHandle::ALWAYS )
			{
				m_InletIO->m_Inlet->getOwningUberBlock().updateWhenInletDataValid( *m_InletIO );
			}
		}

		void InletHandle::setValue( EngineData const& data )
		{
			checkHandle( m_InletIO );
			m_InletIO->m_Buffer->receiveData( data );
		}

		void InletHandle::setBufferSize( const unsigned int size )
		{
			checkHandle( m_InletIO );
			m_InletIO->m_Buffer->setBufferSize( size );
		}

		std::string const& InletHandle::getName() const
		{
			checkHandle( m_InletIO );
			return m_InletIO->m_Inlet->getName();
		}

		std::string const& InletHandle::getLongTypename() const
		{
			checkHandle( m_InletIO );
			return m_InletIO->m_Inlet->getLongTypename();
		}

		std::string const& InletHandle::getTypename() const
		{
			checkHandle( m_InletIO );
			return m_InletIO->m_Inlet->getTypename();
		}
	}
}