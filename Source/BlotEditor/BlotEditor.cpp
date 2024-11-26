// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlotEditor.h"
#include "Modules/ModuleManager.h"


class FBlotEditorModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
	}

	virtual void ShutdownModule() override
	{
	}
	
};

IMPLEMENT_MODULE(FBlotEditorModule, BlotEditor);

#undef LOCTEXT_NAMESPACE
