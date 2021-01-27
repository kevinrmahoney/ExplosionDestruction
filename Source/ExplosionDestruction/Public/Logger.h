// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core\Public\Logging\LogVerbosity.h"

/** Logger
 *
 * Use this to log messages to screen or to console/file
 *
 * Usage examples:
 *  Logger::Info("Hello!");
 *  Logger::Warning("Hello %s! You are going %d units per second!", MyChar->GetName(), MyChar->GetSpeed());
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
		InfoLevel = 0,
		WarningLevel = 1,
		ErrorLevel = 2,
		FatalLevel = 3
	};

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
	static bool bShowTimeStamp;
	static bool bShowTicks;
	static bool bShowOnScreen;
	static enum Verbosity MinVerbosity;

	template <typename FmtType, typename... Types>
	static void LogMessage(enum Verbosity LogVerbosity, FColor Color, const FmtType& Fmt, Types... Args)
	{
		FString Message = FString::Printf(Fmt, Args...);
		FString TickStamp = FString("");
		FString TimeStamp = FString("");

		if(bShowTicks)
			TickStamp = FString::Printf(TEXT("[%s]"), *FString::FromInt(TickCount));

		if(bShowTimeStamp)
			TimeStamp = FString::Printf(TEXT("[%s]"), *GetTimeStamp());

		// We convert our internal Verbosity enum to UE's verbosity level and use UE_LOG.
		if(Verbosity::FatalLevel <= LogVerbosity)
			UE_LOG(LogTemp, Fatal, TEXT("  %s%s %s"), *TimeStamp, *TickStamp, *Message)
		else if(Verbosity::ErrorLevel == LogVerbosity)
			UE_LOG(LogTemp, Error, TEXT("  %s%s %s"), *TimeStamp, *TickStamp, *Message)
		 else if(Verbosity::WarningLevel == LogVerbosity)
			UE_LOG(LogTemp, Warning, TEXT("%s%s %s"), *TimeStamp, *TickStamp, *Message)
		 else if(Verbosity::InfoLevel == LogVerbosity)
			UE_LOG(LogTemp, Display, TEXT("%s%s %s"), *TimeStamp, *TickStamp, *Message)


		if(bShowOnScreen && GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, Color, *Message);
	}

	static FString GetTimeStamp();
};
