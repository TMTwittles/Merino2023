#include "Merino23Editor.h"

#include "Editor/UnrealEdEngine.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FMerino23EditorModule, Merino23Editor);

DEFINE_LOG_CATEGORY(Merino23Editor)

#define LOCTEXT_NAMESPACE "Merino23Editor"

void FMerino23EditorModule::StartupModule()
{
	
}

void FMerino23EditorModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE