#include "stdafx.h"
#include "HostileNetworkClient.h"

using namespace std;

#pragma comment(lib, "Ws2_32.lib") //links to WinSock library

int main(int argc, char* argv[]) {

	string command = argv[1];
	string fileName = argv[2];

	//check for any command besides "get", "send", and "dir"
	if (!(command == "send" || command == "get" || command == "dir")) {
		cout << "Invalid parameters. Usage: program.exe <get|send> filename.txt" << endl;
		exit(-1);
	}

	//if user is trying to send a file, make sure file is specified && file exists
	if (command == "send") {
		if (fileName.empty()) {
			cout << "Invalid parameters. Usage: program.exe <get|send> filepath\filename.txt" << endl;
			exit(-1);
		} else if (!FileExists(fileName)) {
			cout << "File does not exist." << endl;
			exit(-1);
		}
	}

	//create connection to server
	if(ConnectToServer() != NULL)
		cout << "Connected to server successfully." << endl;
	else
		cout << "Failed to connect to server." << endl;


	int a;
	cin >> a;

	return 0;
}

bool FileExists(string fileName) {

	ifstream f(fileName.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

/// <summary>
/// This function opens a socket to the server and returns the socket if successful, NULL otherwise.
/// </summary>
SOCKET ConnectToServer() {

	#define DEFAULT_PORT "58008"

	WSADATA wsaData;
	int iResult;
	PCSTR serverIP = "localhost";

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return NULL;
	}

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return NULL;
	}

	// Create a SOCKET for connecting to server
	SOCKET ConnectSocket = INVALID_SOCKET;
	ptr=result;

	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return NULL;
	}

	//Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		return NULL;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return NULL;
	}

	return ConnectSocket;
}

