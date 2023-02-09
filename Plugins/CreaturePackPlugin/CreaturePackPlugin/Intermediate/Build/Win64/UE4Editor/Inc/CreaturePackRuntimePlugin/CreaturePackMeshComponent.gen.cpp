// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CreaturePackRuntimePlugin/Public/CreaturePackMeshComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCreaturePackMeshComponent() {}
// Cross Module References
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCreaturePackMeshComponent_NoRegister();
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCreaturePackMeshComponent();
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCustomPackProceduralMeshComponent();
	UPackage* Z_Construct_UPackage__Script_CreaturePackRuntimePlugin();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCreaturePackAnimationAsset_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UCreaturePackMeshComponent::execGetAttachmentPosition)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_vertex_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=P_THIS->GetAttachmentPosition(Z_Param_vertex_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCreaturePackMeshComponent::execSetShouldLoop)
	{
		P_GET_UBOOL(Z_Param_flagIn);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetShouldLoop(Z_Param_flagIn);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCreaturePackMeshComponent::execSetBlendActiveAnimation)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_name_in);
		P_GET_PROPERTY(FFloatProperty,Z_Param_factor);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBlendActiveAnimation(Z_Param_name_in,Z_Param_factor);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCreaturePackMeshComponent::execSetActiveAnimation)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_name_in);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetActiveAnimation(Z_Param_name_in);
		P_NATIVE_END;
	}
	void UCreaturePackMeshComponent::StaticRegisterNativesUCreaturePackMeshComponent()
	{
		UClass* Class = UCreaturePackMeshComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetAttachmentPosition", &UCreaturePackMeshComponent::execGetAttachmentPosition },
			{ "SetActiveAnimation", &UCreaturePackMeshComponent::execSetActiveAnimation },
			{ "SetBlendActiveAnimation", &UCreaturePackMeshComponent::execSetBlendActiveAnimation },
			{ "SetShouldLoop", &UCreaturePackMeshComponent::execSetShouldLoop },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics
	{
		struct CreaturePackMeshComponent_eventGetAttachmentPosition_Parms
		{
			int32 vertex_id;
			FVector ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_vertex_id;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::NewProp_vertex_id = { "vertex_id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CreaturePackMeshComponent_eventGetAttachmentPosition_Parms, vertex_id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CreaturePackMeshComponent_eventGetAttachmentPosition_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::NewProp_vertex_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::Function_MetaDataParams[] = {
		{ "Category", "Components|CreaturePack" },
		{ "Comment", "// Blueprint function that returns the world space position of a vertex by id. A value of -1 will result in the use of\n// the attach_vertex_id property value.\n" },
		{ "CPP_Default_vertex_id", "-1" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Blueprint function that returns the world space position of a vertex by id. A value of -1 will result in the use of\nthe attach_vertex_id property value." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCreaturePackMeshComponent, nullptr, "GetAttachmentPosition", nullptr, nullptr, sizeof(CreaturePackMeshComponent_eventGetAttachmentPosition_Parms), Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics
	{
		struct CreaturePackMeshComponent_eventSetActiveAnimation_Parms
		{
			FString name_in;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_name_in;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::NewProp_name_in = { "name_in", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CreaturePackMeshComponent_eventSetActiveAnimation_Parms, name_in), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::NewProp_name_in,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Components|CreaturePack" },
		{ "Comment", "// Blueprint version of setting the active animation name\n" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Blueprint version of setting the active animation name" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCreaturePackMeshComponent, nullptr, "SetActiveAnimation", nullptr, nullptr, sizeof(CreaturePackMeshComponent_eventSetActiveAnimation_Parms), Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics
	{
		struct CreaturePackMeshComponent_eventSetBlendActiveAnimation_Parms
		{
			FString name_in;
			float factor;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_name_in;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_factor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::NewProp_name_in = { "name_in", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CreaturePackMeshComponent_eventSetBlendActiveAnimation_Parms, name_in), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::NewProp_factor = { "factor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CreaturePackMeshComponent_eventSetBlendActiveAnimation_Parms, factor), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::NewProp_name_in,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::NewProp_factor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Components|CreaturePack" },
		{ "Comment", "// Blueprint version of setting the blended active animation name\n" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Blueprint version of setting the blended active animation name" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCreaturePackMeshComponent, nullptr, "SetBlendActiveAnimation", nullptr, nullptr, sizeof(CreaturePackMeshComponent_eventSetBlendActiveAnimation_Parms), Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics
	{
		struct CreaturePackMeshComponent_eventSetShouldLoop_Parms
		{
			bool flagIn;
		};
		static void NewProp_flagIn_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_flagIn;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::NewProp_flagIn_SetBit(void* Obj)
	{
		((CreaturePackMeshComponent_eventSetShouldLoop_Parms*)Obj)->flagIn = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::NewProp_flagIn = { "flagIn", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CreaturePackMeshComponent_eventSetShouldLoop_Parms), &Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::NewProp_flagIn_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::NewProp_flagIn,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::Function_MetaDataParams[] = {
		{ "Category", "Components|CreaturePack" },
		{ "Comment", "// Blueprint function to set whether the animation loops or not\n" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Blueprint function to set whether the animation loops or not" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCreaturePackMeshComponent, nullptr, "SetShouldLoop", nullptr, nullptr, sizeof(CreaturePackMeshComponent_eventSetShouldLoop_Parms), Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCreaturePackMeshComponent_NoRegister()
	{
		return UCreaturePackMeshComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCreaturePackMeshComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_creature_animation_asset_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_creature_animation_asset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_animation_speed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_animation_speed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_animation_frame_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_animation_frame;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_creature_debug_draw_MetaData[];
#endif
		static void NewProp_creature_debug_draw_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_creature_debug_draw;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_attach_vertex_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_attach_vertex_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_region_offset_z_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_region_offset_z;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCreaturePackMeshComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCustomPackProceduralMeshComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CreaturePackRuntimePlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCreaturePackMeshComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCreaturePackMeshComponent_GetAttachmentPosition, "GetAttachmentPosition" }, // 1315381171
		{ &Z_Construct_UFunction_UCreaturePackMeshComponent_SetActiveAnimation, "SetActiveAnimation" }, // 1243682481
		{ &Z_Construct_UFunction_UCreaturePackMeshComponent_SetBlendActiveAnimation, "SetBlendActiveAnimation" }, // 3232091606
		{ &Z_Construct_UFunction_UCreaturePackMeshComponent_SetShouldLoop, "SetShouldLoop" }, // 2461784844
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackMeshComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Rendering" },
		{ "Comment", "// UCreaturePackMeshComponent\n" },
		{ "HideCategories", "Mobility Trigger" },
		{ "IncludePath", "CreaturePackMeshComponent.h" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "UCreaturePackMeshComponent" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_animation_asset_MetaData[] = {
		{ "Category", "Components|CreaturePack" },
		{ "Comment", "/** Points to a Creature Pack Animation Asset containing the binary data of the character.*/" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Points to a Creature Pack Animation Asset containing the binary data of the character." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_animation_asset = { "creature_animation_asset", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackMeshComponent, creature_animation_asset), Z_Construct_UClass_UCreaturePackAnimationAsset_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_animation_asset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_animation_asset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_speed_MetaData[] = {
		{ "Category", "Components|CreaturePack" },
		{ "Comment", "/** Playback speed of the animation, 2.0 is the default */" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Playback speed of the animation, 2.0 is the default" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_speed = { "animation_speed", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackMeshComponent, animation_speed), METADATA_PARAMS(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_speed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_speed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_frame_MetaData[] = {
		{ "Category", "Components|CreaturePack" },
		{ "Comment", "/** Current frame of the animation during playback */" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Current frame of the animation during playback" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_frame = { "animation_frame", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackMeshComponent, animation_frame), METADATA_PARAMS(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_frame_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_frame_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_debug_draw_MetaData[] = {
		{ "Category", "Components|Creature" },
		{ "Comment", "/** Displays the bouding box */" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "Displays the bouding box" },
	};
#endif
	void Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_debug_draw_SetBit(void* Obj)
	{
		((UCreaturePackMeshComponent*)Obj)->creature_debug_draw = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_debug_draw = { "creature_debug_draw", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCreaturePackMeshComponent), &Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_debug_draw_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_debug_draw_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_debug_draw_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_attach_vertex_id_MetaData[] = {
		{ "Category", "Components|Creature" },
		{ "Comment", "/** An attachment vertex, the id of the vertex you want to attach by index */" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "An attachment vertex, the id of the vertex you want to attach by index" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_attach_vertex_id = { "attach_vertex_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackMeshComponent, attach_vertex_id), METADATA_PARAMS(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_attach_vertex_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_attach_vertex_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_region_offset_z_MetaData[] = {
		{ "Category", "Components|Creature" },
		{ "Comment", "/** The z value offset of each mesh region */" },
		{ "ModuleRelativePath", "Public/CreaturePackMeshComponent.h" },
		{ "ToolTip", "The z value offset of each mesh region" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_region_offset_z = { "region_offset_z", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackMeshComponent, region_offset_z), METADATA_PARAMS(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_region_offset_z_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_region_offset_z_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCreaturePackMeshComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_animation_asset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_speed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_animation_frame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_creature_debug_draw,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_attach_vertex_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackMeshComponent_Statics::NewProp_region_offset_z,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCreaturePackMeshComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCreaturePackMeshComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCreaturePackMeshComponent_Statics::ClassParams = {
		&UCreaturePackMeshComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCreaturePackMeshComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackMeshComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCreaturePackMeshComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCreaturePackMeshComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCreaturePackMeshComponent, 2151625052);
	template<> CREATUREPACKRUNTIMEPLUGIN_API UClass* StaticClass<UCreaturePackMeshComponent>()
	{
		return UCreaturePackMeshComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCreaturePackMeshComponent(Z_Construct_UClass_UCreaturePackMeshComponent, &UCreaturePackMeshComponent::StaticClass, TEXT("/Script/CreaturePackRuntimePlugin"), TEXT("UCreaturePackMeshComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCreaturePackMeshComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
