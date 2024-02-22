# UnrealSerialCom
A testing area for opening serial ports for an arduino to communicate with Unreal Engine

The TestClass files are NOT Unreal classes, I used them to test my changes in plain C++

The SerialComPort.h and SerialComPort.cpp classes are the ones I'm using in Unreal

To actually run SerialTest.cpp you need to comment out the Unreal files since they will cause build errors



Parts of the code for this are based off of this plugin: https://github.com/videofeedback/Unreal_Engine_SerialCOM_Plugin


Other resources used include the following:

Windows API documentation

https://learn.microsoft.com/en-us/windows/win32/devio/configuring-a-communications-resource

https://stackoverflow.com/questions/15794422/serial-port-rs-232-connection-in-c

http://hdrlab.org.nz/articles/windows-development/a-c-class-for-controlling-a-comm-port-in-windows/
