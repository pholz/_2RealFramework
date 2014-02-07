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

#include "engine/_2RealAbstractUpdateTrigger.h"
#include "engine/_2RealAbstractStateManager.h"
#include "engine/_2RealEngineImpl.h"
#include "engine/_2RealTimer.h"

namespace _2Real
{

	class TimeBasedTrigger
	{

	public:

		TimeBasedTrigger( AbstractStateManager &mgr, const long timeslice ) :
			m_Condition( false ),
			m_UpdateManager( mgr ),
			m_DesiredTime( timeslice ),
			m_ElapsedTime( 0 )
		{
			AbstractCallback< long > *cb = new MemberCallback< TimeBasedTrigger, long >( *this, &TimeBasedTrigger::tryTriggerUpdate );
			EngineImpl::instance().getTimer().registerToTimerSignal( *cb );
			m_UpdateManager.addTrigger( *this );
		}

		~TimeBasedTrigger()
		{
			AbstractCallback< long > *cb = new MemberCallback< TimeBasedTrigger, long >( *this, &TimeBasedTrigger::tryTriggerUpdate );
			EngineImpl::instance().getTimer().unregisterFromTimerSignal( *cb );
			m_UpdateManager.removeTrigger( *this );
		}

		void tryTriggerUpdate( long &time )
		{
			m_ElapsedTime += time;
			if ( !m_Condition.isFulfilled() && m_ElapsedTime >= m_DesiredTime )
			{
				m_ElapsedTime = 0;
				m_Condition.set( true );
				m_UpdateManager.tryTriggerTime( *this );
			}
		}

		void resetTime()
		{
			m_ElapsedTime = 0;
		}

		bool isFulfilled() const { return m_Condition.isFulfilled(); }
		void set( const bool fulfilled ) { m_Condition.set( fulfilled ); }

	private:

		AbstractStateManager	&m_UpdateManager;
		UpdateCondition			m_Condition;
		long					m_DesiredTime;
		long					m_ElapsedTime;

	};

}