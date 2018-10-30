CC      = gcc
CXX     = g++
CFLAGS  = -g -O3 -Wall -std=c++0x -pthread
LIBS    = -lpthread
LDFLAGS = -g

OBJECTS = Conf.o Log.o MobileGPS.o SerialPort.o Thread.o Timer.o UDPSocket.o Utils.o

all:		MobileGPS

MobileGPS:	$(OBJECTS)
		$(CXX) $(OBJECTS) $(CFLAGS) $(LIBS) -o MobileGPS

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

clean:
		$(RM) MobileGPS *.o *.d *.bak *~
 