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

#include "_2RealExceptionHandler.h"
#include "_2RealData.h"
#include "_2RealRunnableException.h"

#include "Poco/Delegate.h"

namespace _2Real
{

	ExceptionHandler::ExceptionHandler(Identifier const& _system) :
		m_System(_system)
	{
	}

	void ExceptionHandler::registerExceptionCallback(ExceptionCallback _callback)
	{
		m_Event += Poco::delegate(_callback);
	}

	void ExceptionHandler::unregisterExceptionCallback(ExceptionCallback _callback)
	{
		m_Event -= Poco::delegate(_callback);
	}

	void ExceptionHandler::handleException(Exception const& _exception, Identifier const& _sender)
	{
		RunnableException e(_exception.what(), _sender, m_System);
		m_Event.notify(this, e);
	}
}