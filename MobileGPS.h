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

#if !defined(MobileGPS_H)
#define	MobileGPS_H

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

#include <string>

class CMobileGPS
{
public:
	CMobileGPS(const std::string& file);
	~CMobileGPS();

	void run();

private:
	std::string m_file;

	bool        m_debug;

	unsigned char* m_data;
	unsigned int   m_offset;
	bool           m_collect;

	char* m_latitude;
	char* m_latitudeNS;
	char* m_longitude;
	char* m_longitudeEW;
	float m_altitude;
	float m_speed;
	float m_bearing;

	void interpret(const unsigned char* data, unsigned int length);
	bool checkXOR(const unsigned char* data, unsigned int length) const;
	unsigned char calcXOR(const unsigned char* buffer, unsigned int length) const;
	void processGGA();
	void processRMC();
	char* mystrsep(char** sp, const char* sep) const;
};

#endif
