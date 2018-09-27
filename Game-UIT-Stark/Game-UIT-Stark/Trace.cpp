#pragma once
#include "Trace.h"

Trace* Trace::Instance = new Trace();
const char *Trace::FilePath = "Logs/Trace.log";
bool Trace::Active = true;
FILE *Trace::Stream = nullptr;
Trace::Trace()
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s(&Stream, "conin$", "r", stdin);
	freopen_s(&Stream, "conout$", "w", stdout);
	freopen_s(&Stream, "conout$", "w", stderr);
#endif
}

Trace::~Trace()
{
	fclose(Stream);
	delete Stream;
	Stream = nullptr;
	delete[] FilePath;
	FilePath = nullptr;
}

void Trace::Log(const char * format, ...)
{
	if (!Active) return;
	FILE *f = stderr;

#ifndef _DEBUG
	auto filepath = Instance->FilePath;
	if (filepath != NULL)
	{
		if (fopen_s(&f, filepath, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open Trace::Log file '%s' for writing!\n", filepath);
			return;
		}
	}
#endif
	va_list ap;
	va_start(ap, format);
	vfprintf(f, format, ap);
	va_end(ap);
	fprintf(f, "\n");

#ifndef _DEBUG
	if (filepath != NULL) fclose(f);
#endif
}

void Trace::Log(const LPWSTR format, ...)
{
	if (!Active) return;
	FILE *f = stderr;

#ifndef _DEBUG
	auto filepath = Instance->FilePath;
	if (filepath != NULL)
	{
		if (fopen_s(&f, filepath, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open Trace::Log file '%s' for writing!\n", filepath);
			return;
		}
	}
#endif
	va_list ap;
	va_start(ap, format);
	vfwprintf(f, format, ap);
	va_end(ap);
	fprintf(f, "\n");

#ifndef _DEBUG
	if (filepath != NULL) fclose(f);
#endif
}

Trace * Trace::Logger()
{
	if (!Instance)
		Instance = new Trace();

	return Instance;
}
