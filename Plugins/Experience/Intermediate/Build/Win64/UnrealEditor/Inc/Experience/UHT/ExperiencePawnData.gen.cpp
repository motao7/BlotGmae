// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Experience/Public/ExperiencePawnData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExperiencePawnData() {}

// Begin Cross Module References
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraMode_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_APawn_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperiencePawnData();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperiencePawnData_NoRegister();
UPackage* Z_Construct_UPackage__Script_Experience();
// End Cross Module References

// Begin Class UExperiencePawnData
void UExperiencePawnData::StaticRegisterNativesUExperiencePawnData()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UExperiencePawnData);
UClass* Z_Construct_UClass_UExperiencePawnData_NoRegister()
{
	return UExperiencePawnData::StaticClass();
}
struct Z_Construct_UClass_UExperiencePawnData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "ExperiencePawnData.h" },
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PawnClass_MetaData[] = {
		{ "Category", "Pawn" },
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultCameraMode_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_PawnClass;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DefaultCameraMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExperiencePawnData>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_PawnClass = { "PawnClass", nullptr, (EPropertyFlags)0x0014000000000011, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperiencePawnData, PawnClass), Z_Construct_UClass_UClass, Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PawnClass_MetaData), NewProp_PawnClass_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_DefaultCameraMode = { "DefaultCameraMode", nullptr, (EPropertyFlags)0x0014000000000011, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperiencePawnData, DefaultCameraMode), Z_Construct_UClass_UClass, Z_Construct_UClass_UCommonCameraMode_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultCameraMode_MetaData), NewProp_DefaultCameraMode_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExperiencePawnData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_PawnClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_DefaultCameraMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperiencePawnData_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExperiencePawnData_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_Experience,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExperiencePawnData_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UExperiencePawnData_Statics::ClassParams = {
	&UExperiencePawnData::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UExperiencePawnData_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UExperiencePawnData_Statics::PropPointers),
	0,
	0x001100A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UExperiencePawnData_Statics::Class_MetaDataParams), Z_Construct_UClass_UExperiencePawnData_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UExperiencePawnData()
{
	if (!Z_Registration_Info_UClass_UExperiencePawnData.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UExperiencePawnData.OuterSingleton, Z_Construct_UClass_UExperiencePawnData_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UExperiencePawnData.OuterSingleton;
}
template<> EXPERIENCE_API UClass* StaticClass<UExperiencePawnData>()
{
	return UExperiencePawnData::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UExperiencePawnData);
UExperiencePawnData::~UExperiencePawnData() {}
// End Class UExperiencePawnData

// Begin Registration
struct Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExperiencePawnData, UExperiencePawnData::StaticClass, TEXT("UExperiencePawnData"), &Z_Registration_Info_UClass_UExperiencePawnData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExperiencePawnData), 574489073U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_2148616971(TEXT("/Script/Experience"),
	Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
