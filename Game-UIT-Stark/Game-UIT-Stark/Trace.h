#pragma once
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>

// Use Trace::Log(...) for logging any message to a file
// Log file has been set to "C:\\temp\\Trace::Log.log"
// Example: Trace::Log("[ERROR] Failed to create sprite from file '%s'", _FilePath);
class Trace
{
private:
	static FILE *Stream;
	static Trace* Instance;
	Trace();
public:
	static bool Active;
	static const char *FilePath;

	~Trace();

	static void Log(const char *format, ...);
	static void Log(const LPWSTR format, ...);
	static Trace* Logger();
};
