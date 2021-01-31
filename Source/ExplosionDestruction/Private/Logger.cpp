// Fill out your copyright notice in the Description page of Project Settings.


#include "Logger.h"
#include "Misc/DateTime.h"

long Logger::TickCount = 0;

Logger::Logger()
{
}

Logger::~Logger()
{
}

FString Logger::GetTimeStamp()
{
	FString TimeStamp;

	// Get the current time, and the millisecnds too.
	FDateTime Current = FDateTime::Now();
	int32 Ms = Current.GetMillisecond();

	// Create a string that looks like this: "[YYYY.MM.DD-HH-MM-SS.TTT]"
	// Where TTT is milliseconds
	// Example: "[2021.01.24-02.46.58.893] "
	TimeStamp = FString::Printf(TEXT("%s.%03d"), *Current.ToString(), Ms);

	return TimeStamp;
}

// Add tick. Make sure this is only done by ONE actor
// Right now, its done by the Observer actor. Only ONE per level.
void Logger::AddTick()
{
	Logger::TickCount++;
}