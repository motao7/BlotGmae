// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Experience/Public/ExperienceManagerComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExperienceManagerComponent() {}

// Begin Cross Module References
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceDefination_NoRegister();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceManagerComponent();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceManagerComponent_NoRegister();
MODULARGAMEPLAY_API UClass* Z_Construct_UClass_UGameStateComponent();
UPackage* Z_Construct_UPackage__Script_Experience();
// End Cross Module References

// Begin Class UExperienceManagerComponent Function OnRep_CurrentExperience
struct Z_Construct_UFunction_UExperienceManagerComponent_OnRep_CurrentExperience_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\xe5\xae\xa2\xe6\x88\xb7\xe7\xab\xaf\xe6\x89\xa7\xe8\xa1\x8cLoadExperienceTPtrVariable*/" },
#endif
		{ "ModuleRelativePath", "Public/ExperienceManagerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xae\xa2\xe6\x88\xb7\xe7\xab\xaf\xe6\x89\xa7\xe8\xa1\x8cLoadExperienceTPtrVariable" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UExperienceManagerComponent_OnRep_CurrentExperience_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UExperienceManagerComponent, nullptr, "OnRep_CurrentExperience", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UExperienceManagerComponent_OnRep_CurrentExperience_Statics::Function_MetaDataParams), Z_Construct_UFunction_UExperienceManagerComponent_OnRep_CurrentExperience_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UExperienceManagerComponent_OnRep_CurrentExperience()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UExperienceManagerComponent_OnRep_CurrentExperience_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UExperienceManagerComponent::execOnRep_CurrentExperience)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_CurrentExperience();
	P_NATIVE_END;
}
// End Class UExperienceManagerComponent Function OnRep_CurrentExperience

// Begin Class UExperienceManagerComponent
void UExperienceManagerComponent::StaticRegisterNativesUExperienceManagerComponent()
{
	UClass* Class = UExperienceManagerComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnRep_CurrentExperience", &UExperienceManagerComponent::execOnRep_CurrentExperience },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UExperienceManagerComponent);
UClass* Z_Construct_UClass_UExperienceManagerComponent_NoRegister()
{
	return UExperienceManagerComponent::StaticClass();
}
struct Z_Construct_UClass_UExperienceManagerComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\x09\x09\xe5\x8a\xa0\xe8\xbd\xbd""Experience\n *\x09\x09GameState\xe4\xb8\xba\xe5\xae\xa2\xe6\x88\xb7\xe7\xab\xaf\xe5\x92\x8c\xe6\x9c\x8d\xe5\x8a\xa1\xe5\x99\xa8\xe5\x90\x8c\xe6\xad\xa5\xe7\x9a\x84\xe5\xb9\xb6\xe4\xb8\x8d\xe4\xbb\xa3\xe7\xa0\x81\xe5\x85\xb6\xe8\xba\xab\xe4\xb8\x8a\xe7\x9a\x84\xe7\xbb\x84\xe4\xbb\xb6\xe4\xb9\x9f\xe5\x90\x8c\xe6\xad\xa5\xef\xbc\x8c\xe9\x9c\x80\xe8\xa6\x81\xe8\x87\xaa\xe5\xb7\xb1\xe8\xae\xbe\xe7\xbd\xae\xe7\xbd\x91\xe7\xbb\x9c\xe5\x90\x8c\xe6\xad\xa5\n */" },
#endif
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "ExperienceManagerComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/ExperienceManagerComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8a\xa0\xe8\xbd\xbd""Experience\nGameState\xe4\xb8\xba\xe5\xae\xa2\xe6\x88\xb7\xe7\xab\xaf\xe5\x92\x8c\xe6\x9c\x8d\xe5\x8a\xa1\xe5\x99\xa8\xe5\x90\x8c\xe6\xad\xa5\xe7\x9a\x84\xe5\xb9\xb6\xe4\xb8\x8d\xe4\xbb\xa3\xe7\xa0\x81\xe5\x85\xb6\xe8\xba\xab\xe4\xb8\x8a\xe7\x9a\x84\xe7\xbb\x84\xe4\xbb\xb6\xe4\xb9\x9f\xe5\x90\x8c\xe6\xad\xa5\xef\xbc\x8c\xe9\x9c\x80\xe8\xa6\x81\xe8\x87\xaa\xe5\xb7\xb1\xe8\xae\xbe\xe7\xbd\xae\xe7\xbd\x91\xe7\xbb\x9c\xe5\x90\x8c\xe6\xad\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentExperience_MetaData[] = {
		{ "ModuleRelativePath", "Public/ExperienceManagerComponent.h" },
		{ "NativeConstTemplateArg", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentExperience;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UExperienceManagerComponent_OnRep_CurrentExperience, "OnRep_CurrentExperience" }, // 230976135
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExperienceManagerComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExperienceManagerComponent_Statics::NewProp_CurrentExperience = { "CurrentExperience", "OnRep_CurrentExperience", (EPropertyFlags)0x0124080100000020, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperienceManagerComponent, CurrentExperience), Z_Construct_UClass_UExperienceDefination_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentExperience_MetaData), NewProp_CurrentExperience_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExperienceManagerComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceManagerComponent_Statics::NewProp_CurrentExperience,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceManagerComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExperienceManagerComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameStateComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_Experience,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceManagerComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UExperienceManagerComponent_Statics::ClassParams = {
	&UExperienceManagerComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UExperienceManagerComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceManagerComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceManagerComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UExperienceManagerComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UExperienceManagerComponent()
{
	if (!Z_Registration_Info_UClass_UExperienceManagerComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UExperienceManagerComponent.OuterSingleton, Z_Construct_UClass_UExperienceManagerComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UExperienceManagerComponent.OuterSingleton;
}
template<> EXPERIENCE_API UClass* StaticClass<UExperienceManagerComponent>()
{
	return UExperienceManagerComponent::StaticClass();
}
void UExperienceManagerComponent::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static const FName Name_CurrentExperience(TEXT("CurrentExperience"));
	const bool bIsValid = true
		&& Name_CurrentExperience == ClassReps[(int32)ENetFields_Private::CurrentExperience].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UExperienceManagerComponent"));
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UExperienceManagerComponent);
UExperienceManagerComponent::~UExperienceManagerComponent() {}
// End Class UExperienceManagerComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExperienceManagerComponent, UExperienceManagerComponent::StaticClass, TEXT("UExperienceManagerComponent"), &Z_Registration_Info_UClass_UExperienceManagerComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExperienceManagerComponent), 444239884U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_200946624(TEXT("/Script/Experience"),
	Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
