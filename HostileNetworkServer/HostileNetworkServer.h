#ifndef HOSTILENETWORKSERVER
#define HOSTILENETWORKSERVER

//#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

SOCKET LaunchServer();

#endif