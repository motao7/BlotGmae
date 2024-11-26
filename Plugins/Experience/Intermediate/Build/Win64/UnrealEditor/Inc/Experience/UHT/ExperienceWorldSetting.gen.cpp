// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Experience/Public/ExperienceWorldSetting.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExperienceWorldSetting() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AWorldSettings();
EXPERIENCE_API UClass* Z_Construct_UClass_AExperienceWorldSetting();
EXPERIENCE_API UClass* Z_Construct_UClass_AExperienceWorldSetting_NoRegister();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperienceDefination_NoRegister();
UPackage* Z_Construct_UPackage__Script_Experience();
// End Cross Module References

// Begin Class AExperienceWorldSetting
void AExperienceWorldSetting::StaticRegisterNativesAExperienceWorldSetting()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AExperienceWorldSetting);
UClass* Z_Construct_UClass_AExperienceWorldSetting_NoRegister()
{
	return AExperienceWorldSetting::StaticClass();
}
struct Z_Construct_UClass_AExperienceWorldSetting_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\x09\x09\xe6\x8c\x81\xe6\x9c\x89\xe6\xaf\x8f\xe4\xb8\x80\xe4\xb8\xaaLevel\xe5\xaf\xb9\xe5\xba\x94\xe7\x9a\x84""Expeirnece\n */" },
#endif
		{ "HideCategories", "Actor Advanced Display Events Object Attachment Info Input Blueprint Layers Tags Replication LevelInstance Input Movement Collision Transformation HLOD DataLayers" },
		{ "IncludePath", "ExperienceWorldSetting.h" },
		{ "ModuleRelativePath", "Public/ExperienceWorldSetting.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x8c\x81\xe6\x9c\x89\xe6\xaf\x8f\xe4\xb8\x80\xe4\xb8\xaaLevel\xe5\xaf\xb9\xe5\xba\x94\xe7\x9a\x84""Expeirnece" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultExperience_MetaData[] = {
		{ "Category", "Experience" },
		{ "ModuleRelativePath", "Public/ExperienceWorldSetting.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FSoftClassPropertyParams NewProp_DefaultExperience;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AExperienceWorldSetting>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FSoftClassPropertyParams Z_Construct_UClass_AExperienceWorldSetting_Statics::NewProp_DefaultExperience = { "DefaultExperience", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::SoftClass, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AExperienceWorldSetting, DefaultExperience), Z_Construct_UClass_UExperienceDefination_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultExperience_MetaData), NewProp_DefaultExperience_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AExperienceWorldSetting_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AExperienceWorldSetting_Statics::NewProp_DefaultExperience,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AExperienceWorldSetting_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AExperienceWorldSetting_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AWorldSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_Experience,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AExperienceWorldSetting_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AExperienceWorldSetting_Statics::ClassParams = {
	&AExperienceWorldSetting::StaticClass,
	"game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AExperienceWorldSetting_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AExperienceWorldSetting_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AExperienceWorldSetting_Statics::Class_MetaDataParams), Z_Construct_UClass_AExperienceWorldSetting_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AExperienceWorldSetting()
{
	if (!Z_Registration_Info_UClass_AExperienceWorldSetting.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AExperienceWorldSetting.OuterSingleton, Z_Construct_UClass_AExperienceWorldSetting_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AExperienceWorldSetting.OuterSingleton;
}
template<> EXPERIENCE_API UClass* StaticClass<AExperienceWorldSetting>()
{
	return AExperienceWorldSetting::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AExperienceWorldSetting);
AExperienceWorldSetting::~AExperienceWorldSetting() {}
// End Class AExperienceWorldSetting

// Begin Registration
struct Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceWorldSetting_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AExperienceWorldSetting, AExperienceWorldSetting::StaticClass, TEXT("AExperienceWorldSetting"), &Z_Registration_Info_UClass_AExperienceWorldSetting, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AExperienceWorldSetting), 340698793U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceWorldSetting_h_1002072959(TEXT("/Script/Experience"),
	Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceWorldSetting_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceWorldSetting_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
