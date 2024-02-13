//// Fill out your copyright notice in the Description page of Project Settings.
//
//// Parts of the code for this are based off of this plugin: https://github.com/videofeedback/Unreal_Engine_SerialCOM_Plugin
//// Other resources used include the following:
//// Windows API documentation
//// https://learn.microsoft.com/en-us/windows/win32/devio/configuring-a-communications-resource
//// https://stackoverflow.com/questions/15794422/serial-port-rs-232-connection-in-c
//// http://hdrlab.org.nz/articles/windows-development/a-c-class-for-controlling-a-comm-port-in-windows/
//
//#pragma once
//
//#define FLUSH_BUFFER_SIZE 1024
//
//#include <Windows.h>
//#include "CoreMinimal.h"
//
//#include "SerialComPort.generated.h"
//
//
///**
// * The Serial Port data type to be used to manage opened serial ports
// */
//UCLASS(BlueprintType, Category = "Serial")
//class BACKOFFMEBOOTY_API USerialComPort : public UObject
//{
//	GENERATED_BODY()
//
//protected:
//	HANDLE hCom;
//	int portNumber;
//	//I'll need overlapped structs later for async?
//
//public:
//	USerialComPort();
//	~USerialComPort();
//	
//	UFUNCTION(BlueprintPure)
//	bool IsOpened();
//
//	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Serial Port"))
//	bool Open(int port);
//
//	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Close Serial Port"))
//	void Close();
//
//	/*
//	* This Function doesn't actually read a line currently, it reads the number of bytes that I want it to read.
//	*/
//	UFUNCTION(BlueprintCallable)
//	FString ReadLine();
//
//	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Flush Serial Port"))
//	void Flush();
//
//	//Later we may want write functions
//
//	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Serial Port"))
//	static USerialComPort* OpenComPort(bool& bOpened, int portNumber);
//};
