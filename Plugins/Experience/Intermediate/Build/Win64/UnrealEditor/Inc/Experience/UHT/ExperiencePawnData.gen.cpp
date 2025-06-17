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
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperiencePawnData();
EXPERIENCE_API UClass* Z_Construct_UClass_UExperiencePawnData_NoRegister();
EXPERIENCE_API UScriptStruct* Z_Construct_UScriptStruct_FInputMappingContextAndPriority();
TAGINPUT_API UClass* Z_Construct_UClass_UTagInputConfig_NoRegister();
UPackage* Z_Construct_UPackage__Script_Experience();
// End Cross Module References

// Begin ScriptStruct FInputMappingContextAndPriority
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority;
class UScriptStruct* FInputMappingContextAndPriority::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FInputMappingContextAndPriority, (UObject*)Z_Construct_UPackage__Script_Experience(), TEXT("InputMappingContextAndPriority"));
	}
	return Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority.OuterSingleton;
}
template<> EXPERIENCE_API UScriptStruct* StaticStruct<FInputMappingContextAndPriority>()
{
	return FInputMappingContextAndPriority::StaticStruct();
}
struct Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputMapping_MetaData[] = {
		{ "AssetBundles", "Client,Server" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xe8\xbf\x99\xe9\x87\x8c\xe7\x9a\x84\xe6\x84\x8f\xe6\x80\x9d\xe6\x98\xaf\xe5\x8f\xaa\xe5\xaf\xb9InputMapping\xe8\xbf\x9b\xe8\xa1\x8c\xe8\xbd\xaf\xe5\xbc\x95\xe7\x94\xa8?\xe7\x9c\x9f\xe6\xad\xa3\xe5\x8a\xa0\xe8\xbd\xbd\xe9\x9c\x80\xe8\xa6\x81""addInputMapping\xe8\xbf\x9b\xe8\xa1\x8c\xe5\x8a\xa0\xe8\xbd\xbd\xe6\x98\xaf\xe5\x90\x97?\n" },
#endif
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\x99\xe9\x87\x8c\xe7\x9a\x84\xe6\x84\x8f\xe6\x80\x9d\xe6\x98\xaf\xe5\x8f\xaa\xe5\xaf\xb9InputMapping\xe8\xbf\x9b\xe8\xa1\x8c\xe8\xbd\xaf\xe5\xbc\x95\xe7\x94\xa8?\xe7\x9c\x9f\xe6\xad\xa3\xe5\x8a\xa0\xe8\xbd\xbd\xe9\x9c\x80\xe8\xa6\x81""addInputMapping\xe8\xbf\x9b\xe8\xa1\x8c\xe5\x8a\xa0\xe8\xbd\xbd\xe6\x98\xaf\xe5\x90\x97?" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Priority_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Higher priority input mappings will be prioritized over mappings with a lower priority.\n" },
#endif
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Higher priority input mappings will be prioritized over mappings with a lower priority." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_InputMapping;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Priority;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FInputMappingContextAndPriority>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::NewProp_InputMapping = { "InputMapping", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInputMappingContextAndPriority, InputMapping), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputMapping_MetaData), NewProp_InputMapping_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::NewProp_Priority = { "Priority", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInputMappingContextAndPriority, Priority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Priority_MetaData), NewProp_Priority_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::NewProp_InputMapping,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::NewProp_Priority,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Experience,
	nullptr,
	&NewStructOps,
	"InputMappingContextAndPriority",
	Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::PropPointers),
	sizeof(FInputMappingContextAndPriority),
	alignof(FInputMappingContextAndPriority),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FInputMappingContextAndPriority()
{
	if (!Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority.InnerSingleton, Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority.InnerSingleton;
}
// End ScriptStruct FInputMappingContextAndPriority

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
		{ "Comment", "/**\n *\x09\x09\n */" },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputConfig_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputMappingAndPrioritys_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/ExperiencePawnData.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_PawnClass;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DefaultCameraMode;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InputConfig;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InputMappingAndPrioritys_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InputMappingAndPrioritys;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExperiencePawnData>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_PawnClass = { "PawnClass", nullptr, (EPropertyFlags)0x0014000000000011, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperiencePawnData, PawnClass), Z_Construct_UClass_UClass, Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PawnClass_MetaData), NewProp_PawnClass_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_DefaultCameraMode = { "DefaultCameraMode", nullptr, (EPropertyFlags)0x0014000000000011, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperiencePawnData, DefaultCameraMode), Z_Construct_UClass_UClass, Z_Construct_UClass_UCommonCameraMode_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultCameraMode_MetaData), NewProp_DefaultCameraMode_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_InputConfig = { "InputConfig", nullptr, (EPropertyFlags)0x0114000000000011, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperiencePawnData, InputConfig), Z_Construct_UClass_UTagInputConfig_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputConfig_MetaData), NewProp_InputConfig_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_InputMappingAndPrioritys_Inner = { "InputMappingAndPrioritys", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInputMappingContextAndPriority, METADATA_PARAMS(0, nullptr) }; // 998434300
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_InputMappingAndPrioritys = { "InputMappingAndPrioritys", nullptr, (EPropertyFlags)0x0010000000000011, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExperiencePawnData, InputMappingAndPrioritys), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputMappingAndPrioritys_MetaData), NewProp_InputMappingAndPrioritys_MetaData) }; // 998434300
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExperiencePawnData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_PawnClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_DefaultCameraMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_InputConfig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_InputMappingAndPrioritys_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExperiencePawnData_Statics::NewProp_InputMappingAndPrioritys,
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
struct Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FInputMappingContextAndPriority::StaticStruct, Z_Construct_UScriptStruct_FInputMappingContextAndPriority_Statics::NewStructOps, TEXT("InputMappingContextAndPriority"), &Z_Registration_Info_UScriptStruct_InputMappingContextAndPriority, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FInputMappingContextAndPriority), 998434300U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExperiencePawnData, UExperiencePawnData::StaticClass, TEXT("UExperiencePawnData"), &Z_Registration_Info_UClass_UExperiencePawnData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExperiencePawnData), 1686357821U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_3128445046(TEXT("/Script/Experience"),
	Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperiencePawnData_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
