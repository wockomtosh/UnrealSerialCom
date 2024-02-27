//IMPORTANT!!! This class is a copy of the UClass that I'm using for testing in straight cpp


// Parts of the code for this are based off of this plugin: https://github.com/videofeedback/Unreal_Engine_SerialCOM_Plugin
// Other resources used include the following:
// Windows API documentation
// https://learn.microsoft.com/en-us/windows/win32/devio/configuring-a-communications-resource
// https://stackoverflow.com/questions/15794422/serial-port-rs-232-connection-in-c
// http://hdrlab.org.nz/articles/windows-development/a-c-class-for-controlling-a-comm-port-in-windows/

#pragma once

#define FLUSH_BUFFER_SIZE 1024

#include <Windows.h>
#include <string>



/**
 * The Serial Port data type to be used to manage opened serial ports
 */
class USerialComPort
{

protected:
	HANDLE hCom;
	int portNumber;
	//I'll need overlapped structs later for async?
	//After investigating async, for my purposes async doesn't make a lot of sense.
	//If I was reading and loading large files then maybe it would make sense, and there
	//could certainly be issues with synchronous reading, but I think it won't actually change much
	//Since I need the strings to be in order anyways.

public:
	USerialComPort();
	~USerialComPort();

	bool IsOpened();

	bool Open(int port);

	void Close();

	/*
	* This Function doesn't actually read a line currently, it reads the number of bytes that I want it to read.
	*/
	std::string ReadLine();

	void Flush();

	//Later we may want write functions

	static USerialComPort* OpenComPort(bool& bOpened, int portNumber);
};
