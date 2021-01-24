// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core\Public\Logging\LogVerbosity.h"

using namespace ELogVerbosity;

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

	template <typename FmtType, typename... Types>
	static void Info(const FmtType& Fmt, Types... Args)
	{
		LogMessage(Display, FColor::White, Fmt, Args...);
	}

	template <typename FmtType, typename... Types>
	static void Warning(const FmtType& Fmt, Types... Args)
	{
		LogMessage(Warning, FColor::Yellow, Fmt, Args...);
	}

	template <typename FmtType, typename... Types>
	static void Error(const FmtType& Fmt, Types... Args)
	{
		LogMessage(Error, FColor::Orange, Fmt, Args...);
	}

	template <typename FmtType, typename... Types>
	static void Fatal(const FmtType& Fmt, Types... Args)
	{
		LogMessage(Fatal, FColor::Red, Fmt, Args...);
	}

private:
	static long TickCount;
	static bool bShowTimeStamp;
	static bool bShowTicks;
	static bool bShowOnScreen;
	static enum ELogVerbosity::Type MinVerbosity;

	template <typename FmtType, typename... Types>
	static void LogMessage(ELogVerbosity::Type LogVerbosity, FColor Color, const FmtType& Fmt, Types... Args)
	{
		if(LogVerbosity < Logger::MinVerbosity)
			return;

		FString Message = FString::Printf(Fmt, Args...);
		FString TickStamp;
		FString TimeStamp;

		if(bShowTicks)
			TickStamp = FString::Printf(TEXT("[%s]"), *FString::FromInt(TickCount));

		if(bShowTimeStamp)
			TimeStamp = FString::Printf(TEXT("[%s]"), *GetTimeStamp());

		if(ELogVerbosity::Fatal == LogVerbosity)
			UE_LOG(LogTemp, Fatal, TEXT("%s%s%s"), *TimeStamp, *TickStamp, *Message);
		if(ELogVerbosity::Error == LogVerbosity)
			UE_LOG(LogTemp, Error, TEXT("%s%s%s"), *TimeStamp, *TickStamp, *Message);
		if(ELogVerbosity::Warning == LogVerbosity)
			UE_LOG(LogTemp, Warning, TEXT("%s%s%s"), *TimeStamp, *TickStamp, *Message);
		if(ELogVerbosity::Display == LogVerbosity)
			UE_LOG(LogTemp, Display, TEXT("%s%s%s"), *TimeStamp, *TickStamp, *Message);

		if(bShowOnScreen && GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, Color, *Message);
	}

	static FString GetTimeStamp();
};
