#include <iostream>
#include <string>
#include <sstream>
#include "KinectOpenNIDepthBlock.h"
#include "_2RealDatatypes.h"

using namespace _2Real;
using _2Real::bundle::BlockHandle;
using _2Real::Exception;
using std::cout;
using std::endl;
using std::string;

void KinectOpenNIDepthBlock::setup( BlockHandle &block )
{
	// set generator type so base class object works on that generator, this inheritance helps avoid useless codeduplicatio, you could use templates as well
	setGeneratorType(_2RealKinectWrapper::DEPTHIMAGE);
	KinectOpenNIBlockBase::setup(block);
	m_IsAlignedToColorInletHandle = block.getInletHandle("IsAlignedToColor");
	m_bIsAlignedToColor = m_IsAlignedToColorInletHandle.getReadableRef<bool>();
}

void KinectOpenNIDepthBlock::update()
{
	try
	{
		if(m_OpenNIDeviceManager->getNumberOfConnectedDevices()<=0)	// if there is no cameras connected there is nothing todo so return
			return;

		bool bIsAlignedToColor = m_IsAlignedToColorInletHandle.getReadableRef<bool>();
		if( bIsAlignedToColor != m_bIsAlignedToColor)
		{
			if(m_iCurrentDevice!=-1)
				m_OpenNIDeviceManager->setAlignToColor(m_iCurrentDevice, bIsAlignedToColor);
			m_bIsAlignedToColor = bIsAlignedToColor;
		}

		// call update of base class
		KinectOpenNIBlockBase::update();

	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
}