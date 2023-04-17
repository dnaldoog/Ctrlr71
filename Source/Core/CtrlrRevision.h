#ifndef __CTRLR_REVISION__
#define __CTRLR_REVISION__
#include <chrono>
#include <string.h>

static const char* NowToString()
{
		std::time_t ct = std::time(0);
		char* t = ctime(&ct);
		if (t[strlen(t) - 1] == '\n') t[strlen(t) - 1] = '\0'; // remove trailing line break
		return t;
}

static const char *ctrlrRevision              	= "5.7.1";
static const char *ctrlrRevisionDate        	= NowToString(); //"NGO, 5 Apr 2023, 14:37:02 JST";

#endif
