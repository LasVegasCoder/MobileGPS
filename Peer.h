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

#if !defined(Peer_H)
#define	Peer_H

#if !defined(_WIN32) && !defined(_WIN64)
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <winsock.h>
#endif

#include "Timer.h"


class CPeer
{
public:
	CPeer(unsigned int minTime, unsigned int maxTime, unsigned int minDistance, const in_addr& address, unsigned int port);

	bool canReport(float latitude, float longitude);

	void hasReported(float latitude, float longitude);

	void clock(unsigned int ms);

	in_addr      m_address;
	unsigned int m_port;

private:
	CTimer m_minTimer;
	CTimer m_maxTimer;
	float  m_minDistance;
	float  m_lastLatitude;
	float  m_lastLongitude;
};

#endif
