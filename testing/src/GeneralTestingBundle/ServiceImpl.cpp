#include "ServiceImpl.h"

#include <iostream>

using _2Real::bundle::BlockHandle;
using _2Real::bundle::ContextBlock;
using _2Real::Exception;
using _2Real::DeviceInfos;
using _2Real::DeviceInfo;

using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextManager::setup( BlockHandle &handle )
{
	try
	{
		m_Value = 0;
		m_Devices = handle.getOutletHandle( "devices" );
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

void ContextManager::update()
{
	try
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
		m_Value += 1000;

		DeviceInfos &devices = m_Devices.getWriteableRef< DeviceInfos >();
		devices.resize( 3 );

		devices[ 0 ] = DeviceInfo( "device 0", "fuck you!", false );
		devices[ 1 ] = DeviceInfo( "device 1", "you suck!", false );
		devices[ 2 ] = DeviceInfo( "device 2", "die!", false );
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

void ContextManager::shutdown()
{
	try
	{
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

unsigned long ContextManager::getValue() const
{
	Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
	return m_Value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Out::Out( ContextBlock &context ) :
	Block(),
	m_Context( dynamic_cast< ContextManager & >( context ) )
{
}

void Out::setup( BlockHandle &handle )
{
	try
	{
		std::cout << "SETUP OUT" << std::endl;
		m_Out = handle.getOutletHandle( "outlet" );
		m_Discard = handle.getOutletHandle( "discard" );
		m_Out.getWriteableRef< unsigned int >() = 0;
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

void Out::update()
{
	try
	{
		++m_Out.getWriteableRef< unsigned int >();
		m_Discard.discard();
		std::cout << "OUT " << m_Out.getWriteableRef< unsigned int >() << std::endl;
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

void Out::shutdown()
{
	try
	{
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

In::In( ContextBlock &context ) :
	Block(),
	m_Context( dynamic_cast< ContextManager & >( context ) )
{
}

void In::setup( BlockHandle &handle )
{
	try
	{
		std::cout << "SETUP IN" << std::endl;

		m_In = handle.getInletHandle( "inlet" );
		m_Counter = 0;
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

void In::update()
{
	try
	{
		std::cout << "IN inlet" << m_In.getReadableRef< unsigned int >() << std::endl;
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}

void In::shutdown()
{
	try
	{
	}
	catch ( Exception &e )
	{
		e.rethrow();
	}
}