/*
 *   Copyright (C) 2015,2016,2017,2018 by Jonathan Naylor G4KLX
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

#include "Conf.h"
#include "Log.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

const int BUFFER_SIZE = 500;

enum SECTION {
  SECTION_NONE,
  SECTION_GENERAL,
  SECTION_LOG,
  SECTION_GPS,
  SECTION_NETWORK
};

CConf::CConf(const std::string& file) :
m_file(file),
m_minDistance(0U),
m_minTime(0U),
m_maxTime(0U),
m_debug(false),
m_daemon(false),
m_logFilePath(),
m_logFileRoot(),
m_gpsPort(),
m_gpsSpeed(0U),
m_gpsDebug(false),
m_networkAddress(),
m_networkPort(0U),
m_networkDebug(false)
{
}

CConf::~CConf()
{
}

bool CConf::read()
{
  FILE* fp = ::fopen(m_file.c_str(), "rt");
  if (fp == NULL) {
    ::fprintf(stderr, "Couldn't open the .ini file - %s\n", m_file.c_str());
    return false;
  }

  SECTION section = SECTION_NONE;

  char buffer[BUFFER_SIZE];
  while (::fgets(buffer, BUFFER_SIZE, fp) != NULL) {
	  if (buffer[0U] == '#')
		  continue;

	  if (buffer[0U] == '[') {
		  if (::strncmp(buffer, "[General]", 9U) == 0)
			  section = SECTION_GENERAL;
		  else if (::strncmp(buffer, "[Log]", 5U) == 0)
			  section = SECTION_LOG;
		  else if (::strncmp(buffer, "[GPS]", 5U) == 0)
			  section = SECTION_GPS;
		  else if (::strncmp(buffer, "[Network]", 9U) == 0)
			  section = SECTION_NETWORK;
		  else
			  section = SECTION_NONE;

		  continue;
	  }

	  char* key = ::strtok(buffer, " \t=\r\n");
	  if (key == NULL)
		  continue;

	  char* value = ::strtok(NULL, "\r\n");
	  if (section == SECTION_GENERAL) {
		  if (::strcmp(key, "MinDistance") == 0)
			  m_minDistance = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "MinTime") == 0)
			  m_minTime = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "MaxTime") == 0)
			  m_maxTime = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "Debug") == 0)
			  m_debug = ::atoi(value) == 1;
		  else if (::strcmp(key, "Daemon") == 0)
			  m_daemon = ::atoi(value) == 1;
	  } else if (section == SECTION_LOG) {
		  if (::strcmp(key, "FilePath") == 0)
			  m_logFilePath = value;
		  else if (::strcmp(key, "FileRoot") == 0)
			  m_logFileRoot = value;
	  } else if (section == SECTION_GPS) {
		  if (::strcmp(key, "Port") == 0)
			  m_gpsPort = value;
		  else if (::strcmp(key, "Speed") == 0)
			  m_gpsSpeed = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "Debug") == 0)
			  m_gpsDebug = ::atoi(value) == 1;
	  } else if (section == SECTION_NETWORK) {
		  if (::strcmp(key, "Address") == 0)
			  m_networkAddress = value;
		  else if (::strcmp(key, "Port") == 0)
			  m_networkPort = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "Debug") == 0)
			  m_networkDebug = ::atoi(value) == 1;
	  }
  }

  ::fclose(fp);

  return true;
}

unsigned int CConf::getMinDistance() const
{
	return m_minDistance;
}

unsigned int CConf::getMinTime() const
{
	return m_minTime;
}

unsigned int CConf::getMaxTime() const
{
	return m_maxTime;
}

bool CConf::getDebug() const
{
	return m_debug;
}

bool CConf::getDaemon() const
{
	return m_daemon;
}

std::string CConf::getLogFilePath() const
{
  return m_logFilePath;
}

std::string CConf::getLogFileRoot() const
{
  return m_logFileRoot;
}

std::string CConf::getGPSPort() const
{
	return m_gpsPort;
}

unsigned int CConf::getGPSSpeed() const
{
	return m_gpsSpeed;
}

bool CConf::getGPSDebug() const
{
	return m_gpsDebug;
}

std::string CConf::getNetworkAddress() const
{
	return m_networkAddress;
}

unsigned int CConf::getNetworkPort() const
{
	return m_networkPort;
}

bool CConf::getNetworkDebug() const
{
	return m_networkDebug;
}
