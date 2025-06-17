// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonCamera/Public/CommonCameraComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCommonCameraComponent() {}

// Begin Cross Module References
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraComponent();
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraComponent_NoRegister();
COMMONCAMERA_API UClass* Z_Construct_UClass_UCommonCameraModeStack_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent();
UPackage* Z_Construct_UPackage__Script_CommonCamera();
// End Cross Module References

// Begin Class UCommonCameraComponent
void UCommonCameraComponent::StaticRegisterNativesUCommonCameraComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCommonCameraComponent);
UClass* Z_Construct_UClass_UCommonCameraComponent_NoRegister()
{
	return UCommonCameraComponent::StaticClass();
}
struct Z_Construct_UClass_UCommonCameraComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Mobility Rendering LOD Trigger PhysicsVolume" },
		{ "IncludePath", "CommonCameraComponent.h" },
		{ "ModuleRelativePath", "Public/CommonCameraComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommonCameraModeStack_MetaData[] = {
		{ "ModuleRelativePath", "Public/CommonCameraComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CommonCameraModeStack;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonCameraComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCommonCameraComponent_Statics::NewProp_CommonCameraModeStack = { "CommonCameraModeStack", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCommonCameraComponent, CommonCameraModeStack), Z_Construct_UClass_UCommonCameraModeStack_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommonCameraModeStack_MetaData), NewProp_CommonCameraModeStack_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCommonCameraComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonCameraComponent_Statics::NewProp_CommonCameraModeStack,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCommonCameraComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCameraComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_CommonCamera,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonCameraComponent_Statics::ClassParams = {
	&UCommonCameraComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UCommonCameraComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCommonCameraComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UCommonCameraComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCommonCameraComponent()
{
	if (!Z_Registration_Info_UClass_UCommonCameraComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonCameraComponent.OuterSingleton, Z_Construct_UClass_UCommonCameraComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCommonCameraComponent.OuterSingleton;
}
template<> COMMONCAMERA_API UClass* StaticClass<UCommonCameraComponent>()
{
	return UCommonCameraComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCommonCameraComponent);
UCommonCameraComponent::~UCommonCameraComponent() {}
// End Class UCommonCameraComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCommonCameraComponent, UCommonCameraComponent::StaticClass, TEXT("UCommonCameraComponent"), &Z_Registration_Info_UClass_UCommonCameraComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonCameraComponent), 384780818U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraComponent_h_3242970879(TEXT("/Script/CommonCamera"),
	Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Projects_Angelscript_5_4_2_Samples_Games_Blot_Plugins_CommonCamera_Source_CommonCamera_Public_CommonCameraComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
