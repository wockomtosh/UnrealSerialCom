
#include <iostream>

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#include "SerialComPortTestClass.h"

void PrintCommState(DCB dcb)
{
    //  Print some of the DCB structure values
    _tprintf(TEXT("\nBaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d\n"),
        dcb.BaudRate,
        dcb.ByteSize,
        dcb.Parity,
        dcb.StopBits);
}

void SerialTest()
{
    DCB dcb;
    HANDLE hCom;
    bool fSuccess;
    const wchar_t* pcCommPort = TEXT("COM7"); //Our current port

    //Open a handle to our com port
    hCom = CreateFile(pcCommPort,
        GENERIC_READ | GENERIC_WRITE,
        0, //No sharing
        NULL, //Default security attributes
        OPEN_EXISTING, //Must use this
        0, //not overlapped I/O     TO BE ASYNC WE NEED OVERLAPPED
        NULL); //Template must be NULL for comm devices

    if (hCom == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile failed with error %d.\n", GetLastError());
        return;
    }

    // Initialize the DCB structure.
    SecureZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);

    // Build on the current configuration by first retrieving all current settings.
    fSuccess = GetCommState(hCom, &dcb);
    if (!fSuccess)
    {
        //  Handle the error.
        printf("GetCommState failed with error %d.\n", GetLastError());
        return;
    }

    //  Fill in some DCB values and set the com state: 
    //  9600 bps, 8 data bits, no parity, and 1 stop bit.
    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;

    fSuccess = SetCommState(hCom, &dcb);

    if (!fSuccess)
    {
        printf("SetCommState failed with error %d.\n", GetLastError());
        return;
    }

    PrintCommState(dcb);

    COMMTIMEOUTS timeout;
    SecureZeroMemory(&timeout, sizeof(COMMTIMEOUTS));

    timeout.ReadIntervalTimeout = 1;
    timeout.ReadTotalTimeoutMultiplier = 0; //This says that the total timeout is X ms per byte
    timeout.ReadTotalTimeoutConstant = 0; //This is added to the multiplier
    SetCommTimeouts(hCom, &timeout);

    _tprintf(TEXT("Serial port %s successfully reconfigured.\n"), pcCommPort);

    LPVOID lpBuffer = calloc(8, sizeof(char));
    DWORD numBytes = 7; //If we output a line of 5 chars, the string also has a newline char and a null terminator, so we need 7
    LPDWORD lpBytesRead = static_cast<LPDWORD>(malloc(sizeof(DWORD))); 
    bool rSuccess = true;

    //read loop
    while (rSuccess)
    {
        rSuccess = ReadFile(hCom, lpBuffer, numBytes, lpBytesRead, NULL);
        std::cout << static_cast<char*>(lpBuffer) << std::endl;
    }

    CloseHandle(hCom);
}

void SerialClassTest()
{
    bool opened;
    USerialComPort* port;
    for (int i = 1; i <= 8; i++)
    {
        port = USerialComPort::OpenComPort(opened, i);

        if (opened)
        {
            printf("Port %d opened successfully!\n", i);            
            break;
        }
        printf("Port %d didn't open\n", i);
    }
    
    port->Flush();
    printf(port->ReadLine().c_str());
    printf(port->ReadLine().c_str());
    printf(port->ReadLine().c_str());
    printf(port->ReadLine().c_str());
    printf(port->ReadLine().c_str());

    port->Close();
    printf("Port closed\n");
}

int main()
{
    //Select which of these to use based on if I'm testing the communication directly or testing the class
    SerialClassTest();

    //SerialTest();
}