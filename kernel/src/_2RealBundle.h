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

#include "bundle/_2RealBundleMetainfo.h"
#include "bundle/_2RealBlockMetainfo.h"
#include "bundle/_2RealContextBlockMetainfo.h"
#include "helpers/_2RealException.h"
#include "_2RealDatatypes.h"

#if defined( _WIN32 )
	#define _2REAL_LIBRARY_API __declspec( dllexport )
#else
	#define _2REAL_LIBRARY_API
#endif

extern "C"
{
	void _2REAL_LIBRARY_API getBundleMetainfo( _2Real::bundle::BundleMetainfo &info );
}