// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment.h"

// This is used to turn an argument into a string by
// putting quotes to the left and right of it
#define str(s) #s

// This is used to define CVARs
#define DEFINE_CVAR(Type, Name, DefaultValue, HelpText, ECVF) \
Type Environment::Name = DefaultValue; \
FAutoConsoleVariableRef CVAR ## Name ( \
	TEXT(str(Name)), \
	Environment::Name, \
	TEXT(HelpText), \
	ECVF ); \


DEFINE_CVAR(int32, DebugWeapons, 0, "Draw debug lines for weapons and explosion radius", ECVF_Cheat)
DEFINE_CVAR(int32, LogEnabled, 1, "Enable logging", ECVF_Cheat)
DEFINE_CVAR(int32, LogVerbosity, 2, "Verbosity of logging. 4 = Verbose, 3 = Informational, 2 = Warnings, 1 = Errors, 0 = Fatal", ECVF_Cheat)
DEFINE_CVAR(int32, LogToScreen, 0, "Send debug to screen as well as to logs", ECVF_Cheat)
DEFINE_CVAR(int32, LogShowTick, 0, "Show tick count in the logging (not for screen logging)", ECVF_Cheat)
DEFINE_CVAR(int32, LogShowTimestamp, 0, "Send timestamp in the logging (not for screen logging)", ECVF_Cheat)
DEFINE_CVAR(float, DebugWeaponAlpha, 1.f, "Change the alpha for the weapon sprites (switch weapons after changing this to take effect)", ECVF_Cheat)