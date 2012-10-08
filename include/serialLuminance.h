
#include "stdafx.h"

int readSensorValue(int index);

static int readLine(void);

int initialize(WCHAR* portName);

int initialize();

static int openAndTestSerialPort(WCHAR* portName);

static int openSerialPort(WCHAR* portName);