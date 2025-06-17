// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Experience/Public/ExperienceActionSet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExperienceActionSet() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceActionSet();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceActionSet_NoRegister();
GAMEFEATURES_API UClass* Z_Construct_UClass_UGameFeatureAction_NoRegister();
UPackage* Z_Construct_UPackage__Script_Experience();
// End Cross Module References

// Begin Class UExperienceActionSet
void UExperienceActionSet::StaticRegisterNativesUExperienceActionSet()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UExperienceActionSet);
UClass* Z_Construct_UClass_UExperienceActionSet_NoRegister()
{
	return UExperienceActionSet::StaticClass();
}
struct Z_Construct_UClass_UExperienceActionSet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "ExperienceActionSet.h" },
		{ "ModuleRelativePath", "Public/ExperienceActionSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Actions_MetaData[] = {
		{ "Category", "Action" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ExperienceActionSet.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Actions;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExperienceActionSet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExperienceActionSet_Statics::NewProp_Actions_Inner = { "Actions", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UGameFeatureAction_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UExperienceActionSet_Statics::NewProp_Actions = { "Actions", nullptr, (EPropertyFlags)0x0114008000010019, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperienceActionSet, Actions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Actions_MetaData), NewProp_Actions_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExperienceActionSet_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceActionSet_Statics::NewProp_Actions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperienceActionSet_Statics::NewProp_Actions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceActionSet_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExperienceActionSet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_Experience,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceActionSet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UExperienceActionSet_Statics::ClassParams = {
	&UExperienceActionSet::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UExperienceActionSet_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceActionSet_Statics::PropPointers),
	0,
	0x009100A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UExperienceActionSet_Statics::Class_MetaDataParams), Z_Construct_UClass_UExperienceActionSet_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UExperienceActionSet()
{
	if (!Z_Registration_Info_UClass_UExperienceActionSet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UExperienceActionSet.OuterSingleton, Z_Construct_UClass_UExperienceActionSet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UExperienceActionSet.OuterSingleton;
}
template<> EXPERIENCE_API UClass* StaticClass<UExperienceActionSet>()
{
	return UExperienceActionSet::StaticClass();
}
UExperienceActionSet::UExperienceActionSet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UExperienceActionSet);
UExperienceActionSet::~UExperienceActionSet() {}
// End Class UExperienceActionSet

// Begin Registration
struct Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceActionSet_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExperienceActionSet, UExperienceActionSet::StaticClass, TEXT("UExperienceActionSet"), &Z_Registration_Info_UClass_UExperienceActionSet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExperienceActionSet), 4491431U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceActionSet_h_1591261823(TEXT("/Script/Experience"),
	Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceActionSet_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceActionSet_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
