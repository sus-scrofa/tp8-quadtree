#pragma once
#include "compilationSwitch.h"
typedef struct
{
	char * path;
#if MODE == COMPRESS
	float fidelity;
#endif
} cmdLineParserData_t;

int	parserCallback(char * key, char * value, void * data);