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
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xe8\xbf\x99\xe4\xb8\xa4\xe4\xb8\xaa\xe5\xb1\x9e\xe6\x80\xa7\xe6\x88\x91\xe4\xbb\xac\xe5\xb8\x8c\xe6\x9c\x9b\xe9\x95\xbf\xe6\x97\xb6\xe9\x97\xb4\xe5\xad\x98\xe5\x9c\xa8\xef\xbc\x8c\xe5\xa6\x82\xe6\x9e\x9c\xe4\xb8\x8d\xe5\x8a\xa0UPROPERTY(),\xe4\xbc\x9a\xe5\xaf\xbc\xe8\x87\xb4\xe8\x8e\xab\xe5\x90\x8d\xe5\x85\xb6\xe5\xa6\x99\xe7\x9a\x84\xe5\x86\x85\xe5\xad\x98\xe9\x97\xae\xe9\xa2\x98\xe5\x8d\xb3\xe8\xbf\x99\xe4\xb8\xa4\xe4\xb8\xaaTArray\xe8\xa2\xabGC\xe7\xb3\xbb\xe7\xbb\x9f\xe8\x8e\xab\xe5\x90\x8d\xe5\x85\xb6\xe5\xa6\x99\xe5\x9b\x9e\xe6\x94\xb6\xe4\xba\x86\n//\xe5\xbd\x93\xe4\xbd\xa0\xe5\x9c\xa8\xe4\xbd\xbf\xe7\x94\xa8\xe4\xb8\x80\xe4\xb8\xaa\xe6\x8c\x87\xe9\x92\x88\xe5\x89\x8d""check\xe4\xba\x86\xe5\xae\x83\xef\xbc\x8c\xe5\xa6\x82\xe6\x9e\x9c\xe4\xbd\xbf\xe7\x94\xa8\xe8\xbf\x87\xe7\xa8\x8b\xe4\xb8\xad\xe6\x8a\xa5\xe9\x94\x99\xef\xbc\x8c\xe9\x82\xa3\xe5\xa4\xa7\xe6\xa6\x82\xe7\x8e\x87\xe5\xb0\xb1\xe6\x98\xaf\xe8\xaf\xa5\xe6\x8c\x87\xe9\x92\x88\xe8\xa2\xab\xe5\x9e\x83\xe5\x9c\xbe\xe7\xb3\xbb\xe7\xbb\x9f\xe5\x9b\x9e\xe6\x94\xb6\xe4\xba\x86\xef\xbc\x8c\xe7\x94\xa8UPORPERTY()\xe5\x8f\xaf\xe4\xbb\xa5\xe8\xae\xa9GC\xe7\xb3\xbb\xe7\xbb\x9f\xe8\xbf\xbd\xe8\xb8\xaa\xe5\x85\xb6\xe7\x9a\x84\xe7\x94\x9f\xe5\x91\xbd\xe5\x91\xa8\xe6\x9c\x9f\xe4\xbf\x9d\xe6\x8c\x81\xe4\xb8\x8e""class\xe4\xb8\x80\xe8\x87\xb4?\n//\xe4\xbc\x98\xe5\x8c\x96\xe6\x80\xa7\xe8\x83\xbd\xef\xbc\x9a\xe4\xb8\x8d\xe5\xbf\x85\xe8\xa6\x81\xe7\x9a\x84 UPROPERTY() \xe4\xbc\x9a\xe5\xa2\x9e\xe5\x8a\xa0\xe5\xba\x8f\xe5\x88\x97\xe5\x8c\x96\xe5\x92\x8c\xe5\x8f\x8d\xe5\xb0\x84\xe8\xb4\x9f\xe6\x8b\x85\xef\xbc\x8c\xe5\xb0\xbd\xe9\x87\x8f\xe9\x81\xbf\xe5\x85\x8d\xe6\xbb\xa5\xe7\x94\xa8\xe3\x80\x82\n//\xe5\xbc\x95\xe6\x93\x8e\xe4\xb8\xad\xe7\x9a\x84 UObject \xe7\xb1\xbb\xe5\x9e\x8b\xe5\x8f\x98\xe9\x87\x8f\xef\xbc\x8c\xe5\xa6\x82\xe6\x9e\x9c\xe6\xb2\xa1\xe6\x9c\x89 UPROPERTY() \xe4\xbf\xae\xe9\xa5\xb0\xef\xbc\x8c\xe5\x9e\x83\xe5\x9c\xbe\xe5\x9b\x9e\xe6\x94\xb6\xe7\xb3\xbb\xe7\xbb\x9f\xef\xbc\x88GC\xef\xbc\x89\xe6\x97\xa0\xe6\xb3\x95\xe8\xaf\x86\xe5\x88\xab\xe5\xae\x83\xef\xbc\x8c\xe5\x8f\xaf\xe8\x83\xbd\xe5\xaf\xbc\xe8\x87\xb4\xe5\x85\xb6\xe6\x84\x8f\xe5\xa4\x96\xe8\xa2\xab\xe5\x9b\x9e\xe6\x94\xb6\xe3\x80\x82\n//\xe5\xa6\x82\xe6\x9e\x9c\xe6\x8c\x87\xe9\x92\x88\xe7\x9a\x84\xe5\xb0\xbd\xe5\xa4\xb4\xe4\xb8\xbaUObject\xe5\xaf\xb9\xe8\xb1\xa1\xef\xbc\x8c\xe9\x82\xa3\xe4\xb9\x88\xe8\xaf\xa5\xe5\xb1\x9e\xe6\x80\xa7\xe5\xb0\xb1\xe5\xba\x94\xe8\xaf\xa5\xe6\xa0\x87\xe8\xae\xb0\xe4\xb8\xbaUPROPERTY() \n" },
#endif
		{ "ModuleRelativePath", "Public/CommonCameraMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbf\x99\xe4\xb8\xa4\xe4\xb8\xaa\xe5\xb1\x9e\xe6\x80\xa7\xe6\x88\x91\xe4\xbb\xac\xe5\xb8\x8c\xe6\x9c\x9b\xe9\x95\xbf\xe6\x97\xb6\xe9\x97\xb4\xe5\xad\x98\xe5\x9c\xa8\xef\xbc\x8c\xe5\xa6\x82\xe6\x9e\x9c\xe4\xb8\x8d\xe5\x8a\xa0UPROPERTY(),\xe4\xbc\x9a\xe5\xaf\xbc\xe8\x87\xb4\xe8\x8e\xab\xe5\x90\x8d\xe5\x85\xb6\xe5\xa6\x99\xe7\x9a\x84\xe5\x86\x85\xe5\xad\x98\xe9\x97\xae\xe9\xa2\x98\xe5\x8d\xb3\xe8\xbf\x99\xe4\xb8\xa4\xe4\xb8\xaaTArray\xe8\xa2\xabGC\xe7\xb3\xbb\xe7\xbb\x9f\xe8\x8e\xab\xe5\x90\x8d\xe5\x85\xb6\xe5\xa6\x99\xe5\x9b\x9e\xe6\x94\xb6\xe4\xba\x86\n\xe5\xbd\x93\xe4\xbd\xa0\xe5\x9c\xa8\xe4\xbd\xbf\xe7\x94\xa8\xe4\xb8\x80\xe4\xb8\xaa\xe6\x8c\x87\xe9\x92\x88\xe5\x89\x8d""check\xe4\xba\x86\xe5\xae\x83\xef\xbc\x8c\xe5\xa6\x82\xe6\x9e\x9c\xe4\xbd\xbf\xe7\x94\xa8\xe8\xbf\x87\xe7\xa8\x8b\xe4\xb8\xad\xe6\x8a\xa5\xe9\x94\x99\xef\xbc\x8c\xe9\x82\xa3\xe5\xa4\xa7\xe6\xa6\x82\xe7\x8e\x87\xe5\xb0\xb1\xe6\x98\xaf\xe8\xaf\xa5\xe6\x8c\x87\xe9\x92\x88\xe8\xa2\xab\xe5\x9e\x83\xe5\x9c\xbe\xe7\xb3\xbb\xe7\xbb\x9f\xe5\x9b\x9e\xe6\x94\xb6\xe4\xba\x86\xef\xbc\x8c\xe7\x94\xa8UPORPERTY()\xe5\x8f\xaf\xe4\xbb\xa5\xe8\xae\xa9GC\xe7\xb3\xbb\xe7\xbb\x9f\xe8\xbf\xbd\xe8\xb8\xaa\xe5\x85\xb6\xe7\x9a\x84\xe7\x94\x9f\xe5\x91\xbd\xe5\x91\xa8\xe6\x9c\x9f\xe4\xbf\x9d\xe6\x8c\x81\xe4\xb8\x8e""class\xe4\xb8\x80\xe8\x87\xb4?\n\xe4\xbc\x98\xe5\x8c\x96\xe6\x80\xa7\xe8\x83\xbd\xef\xbc\x9a\xe4\xb8\x8d\xe5\xbf\x85\xe8\xa6\x81\xe7\x9a\x84 UPROPERTY() \xe4\xbc\x9a\xe5\xa2\x9e\xe5\x8a\xa0\xe5\xba\x8f\xe5\x88\x97\xe5\x8c\x96\xe5\x92\x8c\xe5\x8f\x8d\xe5\xb0\x84\xe8\xb4\x9f\xe6\x8b\x85\xef\xbc\x8c\xe5\xb0\xbd\xe9\x87\x8f\xe9\x81\xbf\xe5\x85\x8d\xe6\xbb\xa5\xe7\x94\xa8\xe3\x80\x82\n\xe5\xbc\x95\xe6\x93\x8e\xe4\xb8\xad\xe7\x9a\x84 UObject \xe7\xb1\xbb\xe5\x9e\x8b\xe5\x8f\x98\xe9\x87\x8f\xef\xbc\x8c\xe5\xa6\x82\xe6\x9e\x9c\xe6\xb2\xa1\xe6\x9c\x89 UPROPERTY() \xe4\xbf\xae\xe9\xa5\xb0\xef\xbc\x8c\xe5\x9e\x83\xe5\x9c\xbe\xe5\x9b\x9e\xe6\x94\xb6\xe7\xb3\xbb\xe7\xbb\x9f\xef\xbc\x88GC\xef\xbc\x89\xe6\x97\xa0\xe6\xb3\x95\xe8\xaf\x86\xe5\x88\xab\xe5\xae\x83\xef\xbc\x8c\xe5\x8f\xaf\xe8\x83\xbd\xe5\xaf\xbc\xe8\x87\xb4\xe5\x85\xb6\xe6\x84\x8f\xe5\xa4\x96\xe8\xa2\xab\xe5\x9b\x9e\xe6\x94\xb6\xe3\x80\x82\n\xe5\xa6\x82\xe6\x9e\x9c\xe6\x8c\x87\xe9\x92\x88\xe7\x9a\x84\xe5\xb0\xbd\xe5\xa4\xb4\xe4\xb8\xbaUObject\xe5\xaf\xb9\xe8\xb1\xa1\xef\xbc\x8c\xe9\x82\xa3\xe4\xb9\x88\xe8\xaf\xa5\xe5\xb1\x9e\xe6\x80\xa7\xe5\xb0\xb1\xe5\xba\x94\xe8\xaf\xa5\xe6\xa0\x87\xe8\xae\xb0\xe4\xb8\xbaUPROPERTY()" },
#endif
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
struct Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCommonCameraMode, UCommonCameraMode::StaticClass, TEXT("UCommonCameraMode"), &Z_Registration_Info_UClass_UCommonCameraMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonCameraMode), 3366316947U) },
		{ Z_Construct_UClass_UCommonCameraModeStack, UCommonCameraModeStack::StaticClass, TEXT("UCommonCameraModeStack"), &Z_Registration_Info_UClass_UCommonCameraModeStack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonCameraModeStack), 2346825000U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_3507617382(TEXT("/Script/CommonCamera"),
	Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
