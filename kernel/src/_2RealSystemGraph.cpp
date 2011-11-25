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

#include "_2RealSystemGraph.h"
#include "_2RealRunnable.h"
#include "_2RealExceptionHandler.h"

#include <iostream>

namespace _2Real
{
	SystemGraph::SystemGraph(Identifier const& _id) :
		Entity(_id),
		Graph(),
		m_ExceptionHandler(_id),
		m_Threads(4, 20, 10000, 0)
	{
	}

	SystemGraph::~SystemGraph()
	{
		for (RunnableList::iterator it = m_Children.begin(); it != m_Children.end(); it++)
		{
			(*it)->stop();
		}

		m_Threads.joinAll();
		m_Threads.stopAll();

		for (RunnableList::iterator it = m_Children.begin(); it != m_Children.end(); it++)
		{
			std::string name;
			try
			{
				name = (*it)->name();
				std::cout << "deleting runnable: " << name << std::endl;
				delete *it;
			}
			catch (...)
			{
				std::cout << "error on runnable destruction: " << name << std::endl;
			}
		}
	}

	void SystemGraph::registerExceptionCallback(ExceptionCallback callback)
	{
		m_ExceptionHandler.registerExceptionCallback(callback);
	}

	void SystemGraph::unregisterExceptionCallback(ExceptionCallback callback)
	{
		m_ExceptionHandler.unregisterExceptionCallback(callback);
	}

	void SystemGraph::insertChild(Runnable *const child, unsigned int const& index)
	{
		m_Children.push_back(child);

		//if (m_Threads.capacity() < m_Children.size())
		//{
		//	m_Threads.addCapacity(1);
		//}
	}

	void SystemGraph::removeChild(unsigned int const& id)
	{
		RunnableList::iterator it = iteratorId(id);
		m_Children.erase(it);

		//if (m_Threads.capacity() < m_Children.size())
		//{
		//	m_Threads.addCapacity(1);
		//}
	}

	void SystemGraph::startAll()
	{
	}

	void SystemGraph::stopAll()
	{
	}

	void SystemGraph::handleException(Runnable &_child, Exception &_exception)
	{
		m_ExceptionHandler.handleException(_exception, _child.identifier());
		//Graph *subgraph = child->father();
		//stopChild(subgraph->id());
	}

	void SystemGraph::startChild(unsigned int const& id)
	{
		RunnableList::iterator it = this->iteratorId(id);

		if (it == m_Children.end())
		{
			//throw ChildNotFoundException(name(), id.name());
		}

		Runnable *child = *it;
		child->checkConfiguration();
		child->start(false);

		m_Threads.start(*it);
	}

	void SystemGraph::stopChild(unsigned int const& _id)
	{
		RunnableList::iterator it = this->iteratorId(_id);
		if (it == m_Children.end())
		{
			throw Exception("could not start container, " + name() + " does not contain this container");
		}
		//if (!(*it))
		//{
		//	throw Exception(std::string("internal error - null pointer stored in system graph: ").append(this->name()));
		//}

		//Runnable *child = *it;
		//std::map< unsigned int, Poco::Thread * >::iterator thread = m_Threads.find(child->id());
		//if (thread != m_Threads.end())
		//{
		//	child->stop();
		//	thread->second->join();
		//	delete thread->second;
		//	m_Threads.erase(thread);
		//}
	}

}