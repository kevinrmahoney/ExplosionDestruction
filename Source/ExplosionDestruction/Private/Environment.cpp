// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment.h"

// This is used to turn an argument into a string by
// putting quotes to the left and right of it
#define str(s) #s

// This is used to define CVARs
#define DEFINE_CVAR(Name, DefaultValue, HelpText, ECVF) \
int32 Environment::Name = DefaultValue; \
FAutoConsoleVariableRef CVAR ## Name ( \
	TEXT(str(Name)), \
	Environment::Name, \
	TEXT(HelpText), \
	ECVF ); \


DEFINE_CVAR(DebugWeapons, 0, "Draw debug lines for weapons and explosion radius", ECVF_Cheat)
DEFINE_CVAR(LogEnabled, 1, "Enable logging", ECVF_Cheat)
DEFINE_CVAR(LogVerbosity, 2, "Verbosity of logging. 4 = Verbose, 3 = Informational, 2 = Warnings, 1 = Errors, 0 = Fatal", ECVF_Cheat)
DEFINE_CVAR(LogToScreen, 0, "Send debug to screen as well as to logs", ECVF_Cheat)
DEFINE_CVAR(LogShowTick, 0, "Show tick count in the logging (not for screen logging)", ECVF_Cheat)
DEFINE_CVAR(LogShowTimestamp, 0, "Send timestamp in the logging (not for screen logging)", ECVF_Cheat)