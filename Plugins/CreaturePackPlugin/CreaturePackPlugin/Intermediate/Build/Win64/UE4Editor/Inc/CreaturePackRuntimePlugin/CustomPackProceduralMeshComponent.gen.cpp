// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CreaturePackRuntimePlugin/Public/CustomPackProceduralMeshComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomPackProceduralMeshComponent() {}
// Cross Module References
	CREATUREPACKRUNTIMEPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FProceduralPackMeshTriangle();
	UPackage* Z_Construct_UPackage__Script_CreaturePackRuntimePlugin();
	CREATUREPACKRUNTIMEPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FProceduralPackMeshVertex();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCustomPackProceduralMeshComponent_NoRegister();
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCustomPackProceduralMeshComponent();
	ENGINE_API UClass* Z_Construct_UClass_UMeshComponent();
	ENGINE_API UClass* Z_Construct_UClass_UBodySetup_NoRegister();
// End Cross Module References
class UScriptStruct* FProceduralPackMeshTriangle::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CREATUREPACKRUNTIMEPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle, Z_Construct_UPackage__Script_CreaturePackRuntimePlugin(), TEXT("ProceduralPackMeshTriangle"), sizeof(FProceduralPackMeshTriangle), Get_Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Hash());
	}
	return Singleton;
}
template<> CREATUREPACKRUNTIMEPLUGIN_API UScriptStruct* StaticStruct<FProceduralPackMeshTriangle>()
{
	return FProceduralPackMeshTriangle::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FProceduralPackMeshTriangle(FProceduralPackMeshTriangle::StaticStruct, TEXT("/Script/CreaturePackRuntimePlugin"), TEXT("ProceduralPackMeshTriangle"), false, nullptr, nullptr);
static struct FScriptStruct_CreaturePackRuntimePlugin_StaticRegisterNativesFProceduralPackMeshTriangle
{
	FScriptStruct_CreaturePackRuntimePlugin_StaticRegisterNativesFProceduralPackMeshTriangle()
	{
		UScriptStruct::DeferCppStructOps<FProceduralPackMeshTriangle>(FName(TEXT("ProceduralPackMeshTriangle")));
	}
} ScriptStruct_CreaturePackRuntimePlugin_StaticRegisterNativesFProceduralPackMeshTriangle;
	struct Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vertex0_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vertex0;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vertex1_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vertex1;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vertex2_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vertex2;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FProceduralPackMeshTriangle>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex0_MetaData[] = {
		{ "Category", "Triangle" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex0 = { "Vertex0", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FProceduralPackMeshTriangle, Vertex0), Z_Construct_UScriptStruct_FProceduralPackMeshVertex, METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex0_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex0_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex1_MetaData[] = {
		{ "Category", "Triangle" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex1 = { "Vertex1", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FProceduralPackMeshTriangle, Vertex1), Z_Construct_UScriptStruct_FProceduralPackMeshVertex, METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex1_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex1_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex2_MetaData[] = {
		{ "Category", "Triangle" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex2 = { "Vertex2", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FProceduralPackMeshTriangle, Vertex2), Z_Construct_UScriptStruct_FProceduralPackMeshVertex, METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex2_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex2_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex0,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex1,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::NewProp_Vertex2,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CreaturePackRuntimePlugin,
		nullptr,
		&NewStructOps,
		"ProceduralPackMeshTriangle",
		sizeof(FProceduralPackMeshTriangle),
		alignof(FProceduralPackMeshTriangle),
		Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FProceduralPackMeshTriangle()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CreaturePackRuntimePlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ProceduralPackMeshTriangle"), sizeof(FProceduralPackMeshTriangle), Get_Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FProceduralPackMeshTriangle_Hash() { return 741708356U; }
class UScriptStruct* FProceduralPackMeshVertex::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CREATUREPACKRUNTIMEPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FProceduralPackMeshVertex, Z_Construct_UPackage__Script_CreaturePackRuntimePlugin(), TEXT("ProceduralPackMeshVertex"), sizeof(FProceduralPackMeshVertex), Get_Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Hash());
	}
	return Singleton;
}
template<> CREATUREPACKRUNTIMEPLUGIN_API UScriptStruct* StaticStruct<FProceduralPackMeshVertex>()
{
	return FProceduralPackMeshVertex::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FProceduralPackMeshVertex(FProceduralPackMeshVertex::StaticStruct, TEXT("/Script/CreaturePackRuntimePlugin"), TEXT("ProceduralPackMeshVertex"), false, nullptr, nullptr);
static struct FScriptStruct_CreaturePackRuntimePlugin_StaticRegisterNativesFProceduralPackMeshVertex
{
	FScriptStruct_CreaturePackRuntimePlugin_StaticRegisterNativesFProceduralPackMeshVertex()
	{
		UScriptStruct::DeferCppStructOps<FProceduralPackMeshVertex>(FName(TEXT("ProceduralPackMeshVertex")));
	}
} ScriptStruct_CreaturePackRuntimePlugin_StaticRegisterNativesFProceduralPackMeshVertex;
	struct Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Position;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Color;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_U_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_U;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_V_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_V;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FProceduralPackMeshVertex>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Position_MetaData[] = {
		{ "Category", "Triangle" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FProceduralPackMeshVertex, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Position_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Position_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Color_MetaData[] = {
		{ "Category", "Triangle" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FProceduralPackMeshVertex, Color), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Color_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Color_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_U_MetaData[] = {
		{ "Category", "Triangle" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_U = { "U", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FProceduralPackMeshVertex, U), METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_U_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_U_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_V_MetaData[] = {
		{ "Category", "Triangle" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_V = { "V", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FProceduralPackMeshVertex, V), METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_V_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_V_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Position,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_Color,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_U,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::NewProp_V,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CreaturePackRuntimePlugin,
		nullptr,
		&NewStructOps,
		"ProceduralPackMeshVertex",
		sizeof(FProceduralPackMeshVertex),
		alignof(FProceduralPackMeshVertex),
		Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FProceduralPackMeshVertex()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CreaturePackRuntimePlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ProceduralPackMeshVertex"), sizeof(FProceduralPackMeshVertex), Get_Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FProceduralPackMeshVertex_Hash() { return 2908909958U; }
	void UCustomPackProceduralMeshComponent::StaticRegisterNativesUCustomPackProceduralMeshComponent()
	{
	}
	UClass* Z_Construct_UClass_UCustomPackProceduralMeshComponent_NoRegister()
	{
		return UCustomPackProceduralMeshComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ModelBodySetup_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ModelBodySetup;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UMeshComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CreaturePackRuntimePlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Rendering" },
		{ "Comment", "/** Component that allows you to specify custom triangle mesh geometry */" },
		{ "HideCategories", "Mobility Trigger" },
		{ "IncludePath", "CustomPackProceduralMeshComponent.h" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
		{ "ToolTip", "Component that allows you to specify custom triangle mesh geometry" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::NewProp_ModelBodySetup_MetaData[] = {
		{ "Category", "Collision" },
		{ "Comment", "/** Description of collision */" },
		{ "ModuleRelativePath", "Public/CustomPackProceduralMeshComponent.h" },
		{ "ToolTip", "Description of collision" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::NewProp_ModelBodySetup = { "ModelBodySetup", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCustomPackProceduralMeshComponent, ModelBodySetup), Z_Construct_UClass_UBodySetup_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::NewProp_ModelBodySetup_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::NewProp_ModelBodySetup_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::NewProp_ModelBodySetup,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomPackProceduralMeshComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::ClassParams = {
		&UCustomPackProceduralMeshComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::PropPointers),
		0,
		0x00A010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCustomPackProceduralMeshComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCustomPackProceduralMeshComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCustomPackProceduralMeshComponent, 4047135096);
	template<> CREATUREPACKRUNTIMEPLUGIN_API UClass* StaticClass<UCustomPackProceduralMeshComponent>()
	{
		return UCustomPackProceduralMeshComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCustomPackProceduralMeshComponent(Z_Construct_UClass_UCustomPackProceduralMeshComponent, &UCustomPackProceduralMeshComponent::StaticClass, TEXT("/Script/CreaturePackRuntimePlugin"), TEXT("UCustomPackProceduralMeshComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomPackProceduralMeshComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
