/*
 * Copyright 2018 Analog Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file LICENSE.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "libm2k/m2k.hpp"
#include "libm2k/m2kanalogin.hpp"
#include "libm2k/m2kanalogout.hpp"
#include "libm2k/m2kexceptions.hpp"
#include "libm2k/m2kcalibration.hpp"
#include "utils.hpp"
#include <iio.h>
#include <iostream>

using namespace std;
using namespace libm2k::devices;
using namespace libm2k::analog;
using namespace libm2k::utils;

M2K::M2K(std::string uri, iio_context* ctx, std::string name) :
	GenericDevice(uri, ctx, name)
{
	std::cout << "I am M2K device " << std::endl;

	initialize();

	/* Initialize the AnalogIn list */
	for (auto aIn : s_instancesAnalogIn) {
		delete aIn;
	}
	s_instancesAnalogIn.clear();

	/* Initialize the AnalogOut list */
	for (auto aOut : s_instancesAnalogOut) {
		delete aOut;
	}
	s_instancesAnalogOut.clear();

	scanAllAnalogIn();
	scanAllAnalogOut();
	std::vector<libm2k::analog::M2kAnalogIn*> lstIn = getAllAnalogIn();
	std::vector<libm2k::analog::M2kAnalogOut*> lstOut = getAllAnalogOut();
	m_calibration = new M2kCalibration(lstIn, lstOut);
}

M2K::~M2K()
{

}

void M2K::scanAllAnalogIn()
{
	try {
		GenericAnalogIn* aIn = new libm2k::analog::M2kAnalogIn(ctx(), "m2k-adc");
		s_instancesAnalogIn.push_back(aIn);
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}

void M2K::scanAllAnalogOut()
{
	try {
		GenericAnalogOut* aOut = new libm2k::analog::M2kAnalogOut(ctx(), "m2k-dac-a");
		s_instancesAnalogOut.push_back(aOut);

		GenericAnalogOut* bOut = new libm2k::analog::M2kAnalogOut(ctx(), "m2k-dac-b");
		s_instancesAnalogOut.push_back(bOut);
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}

void M2K::calibrate()
{

}

bool M2K::resetCalibration()
{
	try {
		return m_calibration->resetCalibration();
	} catch (std::runtime_error &e) {
		throw std::runtime_error(e.what());
	}
}

bool M2K::calibrateADC()
{
	try {
		return m_calibration->calibrateADC();
	} catch (std::runtime_error &e) {
		throw std::runtime_error(e.what());
	}
}

bool M2K::calibrateDAC()
{
	try {
		return m_calibration->calibrateDAC();
	} catch (std::runtime_error &e) {
		throw std::runtime_error(e.what());
	}
}

M2kAnalogIn* M2K::getAnalogIn(unsigned int index)
{
	if (index < s_instancesAnalogIn.size()) {
		return dynamic_cast<libm2k::analog::M2kAnalogIn*>(
					s_instancesAnalogIn.at(index));
	} else {
		throw no_device_exception("No such analog in");
//		return nullptr;
	}
}

M2kAnalogIn *M2K::getAnalogIn(string dev_name)
{
	for (GenericAnalogIn* d : s_instancesAnalogIn) {
		if (d->getDeviceName() == dev_name) {
			libm2k::analog::M2kAnalogIn* analogIn =
				dynamic_cast<libm2k::analog::M2kAnalogIn*>(d);
			if (analogIn) {
				return analogIn;
			}
		}
	}
	return nullptr;
}

M2kAnalogOut *M2K::getAnalogOut(string dev_name)
{
	for (GenericAnalogOut* d : s_instancesAnalogOut) {
		if (d->getDeviceName() == dev_name) {
			libm2k::analog::M2kAnalogOut* analogOut =
				dynamic_cast<libm2k::analog::M2kAnalogOut*>(d);
			if (analogOut) {
				return analogOut;
			}
		}
	}
	return nullptr;
}

std::vector<M2kAnalogIn*> M2K::getAllAnalogIn()
{
	std::vector<libm2k::analog::M2kAnalogIn*> allAnalogIn = {};
	for (GenericAnalogIn* inst : s_instancesAnalogIn) {
		try {
			libm2k::analog::M2kAnalogIn* analogIn =
				dynamic_cast<libm2k::analog::M2kAnalogIn*>(inst);
			if (analogIn) {
				allAnalogIn.push_back(analogIn);
			}
		} catch (std::runtime_error &e) {
			throw no_device_exception(e.what());
		}
	}
	return allAnalogIn;
}

std::vector<M2kAnalogOut*> M2K::getAllAnalogOut()
{
	std::vector<libm2k::analog::M2kAnalogOut*> allAnalogOut;
	for (GenericAnalogOut* inst : s_instancesAnalogOut) {
		try {
			libm2k::analog::M2kAnalogOut* analogOut =
				dynamic_cast<libm2k::analog::M2kAnalogOut*>(inst);
			if (analogOut) {
				allAnalogOut.push_back(analogOut);
			}
		} catch (std::runtime_error &e) {
			throw no_device_exception(e.what());
		}
	}
	return allAnalogOut;
}

void M2K::initialize()
{
	/* Apply M2k fixes */
	std::string hw_rev = Utils::getHardwareRevision(ctx());

	struct iio_device *dev = iio_context_find_device(ctx(), "ad9963");

	int config1 = 0x05;
	int config2 = 0x05;

	if (hw_rev == "A") {
		config1 = 0x1B; // IGAIN1 +-6db  0.25db steps
		config2 = 0x1B;
	}

	/* Configure TX path */
	iio_device_reg_write(dev, 0x68, config1);
	iio_device_reg_write(dev, 0x6B, config2);
	iio_device_reg_write(dev, 0x69, 0x1C);  // IGAIN2 +-2.5%
	iio_device_reg_write(dev, 0x6C, 0x1C);
	iio_device_reg_write(dev, 0x6A, 0x20);  // IRSET +-20%
	iio_device_reg_write(dev, 0x6D, 0x20);
}
