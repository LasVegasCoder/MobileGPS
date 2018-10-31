/*
*   Copyright (C) 2018 by Jonathan Naylor G4KLX
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "Peer.h"

#include <cmath>
#include <cassert>

const float R = 6371.0F;

float DEG2RAD(float x)
{
	return M_PI * x / 180.0F;
}

CPeer::CPeer(unsigned int minTime, unsigned int maxTime, unsigned int minDistance, const in_addr& address, unsigned int port) :
m_address(address),
m_port(port),
m_minTimer(1000U, minTime),
m_maxTimer(1000U, maxTime),
m_minDistance(float(minDistance) / 1000.0F),
m_lastLatitude(0.0F),
m_lastLongitude(0.0F)
{
	assert(port > 0U);
}

bool CPeer::canReport(float latitude, float longitude)
{
	if (!m_minTimer.hasExpired())
		return false;

	if (m_maxTimer.hasExpired())
		return true;

	float lat1r = DEG2RAD(m_lastLatitude);
	float lon1r = DEG2RAD(m_lastLongitude);
	float lat2r = DEG2RAD(latitude);
	float lon2r = DEG2RAD(longitude);

	float u = ::sin((lat2r - lat1r) / 2.0F);
	float v = ::sin((lon2r - lon1r) / 2.0F);
	
	float distance = 2.0F * R * ::asin(::sqrt(u * u + ::cos(lat1r) * ::cos(lat2r) * v * v));

	return distance >= m_minDistance;
}

void CPeer::hasReported(float latitude, float longitude)
{
	m_minTimer.start();
	m_maxTimer.start();

	m_lastLatitude  = latitude;
	m_lastLongitude = longitude;
}

void CPeer::clock(unsigned int ms)
{
	m_minTimer.clock(ms);
	m_maxTimer.clock(ms);
}
