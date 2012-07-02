
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

#include "_2RealBundleInternal.h"
#include "app/_2RealBundleHandle.h"
#include "_2RealBundleData.h"
#include "_2RealBlockData.h"
#include "bundle/_2RealBlock.h"
#include "app/_2RealBlockHandle.h"
#include "app/_2RealBundleData.h"
#include "app/_2RealBlockData.h"
#include "app/_2RealParameterData.h"
#include "_2RealBundleManager.h"

#include <sstream>

using std::string;
using std::ostringstream;
using std::make_pair;

namespace _2Real
{

	BundleInternal::BundleInternal( Identifier const& id, BundleData const& data, BundleManager &bundleManager ) :
		m_BundleManager( bundleManager ),
		m_Identifier( id ),
		m_Metadata( data ),
		m_BundleContext()
	{
	}

	BundleInternal::~BundleInternal()
	{
		for ( BlockMap::iterator it = m_BlockInstances.begin(); it != m_BlockInstances.end(); ++it )
		{
			bundle::Block *b = it->second;
			delete b;
		}
	}

	Identifier const& BundleInternal::getIdentifier() const
	{
		return m_Identifier;
	}
	
	std::string const& BundleInternal::getName() const
	{
		return m_Identifier.getName();
	}

	app::BundleHandle BundleInternal::createHandle()
	{
		return app::BundleHandle( *this );
	}

	app::BundleData BundleInternal::getBundleData() const
	{
		app::BundleData bundleData;

		bundleData.m_Author = m_Metadata.getAuthor();
		bundleData.m_Category = m_Metadata.getCategory();

		BundleData::BlockMetas const& blocks = m_Metadata.getExportedBlocks();

		for ( BundleData::BlockMetasConstIterator it = blocks.begin(); it != blocks.end(); ++it )
		{
			app::BlockData blockData;

			blockData.m_Name = it->second.getName();
			blockData.m_Description = it->second.getDescription();
			blockData.m_Category = it->second.getCategory();

			BlockData::ParamMetas const& params = it->second.getParameters();
			BlockData::ParamMetas const& input = it->second.getInlets();
			BlockData::ParamMetas const& output = it->second.getOutlets();
			for ( BlockData::ParamMetasConstIterator it = params.begin(); it != params.end(); ++it )
			{
				app::ParameterData paramData;

				paramData.m_Name = it->getName();
				paramData.m_Typename = it->getTypename();
				paramData.m_LongTypename = it->getLongTypename();

				blockData.m_Parameters.push_back( paramData );
			}

			for ( BlockData::ParamMetasConstIterator it = input.begin(); it != input.end(); ++it )
			{
				app::ParameterData paramData;

				paramData.m_Name = it->getName();
				paramData.m_Typename = it->getTypename();
				paramData.m_LongTypename = it->getLongTypename();

				blockData.m_Inlets.push_back( paramData );
			}

			for ( BlockData::ParamMetasConstIterator it = output.begin(); it != output.end(); ++it )
			{
				app::ParameterData paramData;

				paramData.m_Name = it->getName();
				paramData.m_Typename = it->getTypename();
				paramData.m_LongTypename = it->getLongTypename();

				blockData.m_Outlets.push_back( paramData );
			}

			bundleData.m_ExportedBlocks.push_back( blockData );
		}

		return bundleData;
	}

	BundleData const& BundleInternal::getMetadata() const
	{
		return m_Metadata;
	}

	app::BlockHandle BundleInternal::createBlockInstance( std::string const& blockName )
	{
		// this is a bit strange, bundle mgr will call 'addBlockInstance'
		// = result of interface changes
		return m_BundleManager.createFunctionBlock( *this, blockName );
	}

	void BundleInternal::setBundleContextHandle( app::ContextBlockHandle const& handle )
	{
		// will be called by bundle manager on loading a bundle ( if there is one )
		m_BundleContext = handle;
	}

	app::ContextBlockHandle BundleInternal::getBundleContextHandle() const
	{
		return m_BundleContext;
	}

	unsigned int BundleInternal::getBlockInstanceCount( string const& blockName ) const
	{
		unsigned int counter = 0;
		std::pair< BlockMap::const_iterator, BlockMap::const_iterator > range = m_BlockInstances.equal_range( blockName );
		for ( BlockMap::const_iterator it = range.first; it != range.second; ++it )
		{
			++counter;
		}

		return counter;
	}

	void BundleInternal::addBlockInstance( bundle::Block &block, string const& blockName )
	{
		m_BlockInstances.insert( make_pair( blockName, &block ) );
	}

}