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

#include "datatypes/_2RealDataField.h"
#include "helpers/_2RealStdIncludes.h"
#include "helpers/_2RealIdentifiable.h"

namespace _2Real
{
	class FieldDescriptor;
	class CustomType;
	class TypeRegistry;

	class TypeMatch;
	class TypeConverter;

	class TypeMetadata
	{

	public:

		~TypeMetadata();

		class TypeMatchSetting
		{
		public:
			enum Type { IDENTICAL_MATCH = 0, PERFECT_TYPE_MATCH = 1 };
			TypeMatchSetting( const Type c );
			TypeMatch const* createMatch( TypeMetadata const* a, TypeMetadata const* b ) const;
			Type getCode() const { return mCode; }
			static Type sPriorities[ 2 ];
		private:
			Type		mCode;
		};

		TypeMetadata( std::shared_ptr< TemplateId > , TypeRegistry const*, TypeRegistry const* );
		std::shared_ptr< const TemplateId > getIdentifier() const;
		//std::string const& getCode() const;
		std::string const& getHumanReadableName() const;
		std::string const& getFullHumanReadableName() const;
		void addField( std::string const&, std::string const&, std::shared_ptr< const FieldDescriptor > );
		bool matches( TypeMetadata const* other, TypeMatchSetting const& desiredMatch, std::shared_ptr< const TypeConverter > &cvAB, std::shared_ptr< const TypeConverter > &cvBA ) const;
		void getDataFields( DataFields &fields ) const;

	private:

		TypeMetadata( TypeMetadata const& other );
		TypeMetadata& operator=( TypeMetadata const& other );

		typedef std::shared_ptr< const FieldDescriptor >			FieldDescriptorRef;
		typedef std::pair< std::string, FieldDescriptorRef >		FieldDescription;		// name / desc
		typedef std::vector< FieldDescription >						FieldDescriptions;

		friend class CustomType;

		std::shared_ptr< TemplateId > 		mIdentifier;
		FieldDescriptions			mFields;
		TypeRegistry				const* mFrameworkTypes;
		TypeRegistry				const* mExportedTypes;

	};
}