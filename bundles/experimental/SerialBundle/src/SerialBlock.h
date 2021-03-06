#pragma once

#include "_2realblock.h"

#include "SerialDeviceManager.h"

/*
class SerialBlock

Defines the Serialput Block --> Via a Serial Input Port the Serial Messages are sent through three Outlets.
*/
class SerialBlock : public _2Real::bundle::Block
{
public:
	SerialBlock( _2Real::bundle::ContextBlock & context );
	virtual ~SerialBlock();

	// Virtual Methods
	virtual void					update();
	virtual void					setup( _2Real::bundle::BlockHandle &context );
	virtual void					shutdown();

private:
	void							discardAllOutlets();

	// The Block Inlets 
	_2Real::bundle::InletHandle	m_SerialPortInlet;
	_2Real::bundle::InletHandle m_iBaudRateInlet;
	_2Real::bundle::InletHandle m_DataInIntel;

	// The Block Outlets
	_2Real::bundle::OutletHandle m_DataOutOutlet;
	
	// The SerialDevice Manager
	SerialDeviceManager*		m_SerialDeviceManager;

	// internal binding status
	bool m_bBound;
	bool m_bBindable;

	// current active serial identifier (empty string means none)
	std::string m_SerialIdentifer;

	std::vector<unsigned char> m_SerialMessage;
};
