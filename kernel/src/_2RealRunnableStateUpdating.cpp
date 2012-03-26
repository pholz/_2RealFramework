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

#include "_2RealRunnable.h"
#include "_2RealException.h"
#include "_2RealRunnableStateCreated.h"
#include "_2RealRunnableStateSetUp.h"
#include "_2RealRunnableStateReady.h"
#include "_2RealRunnableStateUpdating.h"
#include "_2RealRunnableStateShutDown.h"
#include "_2RealRunnableStateError.h"

#include <iostream>

namespace _2Real
{

	RunnableStateUpdating::RunnableStateUpdating() :
		AbstractRunnableState(3, "this runnable is ready to be updated and waiting for a thread to do so")
	{
	}

	void RunnableStateUpdating::setUp(Runnable &runnable) const
	{
	}

	const bool RunnableStateUpdating::tryGetReady() const
	{
		return false;
	}

	const bool RunnableStateUpdating::tryBeginUpdate() const
	{
		return false;
	}

	const bool RunnableStateUpdating::tryFinishUpdate() const
	{
		return true;
	}

	const bool RunnableStateUpdating::shutDown(Runnable &runnable) const
	{
		return false;
	}

}