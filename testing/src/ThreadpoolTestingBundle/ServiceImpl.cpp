#include "ServiceImpl.h"

#include "bundle/_2RealBlockHandle.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using _2Real::bundle::BlockHandle;
using _2Real::bundle::ContextBlock;
using _2Real::Exception;

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

TestContext::TestContext() :
	ContextBlock(),
	m_Counter( 100 )
{
}

void TestContext::setup( BlockHandle &handle )
{
	try
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
		m_Val = 2;
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void TestContext::update()
{
	try
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
		m_Val *= 4;
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

unsigned int TestContext::getCounterValue()
{
	Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
	return ++m_Counter;
}

unsigned int TestContext::getCurrentValue()
{
	Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
	return m_Val;
}

void Out::setup( BlockHandle &handle )
{
	try
	{
		m_Msg= handle.getInletHandle( "out msg" );
		m_Out = handle.getOutletHandle( "out outlet" );
		m_Out.getWriteableRef< unsigned int >() = 0;
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void Out::update()
{
	try
	{
		++m_Out.getWriteableRef< unsigned int >();
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void InOut::setup( BlockHandle &handle )
{
	try
	{
		m_In = handle.getInletHandle( "inout inlet" );
		m_Msg= handle.getInletHandle( "inout msg" );
		m_Out = handle.getOutletHandle( "inout outlet" );
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void InOut::update()
{
	try
	{
		m_Out.getWriteableRef< unsigned int>() = m_In.getReadableRef< unsigned int >();
	}
	catch ( Exception &e)
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void In::setup( BlockHandle &handle )
{
	try
	{
		m_In = handle.getInletHandle( "in inlet" );
		m_Msg= handle.getInletHandle( "in msg" );
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void In::update()
{
	try
	{
		ostringstream msg;
		msg << m_Msg.getReadableRef< string >() << " " << m_In.getReadableRef< unsigned int >() << endl;
		cout << msg.str();
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};