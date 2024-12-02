// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonCamera/Public/CommonCameraMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCommonCameraMode() {}

// Begin Cross Module References
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraMode();
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraMode_NoRegister();
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraModeStack();
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraModeStack_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_CommonCamera();
// End Cross Module References

// Begin Class UCommonCameraMode
void UCommonCameraMode::StaticRegisterNativesUCommonCameraMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCommonCameraMode);
UClass* Z_Construct_UClass_UCommonCameraMode_NoRegister()
{
	return UCommonCameraMode::StaticClass();
}
struct Z_Construct_UClass_UCommonCameraMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "CommonCameraMode.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/CommonCameraMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FOV_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "Public/CommonCameraMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlendTime_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "Public/CommonCameraMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FOV;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BlendTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonCameraMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCommonCameraMode_Statics::NewProp_FOV = { "FOV", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCameraMode, FOV), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FOV_MetaData), NewProp_FOV_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCommonCameraMode_Statics::NewProp_BlendTime = { "BlendTime", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCameraMode, BlendTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlendTime_MetaData), NewProp_BlendTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCommonCameraMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCameraMode_Statics::NewProp_FOV,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCameraMode_Statics::NewProp_BlendTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraMode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCommonCameraMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CommonCamera,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonCameraMode_Statics::ClassParams = {
	&UCommonCameraMode::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UCommonCameraMode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraMode_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraMode_Statics::Class_MetaDataParams), Z_Construct_UClass_UCommonCameraMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCommonCameraMode()
{
	if (!Z_Registration_Info_UClass_UCommonCameraMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonCameraMode.OuterSingleton, Z_Construct_UClass_UCommonCameraMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCommonCameraMode.OuterSingleton;
}
template<> COMMONCAMERA_API UClass* StaticClass<UCommonCameraMode>()
{
	return UCommonCameraMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCommonCameraMode);
UCommonCameraMode::~UCommonCameraMode() {}
// End Class UCommonCameraMode

// Begin Class UCommonCameraModeStack
void UCommonCameraModeStack::StaticRegisterNativesUCommonCameraModeStack()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCommonCameraModeStack);
UClass* Z_Construct_UClass_UCommonCameraModeStack_NoRegister()
{
	return UCommonCameraModeStack::StaticClass();
}
struct Z_Construct_UClass_UCommonCameraModeStack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "CommonCameraMode.h" },
		{ "ModuleRelativePath", "Public/CommonCameraMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraModeInstances_MetaData[] = {
		{ "ModuleRelativePath", "Public/CommonCameraMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraModeStack_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//0\xe4\xb8\xbaStack\xe7\x9a\x84\xe9\xa1\xb6\xef\xbc\x8cLast\xe5\x85\x83\xe7\xb4\xa0\xe4\xb8\xbaStack\xe7\x9a\x84\xe5\xba\x95\n" },
#endif
		{ "ModuleRelativePath", "Public/CommonCameraMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0\xe4\xb8\xbaStack\xe7\x9a\x84\xe9\xa1\xb6\xef\xbc\x8cLast\xe5\x85\x83\xe7\xb4\xa0\xe4\xb8\xbaStack\xe7\x9a\x84\xe5\xba\x95" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraModeInstances_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CameraModeInstances;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraModeStack_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CameraModeStack;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonCameraModeStack>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeInstances_Inner = { "CameraModeInstances", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UCommonCameraMode_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeInstances = { "CameraModeInstances", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCameraModeStack, CameraModeInstances), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraModeInstances_MetaData), NewProp_CameraModeInstances_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeStack_Inner = { "CameraModeStack", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UCommonCameraMode_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeStack = { "CameraModeStack", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCameraModeStack, CameraModeStack), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraModeStack_MetaData), NewProp_CameraModeStack_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCommonCameraModeStack_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeInstances_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeInstances,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeStack_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCameraModeStack_Statics::NewProp_CameraModeStack,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraModeStack_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCommonCameraModeStack_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_CommonCamera,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraModeStack_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonCameraModeStack_Statics::ClassParams = {
	&UCommonCameraModeStack::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UCommonCameraModeStack_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraModeStack_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraModeStack_Statics::Class_MetaDataParams), Z_Construct_UClass_UCommonCameraModeStack_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCommonCameraModeStack()
{
	if (!Z_Registration_Info_UClass_UCommonCameraModeStack.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonCameraModeStack.OuterSingleton, Z_Construct_UClass_UCommonCameraModeStack_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCommonCameraModeStack.OuterSingleton;
}
template<> COMMONCAMERA_API UClass* StaticClass<UCommonCameraModeStack>()
{
	return UCommonCameraModeStack::StaticClass();
}
UCommonCameraModeStack::UCommonCameraModeStack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCommonCameraModeStack);
UCommonCameraModeStack::~UCommonCameraModeStack() {}
// End Class UCommonCameraModeStack

// Begin Registration
struct Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCommonCameraMode, UCommonCameraMode::StaticClass, TEXT("UCommonCameraMode"), &Z_Registration_Info_UClass_UCommonCameraMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonCameraMode), 3366316947U) },
		{ Z_Construct_UClass_UCommonCameraModeStack, UCommonCameraModeStack::StaticClass, TEXT("UCommonCameraModeStack"), &Z_Registration_Info_UClass_UCommonCameraModeStack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonCameraModeStack), 3139174505U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_3931573446(TEXT("/Script/CommonCamera"),
	Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
