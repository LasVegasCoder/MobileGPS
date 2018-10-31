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

#if !defined(CONF_H)
#define	CONF_H

#include <string>
#include <vector>

class CConf
{
public:
  CConf(const std::string& file);
  ~CConf();

  bool read();

  // The General section
  unsigned int getMinDistance() const;
  unsigned int getMinTime() const;
  unsigned int getMaxTime() const;
  bool         getDebug() const;
  bool         getDaemon() const;

  // The Log section
  std::string  getLogFilePath() const;
  std::string  getLogFileRoot() const;

  // The GPS section
  std::string  getGPSPort() const;
  unsigned int getGPSSpeed() const;
  bool         getGPSDebug() const;

  // The Network section
  std::string  getNetworkAddress() const;
  unsigned int getNetworkPort() const;
  bool         getNetworkDebug() const;

private:
  std::string  m_file;
  unsigned int m_minDistance;
  unsigned int m_minTime;
  unsigned int m_maxTime;
  bool         m_debug;
  bool         m_daemon;

  std::string  m_logFilePath;
  std::string  m_logFileRoot;

  std::string  m_gpsPort;
  unsigned int m_gpsSpeed;
  bool         m_gpsDebug;

  std::string  m_networkAddress;
  unsigned int m_networkPort;
  bool         m_networkDebug;
};

#endif
