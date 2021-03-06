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

#include "private/context_impl.cpp"

using namespace libm2k::analog;
using namespace libm2k::digital;
using namespace libm2k::contexts;
using namespace libm2k::utils;

Context::Context(std::string uri, struct iio_context *ctx, std::string name, bool sync) :
	m_pimpl(std::shared_ptr<ContextImpl>(new ContextImpl(uri, ctx, name, sync)))
{
}

Context::Context(ContextImpl* impl)
{
	m_pimpl = std::shared_ptr<ContextImpl>(impl);
}

Context::~Context()
{
}

void Context::init()
{
	m_pimpl->init();
}

void Context::deinitialize()
{
	m_pimpl->deinitialize();
}

unsigned int Context::getAnalogInCount()
{
	return m_pimpl->getAnalogInCount();
}

GenericAnalogIn* Context::getAnalogIn(unsigned int index)
{
	return m_pimpl->getAnalogIn(index);
}

GenericAnalogIn* Context::getAnalogIn(std::string dev_name)
{
	return m_pimpl->getAnalogIn(dev_name);
}

unsigned int Context::getAnalogOutCount()
{
	return m_pimpl->getAnalogOutCount();
}

GenericAnalogOut* Context::getAnalogOut(unsigned int index)
{
	return m_pimpl->getAnalogOut(index);
}

GenericAnalogOut* Context::getAnalogOut(std::string dev_name)
{
	return m_pimpl->getAnalogOut(dev_name);
}

bool Context::iioDevHasAttribute(iio_device* dev, std::string const& attr)
{
	return ContextImpl::iioDevHasAttribute(dev, attr);
}

bool Context::iioDevBufferHasAttribute(iio_device *dev, const std::string &attr)
{
	return ContextImpl::iioDevBufferHasAttribute(dev, attr);
}

std::string Context::getFirmwareVersion()
{
	return m_pimpl->getFirmwareVersion();
}

bool Context::iioChannelHasAttribute(iio_channel* chn, std::string const& attr)
{
	return ContextImpl::iioChannelHasAttribute(chn, attr);
}

std::unordered_set<std::string> Context::getAllDevices()
{
	return m_pimpl->getAllDevices();
}

std::vector<std::string> Context::scanAllAnalogIn()
{
	return m_pimpl->scanAllAnalogIn();
}

std::vector<std::string> Context::scanAllAnalogOut()
{
	return m_pimpl->scanAllAnalogOut();
}

void Context::scanAllDMM()
{
	m_pimpl->scanAllDMM();
}

unsigned int Context::getDmmCount()
{
	return m_pimpl->getDmmCount();
}

DMM* Context::getDMM(std::string dev_name)
{
	return m_pimpl->getDMM(dev_name);
}


DMM* Context::getDMM(unsigned int index)
{
	return m_pimpl->getDMM(index);
}

std::vector<DMM*> Context::getAllDmm()
{
	return m_pimpl->getAllDmm();
}

std::vector<std::string> Context::getAvailableContextAttributes()
{
	return m_pimpl->getAvailableContextAttributes();
}

std::string Context::getContextAttributeValue(std::string attr)
{
	return m_pimpl->getContextAttributeValue(attr);
}

std::string Context::getContextDescription()
{
	return m_pimpl->getContextDescription();
}

std::string Context::getSerialNumber()
{
	return m_pimpl->getSerialNumber();
}

M2k* Context::toM2k()
{
	return m_pimpl->toM2k(this);
}

std::string Context::getUri()
{
	return m_pimpl->getUri();
}

void libm2k::contexts::Context::scanAllPowerSupply()
{
	m_pimpl->scanAllPowerSupply();
}

void libm2k::contexts::Context::scanAllDigital()
{
	m_pimpl->scanAllDigital();
}
