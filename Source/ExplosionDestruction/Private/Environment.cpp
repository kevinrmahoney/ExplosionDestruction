// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment.h"

Environment::Environment()
{
}

Environment::~Environment()
{
}

// This is used to turn an argument into a string by
// putting quotes to the left and right of it
#define str(s) #s

// This is used to define CVARs
#define DEFINE_CVAR(Name, HelpText, ECVF) \
int32 Environment::Name = 0; \
FAutoConsoleVariableRef CVAR ## Name ( \
	TEXT(str(Name)), \
	Environment::Name, \
	TEXT(HelpText), \
	ECVF ); \

DEFINE_CVAR(DebugWeapons, "Draw debug lines for weapons and explosion radius", ECVF_Cheat)

DEFINE_CVAR(DebugLogs, "Show console logs", ECVF_Cheat)

DEFINE_CVAR(DebugVerbosity, "Verbosity of logging. 0 = Verbose, 10 = Informational, 20 = Warnings, 30 = Errors, 40 = Fatal", ECVF_Cheat)