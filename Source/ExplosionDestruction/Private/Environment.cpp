// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment.h"

// This is used to turn an argument into a string by
// putting quotes to the left and right of it
#define str(s) #s

// This is used to define CVARs
#define DEFINE_CVAR(Type, Name, DefaultValue, ECVF, HelpText) \
Type Environment::Name = DefaultValue; \
FAutoConsoleVariableRef CVAR ## Name ( \
	TEXT(str(Name)), \
	Environment::Name, \
	TEXT(HelpText), \
	ECVF); \


DEFINE_CVAR(int32,      DebugWeapons,            0,         ECVF_Cheat,       "Draw debug lines for weapons and explosion radius")
DEFINE_CVAR(int32,      LogEnabled,              1,         ECVF_Cheat,       "Enable logging")
DEFINE_CVAR(int32,      LogVerbosity,            2,         ECVF_Cheat,       "Verbosity of logging. 4 = Verbose, 3 = Informational, 2 = Warnings, 1 = Errors, 0 = Fatal")
DEFINE_CVAR(int32,      LogToScreen,             0,         ECVF_Cheat,       "Send debug to screen as well as to logs")
DEFINE_CVAR(int32,      LogShowTick,             0,         ECVF_Cheat,       "Show tick count in the logging (not for screen logging)")
DEFINE_CVAR(int32,      LogShowTimestamp,        0,         ECVF_Cheat,       "Send timestamp in the logging (not for screen logging)")
DEFINE_CVAR(float,      DebugWeaponAlpha,        1.f,       ECVF_Cheat,       "Change the alpha for the weapon sprites (switch weapons after changing this to take effect)")
DEFINE_CVAR(int32,      Invincible,              0,         ECVF_Cheat,       "Become invincible to all damage")
DEFINE_CVAR(int32,      DebugFloorAngle,         0,         ECVF_Cheat,       "Debug the calculation of the floor angle")