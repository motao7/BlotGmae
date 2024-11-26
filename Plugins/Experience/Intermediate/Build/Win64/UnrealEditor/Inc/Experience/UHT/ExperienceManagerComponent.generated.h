// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ExperienceManagerComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef EXPERIENCE_ExperienceManagerComponent_generated_h
#error "ExperienceManagerComponent.generated.h already included, missing '#pragma once' in ExperienceManagerComponent.h"
#endif
#define EXPERIENCE_ExperienceManagerComponent_generated_h

#define FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnRep_CurrentExperience);


#define FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUExperienceManagerComponent(); \
	friend struct Z_Construct_UClass_UExperienceManagerComponent_Statics; \
public: \
	DECLARE_CLASS(UExperienceManagerComponent, UGameStateComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Experience"), NO_API) \
	DECLARE_SERIALIZER(UExperienceManagerComponent) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CurrentExperience=NETFIELD_REP_START, \
		NETFIELD_REP_END=CurrentExperience	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_25_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UExperienceManagerComponent(UExperienceManagerComponent&&); \
	UExperienceManagerComponent(const UExperienceManagerComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UExperienceManagerComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UExperienceManagerComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UExperienceManagerComponent) \
	NO_API virtual ~UExperienceManagerComponent();


#define FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_22_PROLOG
#define FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_25_INCLASS_NO_PURE_DECLS \
	FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> EXPERIENCE_API UClass* StaticClass<class UExperienceManagerComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Samples_Games_Blot_Plugins_Experience_Source_Experience_Public_ExperienceManagerComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
