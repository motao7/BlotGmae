// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team.h"

#define LOCTEXT_NAMESPACE "FTeamModule"
DEFINE_LOG_CATEGORY(LogTeam);

void FTeamModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTeamModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTeamModule, Team)