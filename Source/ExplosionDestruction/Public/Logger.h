// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core\Public\Logging\LogVerbosity.h"
#include "Environment.h"

#define PRINTFUNCENABLED

#ifdef PRINTFUNCENABLED
#define PRINTFUNC Logger::Verbose(TEXT("Function = %s"), *FString(__FUNCSIG__));
#else
#define PRINTFUNC
#endif

/** Logger
 *
 * Use this to log messages to screen or to console/file
 *
 * Usage examples:
 *  Logger::Info(TEXT("Hello!"));
 *  Logger::Warning(TEXT("Hello %s! You are going %d units per second!"), MyChar->GetName(), MyChar->GetSpeed());
 *
 * Can turn on showing to messages by turning on a boolean (see .cpp file). Default is off.
 * The output log shows tick count and timestamps as well by default.
 *
 */
class EXPLOSIONDESTRUCTION_API Logger
{
public:
	Logger();
	~Logger();

	static void AddTick();

	enum Verbosity
	{
		VerboseLevel = 4,
		InfoLevel = 3,
		WarningLevel = 2,
		ErrorLevel = 1,
		FatalLevel = 0
	};

	template <typename FmtType, typename... Types>
	static void Verbose(const FmtType& Fmt, Types... Args)
	{
		LogMessage(VerboseLevel, FColor::Cyan, Fmt, Args...);
	}

	template <typename FmtType, typename... Types>
	static void Info(const FmtType& Fmt, Types... Args)
	{
		LogMessage(InfoLevel, FColor::White, Fmt, Args...);
	}

	template <typename FmtType, typename... Types>
	static void Warning(const FmtType& Fmt, Types... Args)
	{
		LogMessage(WarningLevel, FColor::Yellow, Fmt, Args...);
	}

	template <typename FmtType, typename... Types>
	static void Error(const FmtType& Fmt, Types... Args)
	{
		LogMessage(ErrorLevel, FColor::Orange, Fmt, Args...);
	}

	template <typename FmtType, typename... Types>
	static void Fatal(const FmtType& Fmt, Types... Args)
	{
		LogMessage(FatalLevel, FColor::Red, Fmt, Args...);
	}

private:
	static long TickCount;

	template <typename FmtType, typename... Types>
	static void LogMessage(enum Verbosity LogVerbosity, FColor Color, const FmtType& Fmt, Types... Args)
	{
		// Only log if we have enabled the logger, and if the verboisty of the message is less than the verbosity setting
		if(Environment::LogsEnabled > 0 && LogVerbosity <= Environment::LogsVerbosity)
		{	
			// Create the formatted string
			FString Message = FString::Printf(Fmt, Args...);
			FString TickStamp = FString("");
			FString TimeStamp = FString("");

			// If enabled, create the timestamp and tick stamp
			if(Environment::LogsShowTick > 0)
				TickStamp = FString::Printf(TEXT("[%s]"), *FString::FromInt(TickCount));

			if(Environment::LogsShowTimestamp > 0)
				TimeStamp = FString::Printf(TEXT("[%s]"), *GetTimeStamp());

			// We convert our internal Verbosity enum to UE's verbosity level and use UE_LOG.
			if(Verbosity::FatalLevel == LogVerbosity)
				UE_LOG(LogTemp, Fatal, TEXT("  %s%s %s"), *TimeStamp, *TickStamp, *Message)
			else if(Verbosity::ErrorLevel == LogVerbosity)
				UE_LOG(LogTemp, Error, TEXT("  %s%s %s"), *TimeStamp, *TickStamp, *Message)
			else if(Verbosity::WarningLevel == LogVerbosity)
				UE_LOG(LogTemp, Warning, TEXT("%s%s %s"), *TimeStamp, *TickStamp, *Message)
			else if(Verbosity::InfoLevel == LogVerbosity)
				UE_LOG(LogTemp, Display, TEXT("%s%s %s"), *TimeStamp, *TickStamp, *Message)
			else if(Verbosity::VerboseLevel == LogVerbosity)
				UE_LOG(LogTemp, Display, TEXT("%s%s %s"), *TimeStamp, *TickStamp, *Message)

			// If enabled, also log to screen
			if(Environment::LogsToScreen && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, Color, *Message);
		}
	}

	static FString GetTimeStamp();
};
