// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Experience/Public/ExperienceDefination.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExperienceDefination() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceActionSet_NoRegister();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceDefination();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceDefination_NoRegister();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperiencePawnData_NoRegister();
GAMEFEATURES_API UClass* Z_Construct_UClass_UGameFeatureAction_NoRegister();
UPackage* Z_Construct_UPackage__Script_Experience();
// End Cross Module References

// Begin Class UExperienceDefination
void UExperienceDefination::StaticRegisterNativesUExperienceDefination()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UExperienceDefination);
UClass* Z_Construct_UClass_UExperienceDefination_NoRegister()
{
	return UExperienceDefination::StaticClass();
}
struct Z_Construct_UClass_UExperienceDefination_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\x09\x09\xe5\x8c\x85\xe5\x90\xab\xe5\x9f\xba\xe6\x9c\xac\xe7\x9a\x84""Experience\xe9\x9c\x80\xe8\xa6\x81\xe5\x8a\xa0\xe8\xbd\xbd\xe7\x9a\x84\xe4\xb8\x9c\xe8\xa5\xbf---\xe6\x8c\x87\xe9\x92\x88\xe4\xb8\xbaTObjectPtr\xef\xbc\x8c\xe5\x88\xb0\xe8\xa6\x81\xe5\x8a\xa0\xe8\xbd\xbd""ExperienceDefination\xe7\x9a\x84\xe9\x98\xb6\xe6\xae\xb5\xe5\xb0\xb1\xe5\x85\xa8\xe9\x83\xa8\xe5\x8a\xa0\xe8\xbd\xbd\xe8\xbf\x9b\xe6\x9d\xa5\n */" },
#endif
		{ "IncludePath", "ExperienceDefination.h" },
		{ "ModuleRelativePath", "Public/ExperienceDefination.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8c\x85\xe5\x90\xab\xe5\x9f\xba\xe6\x9c\xac\xe7\x9a\x84""Experience\xe9\x9c\x80\xe8\xa6\x81\xe5\x8a\xa0\xe8\xbd\xbd\xe7\x9a\x84\xe4\xb8\x9c\xe8\xa5\xbf---\xe6\x8c\x87\xe9\x92\x88\xe4\xb8\xbaTObjectPtr\xef\xbc\x8c\xe5\x88\xb0\xe8\xa6\x81\xe5\x8a\xa0\xe8\xbd\xbd""ExperienceDefination\xe7\x9a\x84\xe9\x98\xb6\xe6\xae\xb5\xe5\xb0\xb1\xe5\x85\xa8\xe9\x83\xa8\xe5\x8a\xa0\xe8\xbd\xbd\xe8\xbf\x9b\xe6\x9d\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GameFeatureToEnable_MetaData[] = {
		{ "Category", "URL" },
		{ "ModuleRelativePath", "Public/ExperienceDefination.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultPawnData_MetaData[] = {
		{ "Category", "PawnData" },
		{ "ModuleRelativePath", "Public/ExperienceDefination.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActionSets_MetaData[] = {
		{ "Category", "Action" },
		{ "ModuleRelativePath", "Public/ExperienceDefination.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Actions_MetaData[] = {
		{ "Category", "Actions" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ExperienceDefination.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_GameFeatureToEnable_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_GameFeatureToEnable;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultPawnData;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActionSets_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActionSets;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Actions;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExperienceDefination>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UExperienceDefination_Statics::NewProp_GameFeatureToEnable_Inner = { "GameFeatureToEnable", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UExperienceDefination_Statics::NewProp_GameFeatureToEnable = { "GameFeatureToEnable", nullptr, (EPropertyFlags)0x0010000000000011, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperienceDefination, GameFeatureToEnable), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GameFeatureToEnable_MetaData), NewProp_GameFeatureToEnable_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExperienceDefination_Statics::NewProp_DefaultPawnData = { "DefaultPawnData", nullptr, (EPropertyFlags)0x0114000000000011, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperienceDefination, DefaultPawnData), Z_Construct_UClass_UExperiencePawnData_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultPawnData_MetaData), NewProp_DefaultPawnData_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExperienceDefination_Statics::NewProp_ActionSets_Inner = { "ActionSets", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UExperienceActionSet_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UExperienceDefination_Statics::NewProp_ActionSets = { "ActionSets", nullptr, (EPropertyFlags)0x0114000000010011, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperienceDefination, ActionSets), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActionSets_MetaData), NewProp_ActionSets_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExperienceDefination_Statics::NewProp_Actions_Inner = { "Actions", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UGameFeatureAction_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UExperienceDefination_Statics::NewProp_Actions = { "Actions", nullptr, (EPropertyFlags)0x0114008000010019, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperienceDefination, Actions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Actions_MetaData), NewProp_Actions_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExperienceDefination_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceDefination_Statics::NewProp_GameFeatureToEnable_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceDefination_Statics::NewProp_GameFeatureToEnable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceDefination_Statics::NewProp_DefaultPawnData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceDefination_Statics::NewProp_ActionSets_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceDefination_Statics::NewProp_ActionSets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceDefination_Statics::NewProp_Actions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceDefination_Statics::NewProp_Actions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceDefination_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExperienceDefination_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_Experience,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceDefination_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UExperienceDefination_Statics::ClassParams = {
	&UExperienceDefination::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UExperienceDefination_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceDefination_Statics::PropPointers),
	0,
	0x009100A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceDefination_Statics::Class_MetaDataParams), Z_Construct_UClass_UExperienceDefination_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UExperienceDefination()
{
	if (!Z_Registration_Info_UClass_UExperienceDefination.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UExperienceDefination.OuterSingleton, Z_Construct_UClass_UExperienceDefination_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UExperienceDefination.OuterSingleton;
}
template<> EXPERIENCE_API UClass* StaticClass<UExperienceDefination>()
{
	return UExperienceDefination::StaticClass();
}
UExperienceDefination::UExperienceDefination(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UExperienceDefination);
UExperienceDefination::~UExperienceDefination() {}
// End Class UExperienceDefination

// Begin Registration
struct Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceDefination_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExperienceDefination, UExperienceDefination::StaticClass, TEXT("UExperienceDefination"), &Z_Registration_Info_UClass_UExperienceDefination, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExperienceDefination), 2391707234U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceDefination_h_1461900144(TEXT("/Script/Experience"),
	Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceDefination_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceDefination_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
