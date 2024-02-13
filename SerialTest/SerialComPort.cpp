//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "SerialComPort.h"
//
//USerialComPort::USerialComPort() :
//	hCom(nullptr), portNumber(-1)
//{
//	//Allocate overlapped structs if we get there
//}
//
//USerialComPort::~USerialComPort()
//{
//	Close();
//
//	//Delete overlapped structs if we get there
//}
//
//bool USerialComPort::IsOpened()
//{
//	return hCom != nullptr;
//}
//
//bool USerialComPort::Open(int port)
//{
//	const int BUF_SIZE = 5;
//	wchar_t* wstrBuf = static_cast<wchar_t*>(calloc(BUF_SIZE, sizeof(wchar_t)));
//	swprintf(wstrBuf, BUF_SIZE, L"%s%d", L"COM", port);
//
//	DCB dcb;
//	bool fSuccess;
//
//	//Open a handle to our com port
//	hCom = CreateFile(wstrBuf,
//		GENERIC_READ | GENERIC_WRITE,
//		0, //No sharing
//		NULL, //Default security attributes
//		OPEN_EXISTING, //Must use this
//		0, //not overlapped I/O     TO BE ASYNC WE NEED OVERLAPPED STRUCTS
//		NULL); //Template must be NULL for comm devices
//
//	if (hCom == INVALID_HANDLE_VALUE)
//	{
//		//TODO: Handle errors
//		hCom = nullptr;
//		return false;
//	}
//
//    // Initialize the DCB structure.
//    SecureZeroMemory(&dcb, sizeof(DCB));
//    dcb.DCBlength = sizeof(DCB);
//
//    // Build on the current configuration by first retrieving all current settings.
//    fSuccess = GetCommState(hCom, &dcb);
//    if (!fSuccess)
//    {
//        //TODO: Handle the error.
//		hCom = nullptr;
//        return false;
//    }
//
//    //  Fill in some DCB values and set the com state: 
//    //  9600 bps, 8 data bits, no parity, and 1 stop bit.
//    dcb.BaudRate = CBR_9600;
//    dcb.ByteSize = 8;
//    dcb.StopBits = ONESTOPBIT;
//    dcb.Parity = NOPARITY;
//
//    fSuccess = SetCommState(hCom, &dcb);
//
//    if (!fSuccess)
//    {
//		//TODO: Handle the error.
//		hCom = nullptr;
//		return false;
//    }
//
//    COMMTIMEOUTS timeout;
//    SecureZeroMemory(&timeout, sizeof(COMMTIMEOUTS));
//
//    timeout.ReadIntervalTimeout = 1;
//    timeout.ReadTotalTimeoutMultiplier = 0; //This says that the total timeout is X ms per byte
//    timeout.ReadTotalTimeoutConstant = 20; //This is added to the multiplier
//    SetCommTimeouts(hCom, &timeout);
//
//	return true;
//}
//
//void USerialComPort::Close()
//{
//	//Handle the overlappeds here if we get there
//	CloseHandle(hCom);
//	hCom = nullptr;
//
//	//TODO: ???
//	UObjectBaseUtility::RemoveFromRoot();
//}
//
//FString USerialComPort::ReadLine()
//{
//	LPVOID lpBuffer = calloc(8, sizeof(char));
//	DWORD numBytes = 7; //If we output a line of 5 chars, the string also has a newline char and a null terminator, so we need 7
//	LPDWORD lpBytesRead = static_cast<LPDWORD>(malloc(sizeof(DWORD)));
//	bool rSuccess = true;
//
//	rSuccess = ReadFile(hCom, lpBuffer, numBytes, lpBytesRead, NULL);
//
//	return FString(static_cast<char*>(lpBuffer));
//}
//
//void USerialComPort::Flush()
//{
//	//Basically just read a bunch of bytes
//	LPVOID lpBuffer = malloc(FLUSH_BUFFER_SIZE);
//	ReadFile(hCom, lpBuffer, FLUSH_BUFFER_SIZE, NULL, NULL);
//}
//
//USerialComPort* USerialComPort::OpenComPort(bool &bOpened, int portNumber)
//{
//	USerialComPort* serialPort = NewObject<USerialComPort>();
//	bOpened = serialPort->Open(portNumber);
//	return serialPort;
//}
