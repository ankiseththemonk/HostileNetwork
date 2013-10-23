#ifndef HOSTILENETWORKCLIENT
#define HOSTILENETWORKCLIENT

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

bool FileExists(string fileName);
SOCKET ConnectToServer();

#endif