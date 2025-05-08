// Fill out your copyright notice in the Description page of Project Settings.

#include "ShroomCafe.h"
#include "Modules/ModuleManager.h"
#include "MyGameplayTags.h" 



class FShroomCafeModule : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override
    {
        FMyGameplayTags::InitializeNativeTags();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(FShroomCafeModule, ShroomCafe, "ShroomCafe");

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ShroomCafe, "ShroomCafe" );
