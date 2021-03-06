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

#include "private/devicegeneric_impl.cpp"

using namespace std;
using namespace libm2k::utils;
using namespace libm2k::contexts;

/*
 * Represents an iio_DeviceGeneric
 */
DeviceGeneric::DeviceGeneric(struct iio_context* context, std::string dev_name) :
	m_pimpl(std::unique_ptr<DeviceGenericImpl>(new DeviceGenericImpl(context, dev_name)))
{
}

DeviceGeneric::DeviceGeneric(DeviceGeneric::DeviceGenericImpl *impl)
{
	m_pimpl = std::unique_ptr<DeviceGenericImpl>(impl);
}

DeviceGeneric::~DeviceGeneric()
{
}

Channel* DeviceGeneric::getChannel(unsigned int chnIdx, bool output)
{
	return m_pimpl->getChannel(chnIdx, output);
}

Channel* DeviceGeneric::getChannel(std::string id, bool output)
{
	return m_pimpl->getChannel(id, output);
}

bool DeviceGeneric::isChannel(unsigned int chnIdx, bool output)
{
	return m_pimpl->isChannel(chnIdx, output);
}

void DeviceGeneric::enableChannel(unsigned int chnIdx, bool enable, bool output)
{
	m_pimpl->enableChannel(chnIdx, enable, output);
}

bool DeviceGeneric::isChannelEnabled(unsigned int chnIdx, bool output)
{
	return m_pimpl->isChannelEnabled(chnIdx, output);
}

string DeviceGeneric::getName()
{
	return m_pimpl->getName();
}

double DeviceGeneric::getDoubleValue(std::string attr)
{
	return m_pimpl->getDoubleValue(attr);
}

double DeviceGeneric::getDoubleValue(unsigned int chn_idx, std::string attr, bool output)
{
	return m_pimpl->getDoubleValue(chn_idx, attr, output);
}

double DeviceGeneric::setDoubleValue(double value, std::string attr)
{
	return m_pimpl->setDoubleValue(value, attr);
}

double DeviceGeneric::setDoubleValue(unsigned int chn_idx, double value, std::string attr, bool output)
{
	return m_pimpl->setDoubleValue(chn_idx, value, attr, output);
}

int DeviceGeneric::getLongValue(string attr)
{
	return m_pimpl->getLongValue(attr);
}

int DeviceGeneric::getLongValue(unsigned int chn_idx, string attr, bool output)
{
	return m_pimpl->getLongValue(chn_idx, attr, output);
}

int DeviceGeneric::getBufferLongValue(std::string attr)
{
	return m_pimpl->getBufferLongValue(attr);
}

int DeviceGeneric::setLongValue(int value, string attr)
{
	return m_pimpl->setLongValue(value, attr);
}

int DeviceGeneric::setLongValue(unsigned int chn_idx, int value, string attr, bool output)
{
	return m_pimpl->setLongValue(chn_idx, value, attr, output);
}

int DeviceGeneric::setBufferLongValue(int value, std::string attr)
{
	return m_pimpl->setBufferLongValue(value, attr);
}

bool DeviceGeneric::getBoolValue(string attr)
{
	return m_pimpl->getBoolValue(attr);
}

bool DeviceGeneric::getBoolValue(unsigned int chn_idx, string attr, bool output)
{
	return m_pimpl->getBoolValue(chn_idx, attr, output);
}

bool DeviceGeneric::setBoolValue(bool value, string attr)
{
	return m_pimpl->setBoolValue(value, attr);
}

bool DeviceGeneric::setBoolValue(unsigned int chn_idx, bool value, string attr, bool output)
{
	return m_pimpl->setBoolValue(chn_idx, value, attr, output);
}

string DeviceGeneric::setStringValue(string attr, string value)
{
	return m_pimpl->setStringValue(attr, value);
}

string DeviceGeneric::setStringValue(unsigned int chn_idx, string attr, string value, bool output)
{
	return m_pimpl->setStringValue(chn_idx, attr, value, output);
}

string DeviceGeneric::getStringValue(string attr)
{
	return m_pimpl->getStringValue(attr);
}

string DeviceGeneric::getStringValue(unsigned int chn_idx, string attr, bool output)
{
	return m_pimpl->getStringValue(chn_idx, attr, output);
}

std::vector<double> DeviceGeneric::getAvailableSampleRates()
{
	return m_pimpl->getAvailableSampleRates();
}

void DeviceGeneric::writeRegister(uint32_t address, uint32_t value)
{
	m_pimpl->writeRegister(address, value);
}

std::string DeviceGeneric::getHardwareRevision()
{
	return m_pimpl->getHardwareRevision();
}

unsigned int DeviceGeneric::getNbChannels(bool output)
{
	return m_pimpl->getNbChannels(output);
}

void DeviceGeneric::convertChannelHostFormat(unsigned int chn_idx, int16_t *avg, int16_t *src, bool output)
{
	m_pimpl->convertChannelHostFormat(chn_idx, avg, src, output);
}

void DeviceGeneric::convertChannelHostFormat(unsigned int chn_idx, double *avg, int16_t *src, bool output)
{
	m_pimpl->convertChannelHostFormat(chn_idx, avg, src, output);
}

void DeviceGeneric::setKernelBuffersCount(unsigned int count)
{
	m_pimpl->setKernelBuffersCount(count);
}

bool DeviceGeneric::isValidDmmChannel(unsigned int chnIdx)
{
	return m_pimpl->isValidDmmChannel(chnIdx);
}

std::pair<string, string> DeviceGeneric::getContextAttr(unsigned int attrIdx)
{
	return m_pimpl->getContextAttr(attrIdx);
}

void DeviceGeneric::setCyclic(bool en)
{
	m_pimpl->setCyclic(en);
}
