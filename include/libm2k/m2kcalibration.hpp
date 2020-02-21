/*
 * Copyright (c) 2019 Analog Devices Inc.
 *
 * This file is part of libm2k
 * (see http://www.github.com/analogdevicesinc/libm2k).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef M2KCALIBRATION_HPP
#define M2KCALIBRATION_HPP

#include <libm2k/m2kglobal.hpp>
#include <libm2k/m2khardwaretrigger.hpp>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <map>

namespace libm2k {

class LIBM2K_API M2kCalibration
{
public:
	M2kCalibration(struct iio_context* ctx, libm2k::analog::M2kAnalogIn* analogIn,
		       libm2k::analog::M2kAnalogOut* analogOut, libm2k::analog::DMM *dmm);
	virtual ~M2kCalibration();

	bool initialize();
	bool isInitialized() const;

	void setAdcInCalibMode();
	void setDacInCalibMode();
	void restoreAdcFromCalibMode();
	void restoreDacFromCalibMode();

	bool calibrateAll();
	bool calibrateADC();
	bool calibrateADCoffset();
	bool calibrateADCgain();
	bool calibrateDAC();
	bool calibrateDACoffset();
	bool calibrateDACgain();
	void cancelCalibration();

	int adcOffsetChannel0() const;
	int adcOffsetChannel1() const;
	int dacAoffset() const;
	int dacBoffset() const;
	double adcGainChannel0() const;
	double adcGainChannel1() const;
	double dacAvlsb() const;
	double dacBvlsb() const;

	bool resetCalibration();
	void updateAdcCorrections();
	void updateDacCorrections();

	bool setCalibrationMode(int);

	std::pair<double, std::map<libm2k::CALIBRATION_PARAMETER, double>> getCalibrationParameters();
	void setCalibrationParameters(std::map<libm2k::CALIBRATION_PARAMETER, double> &calibrationParameters);
	bool calibrateADC(const std::string &serialNumber, const std::string &path = std::string());
	bool calibrateDAC(const std::string &serialNumber, const std::string &path = std::string());
	bool calibrateAll(const std::string &serialNumber, const std::string &path = std::string());


protected:
	class M2kCalibrationImpl;
	std::unique_ptr<M2kCalibrationImpl> m_pimpl;
};

}

#endif /* M2KCALIBRATION_HPP */
