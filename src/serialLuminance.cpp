// serialLuminance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "serialLuminance.h"

#define LINE_BUFFER_LENGTH 16

static DCB dcb;
static HANDLE hSerial;
static BOOL fSuccess;
static char lineBuffer[LINE_BUFFER_LENGTH];

int readSensorValue(int index)
{
	char tx =(48+index) & 0xFF;
	DWORD numberOfBytesWritten=0;
	WriteFile(hSerial, &tx, 1, &numberOfBytesWritten, NULL);
	if(numberOfBytesWritten < 1)
		return -2;
	int result = readLine();
	if(result < 1)
		return result;
	return atoi(lineBuffer);
}
static int readLine()
{
	int count=0;
	DWORD numberOfBytesRead;
	char newChar;
	do
	{
		ReadFile(hSerial, &newChar, 1, &numberOfBytesRead, NULL);
		if(numberOfBytesRead < 1)
			return -1;
		lineBuffer[count++]=newChar;
	}while(newChar!='\n' || count>=LINE_BUFFER_LENGTH);
	lineBuffer[count++]=0;
	return count;
}
int initialize()
{
	WCHAR comName[5] = L"COM0";
	char test='0';
	int result;

	for(test='0'; test<='9'; test++)
	{
		comName[3]=test;
		printf_s("trying to open COM%c\n",test);
		result=openAndTestSerialPort(comName);
		if(!result)
			return test-'0';
	}
	return -1;
}
static int openAndTestSerialPort(WCHAR* portName)
{
	int result;
	char received[2];
	DWORD numberOfBytes;

	//open
	result=openSerialPort(portName);
	if(result)
		return result;

	//test
	for(char c='a'; c<='z'; c++)
	{
		WriteFile(hSerial, &c, 1, &numberOfBytes, NULL);
		ReadFile(hSerial, received, 2, &numberOfBytes, NULL);
		if(c!=received[0])
		{
			CloseHandle(hSerial);
		}
		if('\n'!=received[1])
			return -6;
	}

	return 0;
}
static int openSerialPort(WCHAR* portName)
{

	char* arr=new char[5];

	for (int i=0;i<5;i++)
		arr[i]=portName[i];

	LPCSTR mName=(LPCSTR)arr;
	


	hSerial = CreateFile( mName,
		GENERIC_READ | GENERIC_WRITE,   
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if(hSerial==INVALID_HANDLE_VALUE)
	{
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{
			//serial port does not exist. Inform user.
			//printf_s("port doesn't exist\n");
			return 1;
		}
		//some other error occurred. Inform user.
	}
	//Initialize the DCB structure
	SecureZeroMemory (&dcb,sizeof(DCB));
	dcb.DCBlength=sizeof(DCB);

	//Build on the current configuration by first retrieving all current settings
	fSuccess=GetCommState(hSerial,&dcb);

	if (!fSuccess)
	{
		//Handle the error
		//printf_s ("GetCommState failed with error %d.\n",GetLastError());
		return 2;
	}

	//PrintCommState(dcb);
	dcb.BaudRate=CBR_115200;
	dcb.ByteSize=8;
	dcb.Parity=NOPARITY;
	dcb.StopBits=ONESTOPBIT;

	fSuccess= SetCommState(hSerial,&dcb);
	if (!fSuccess) 
	{
		//  Handle the error.
		printf_s ("SetCommState failed with error %d.\n", GetLastError());
		return 3;
	}

	COMMTIMEOUTS timeouts={0};
	timeouts.ReadIntervalTimeout=50;
	timeouts.ReadTotalTimeoutConstant=50;
	timeouts.ReadTotalTimeoutMultiplier=10;
	timeouts.WriteTotalTimeoutConstant=50;
	timeouts.WriteTotalTimeoutMultiplier=10;
	if(!SetCommTimeouts(hSerial, &timeouts))
	{
		//error occureed. Inform user
	}

	fSuccess = GetCommState(hSerial, &dcb);
	if (!fSuccess) 
	{
		//  Handle the error.
		printf_s ("GetCommState failed with error %d.\n", GetLastError());
		return 2;
	}
	return 0;
}