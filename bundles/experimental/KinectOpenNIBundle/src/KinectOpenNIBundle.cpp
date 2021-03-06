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
#include "OpenNIDeviceManager.h"
#include "KinectOpenNIRgbBlock.h"
#include "KinectOpenNIDepthBlock.h"
#include "KinectOpenNIIrBlock.h"
#include "KinectOpenNIUserSkeletonBlock.h"
#include "KinectOpenNIMotorBlock.h"

#include "_2RealBundle.h"
#include <sstream>
#include <iostream>

using namespace _2Real;

using namespace _2Real::bundle;
using			_2Real::Exception;
using std::string;
using std::cout;
using std::endl;

void getBundleMetainfo( BundleMetainfo& info )
{
	try
	{
		info.setName("KinectOpenNIBundle");
		info.setDescription( "Kinect OpenNI Bundle" );
		info.setAuthor( "Robert Praxmarer, Nikolas Psaroudakis" );
		info.setCategory( "Devices" );
		info.setContact( "help@cadet.at" );
		info.setVersion( 0, 1, 0 );

		ContextBlockMetainfo contextBlockInfo = info.exportContextBlock< OpenNIDeviceManager >();

		BlockMetainfo rgbBlockInfo = info.exportBlock< KinectOpenNIRgbBlock, WithContext >( "KinectOpenNIRgbBlock" );
		rgbBlockInfo.addInlet<int>( "DeviceIndex", 0 );
		rgbBlockInfo.addInlet<int>( "Width", 640 );
		rgbBlockInfo.addInlet<int>( "Height", 480 );
		rgbBlockInfo.addInlet<int>( "Fps", 30 );
		rgbBlockInfo.addInlet<bool>( "IsMirrored", false );
		rgbBlockInfo.addOutlet< Image >("ImageData");
		rgbBlockInfo.addOutlet<int>( "Width" );
		rgbBlockInfo.addOutlet<int>( "Height" );
		rgbBlockInfo.addOutlet<double>( "FovHorizontal" );
		rgbBlockInfo.addOutlet<double>( "FovVertical" );
		rgbBlockInfo.setDescription( "OpenNI Kinect Rgb Image Block" );

		BlockMetainfo depthBlockInfo = info.exportBlock< KinectOpenNIDepthBlock, WithContext >( "KinectOpenNIDepthBlock" );
		depthBlockInfo.addInlet<int>( "DeviceIndex", 0 );
		depthBlockInfo.addInlet<int>( "Width", 640 );
		depthBlockInfo.addInlet<int>( "Height", 480 );
		depthBlockInfo.addInlet<int>( "Fps", 30 );
		depthBlockInfo.addInlet<bool>( "IsMirrored", false );
		depthBlockInfo.addInlet<bool>( "IsAlignedToColor", false );
		// 8 bit, 16 bit or point cloud
		depthBlockInfo.addInlet<bool>( "Is16BitImage", true );
		depthBlockInfo.addInlet<bool>( "IsPointCloud", false );
		depthBlockInfo.addOutlet< Image >("ImageData");
		depthBlockInfo.addOutlet<int>( "Width" );
		depthBlockInfo.addOutlet<int>( "Height" );
		depthBlockInfo.addOutlet<double>( "FovHorizontal" );
		depthBlockInfo.addOutlet<double>( "FovVertical" );
		depthBlockInfo.setDescription( "OpenNI Kinect Depth Image Block" );

		BlockMetainfo userSkeletonBlockInfo = info.exportBlock< KinectOpenNIUserSkeletonBlock, WithContext >( "KinectOpenNIUserSkeletonBlock" );
		userSkeletonBlockInfo.addInlet<int>( "DeviceIndex", 0 );
		userSkeletonBlockInfo.addInlet<int>( "Width", 640 );
		userSkeletonBlockInfo.addInlet<int>( "Height", 480 );
		userSkeletonBlockInfo.addInlet<int>( "Fps", 30 );
		userSkeletonBlockInfo.addInlet<bool>( "IsMirrored", false );
		userSkeletonBlockInfo.addInlet<bool>( "IsAlignedToColor", false );
		userSkeletonBlockInfo.addInlet<bool>( "IsWorldCoordinates", false );
		userSkeletonBlockInfo.addOutlet< Image >("ImageData");
		userSkeletonBlockInfo.addOutlet<int>( "Width" );
		userSkeletonBlockInfo.addOutlet<int>( "Height" );
		userSkeletonBlockInfo.addOutlet<double>( "FovHorizontal" );
		userSkeletonBlockInfo.addOutlet<double>( "FovVertical" );
		userSkeletonBlockInfo.addOutlet<std::vector<Point>>( "UsersCenterOfMass" );
		userSkeletonBlockInfo.addOutlet< std::vector< Skeleton > >( "Skeletons" );
		userSkeletonBlockInfo.addOutlet<int>( "NrOfUsers" );
		userSkeletonBlockInfo.addOutlet<int>( "NrOfSkeletons" );

		userSkeletonBlockInfo.setDescription( "OpenNI Kinect User/Skeleton Image Block" );

		BlockMetainfo irBlockInfo = info.exportBlock< KinectOpenNIIrBlock, WithContext >( "KinectOpenNIIrBlock" );
		irBlockInfo.addInlet<int>( "DeviceIndex", 0 );
		irBlockInfo.addInlet<int>( "Width", 640 );
		irBlockInfo.addInlet<int>( "Height", 480 );
		irBlockInfo.addInlet<int>( "Fps", 30 );
		irBlockInfo.addInlet<bool>( "IsMirrored", false );
		irBlockInfo.addOutlet< Image >("ImageData");
		irBlockInfo.addOutlet<int>( "Width" );
		irBlockInfo.addOutlet<int>( "Height" );
		irBlockInfo.addOutlet<double>( "FovHorizontal" );
		irBlockInfo.addOutlet<double>( "FovVertical" );
		irBlockInfo.setDescription( "OpenNI Kinect Infrared Image Block" );

		BlockMetainfo motorBlockInfo = info.exportBlock< KinectOpenNIMotorBlock, WithContext >( "KinectOpenNIMotorBlock" );
		motorBlockInfo.addInlet<int>( "DeviceIndex", 0 );
		motorBlockInfo.addInlet<int>( "Angle", 0 );
		motorBlockInfo.addOutlet<int>("Angle");
		motorBlockInfo.setDescription( "OpenNI Kinect Motor Control Block" );
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
}