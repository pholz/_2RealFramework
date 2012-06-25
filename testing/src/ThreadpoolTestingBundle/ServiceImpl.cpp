#include "ServiceImpl.h"

#include "_2RealFrameworkContext.h"
#include "_2RealException.h"

#include <iostream>
#include <vector>
#include <string>

using _2Real::FrameworkContext;
using _2Real::ContextBlock;
using _2Real::Exception;

using std::cout;
using std::endl;
using std::string;

TestContext::TestContext() :
	ContextBlock(),
	m_Counter( 100 )
{
}

void TestContext::setup( FrameworkContext &context )
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

void Out::setup( FrameworkContext &context )
{
	try
	{
		m_Out = context.getOutletHandle( "outlet" );
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
		cout << " OUT" << endl;
		++m_Out.getWriteableRef< unsigned int >();
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void InOut::setup( FrameworkContext &context )
{
	try
	{
		m_In = context.getInletHandle( "inlet" );
		m_Out = context.getOutletHandle( "outlet" );
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
		cout << " INOUT" << endl;
		m_Out.getWriteableRef< unsigned int>() = m_In.getReadableRef< unsigned int >();
	}
	catch ( Exception &e)
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};

void In::setup( FrameworkContext &context )
{
	try
	{
		m_Counter = -1;
		m_In = context.getInletHandle( "inlet" );
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
		if ( ++m_Counter == 100 )
		{
			//cout << m_In.getReadableRef< unsigned int >() << endl;
			cout << "YAY!" << endl;
			m_Counter = 0;
		}
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
};