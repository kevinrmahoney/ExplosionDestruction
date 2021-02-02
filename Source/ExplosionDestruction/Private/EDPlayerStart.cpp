// Fill out your copyright notice in the Description page of Project Settings.


#include "EDPlayerStart.h"
#include "Logger.h"

void AEDPlayerStart::Activate()
{
	Activated = true;

	Logger::Info(TEXT("Activating spawner %s"), *GetName());
}

void AEDPlayerStart::Deactivate()
{
	Activated = false;

	Logger::Info(TEXT("Deactivating spawner %s"), *GetName());
}