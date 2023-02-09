// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CreaturePackRuntimePlugin/Public/CreaturePackAnimationAsset.h"
#include "Serialization/ArchiveUObjectFromStructuredArchive.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCreaturePackAnimationAsset() {}
// Cross Module References
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCreaturePackAnimationAsset_NoRegister();
	CREATUREPACKRUNTIMEPLUGIN_API UClass* Z_Construct_UClass_UCreaturePackAnimationAsset();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_CreaturePackRuntimePlugin();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAssetImportData_NoRegister();
// End Cross Module References
	void UCreaturePackAnimationAsset::StaticRegisterNativesUCreaturePackAnimationAsset()
	{
	}
	UClass* Z_Construct_UClass_UCreaturePackAnimationAsset_NoRegister()
	{
		return UCreaturePackAnimationAsset::StaticClass();
	}
	struct Z_Construct_UClass_UCreaturePackAnimationAsset_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_animation_speed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_animation_speed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_collection_material_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_collection_material;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_CreatureZipBinary_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CreatureZipBinary_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_CreatureZipBinary;
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetImportData_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AssetImportData;
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_creature_filename_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_creature_filename;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_EDITORONLY_DATA
#endif // WITH_EDITORONLY_DATA
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CreaturePackRuntimePlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CreaturePackAnimationAsset.h" },
		{ "ModuleRelativePath", "Public/CreaturePackAnimationAsset.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_animation_speed_MetaData[] = {
		{ "Category", "Creature" },
		{ "ModuleRelativePath", "Public/CreaturePackAnimationAsset.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_animation_speed = { "animation_speed", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackAnimationAsset, animation_speed), METADATA_PARAMS(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_animation_speed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_animation_speed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_collection_material_MetaData[] = {
		{ "Category", "Creature" },
		{ "ModuleRelativePath", "Public/CreaturePackAnimationAsset.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_collection_material = { "collection_material", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackAnimationAsset, collection_material), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_collection_material_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_collection_material_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_CreatureZipBinary_Inner = { "CreatureZipBinary", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_CreatureZipBinary_MetaData[] = {
		{ "Comment", "// Zip Binary Data\n" },
		{ "ModuleRelativePath", "Public/CreaturePackAnimationAsset.h" },
		{ "ToolTip", "Zip Binary Data" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_CreatureZipBinary = { "CreatureZipBinary", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackAnimationAsset, CreatureZipBinary), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_CreatureZipBinary_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_CreatureZipBinary_MetaData)) };
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_AssetImportData_MetaData[] = {
		{ "Category", "ImportSettings" },
		{ "Comment", "// Denoting creature filename using UE4's asset registry system\n// keep in sync with creature_filename\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/CreaturePackAnimationAsset.h" },
		{ "ToolTip", "Denoting creature filename using UE4's asset registry system\nkeep in sync with creature_filename" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_AssetImportData = { "AssetImportData", nullptr, (EPropertyFlags)0x00220808000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackAnimationAsset, AssetImportData), Z_Construct_UClass_UAssetImportData_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_AssetImportData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_AssetImportData_MetaData)) };
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_creature_filename_MetaData[] = {
		{ "Comment", "// Denoting creature filename: stored as the creature runtime uses this in packaged builds\n// kept in sync with AssetImportData\n" },
		{ "ModuleRelativePath", "Public/CreaturePackAnimationAsset.h" },
		{ "ToolTip", "Denoting creature filename: stored as the creature runtime uses this in packaged builds\nkept in sync with AssetImportData" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_creature_filename = { "creature_filename", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCreaturePackAnimationAsset, creature_filename), METADATA_PARAMS(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_creature_filename_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_creature_filename_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_animation_speed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_collection_material,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_CreatureZipBinary_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_CreatureZipBinary,
#if WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_AssetImportData,
#endif // WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::NewProp_creature_filename,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCreaturePackAnimationAsset>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::ClassParams = {
		&UCreaturePackAnimationAsset::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCreaturePackAnimationAsset()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCreaturePackAnimationAsset_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCreaturePackAnimationAsset, 2980568032);
	template<> CREATUREPACKRUNTIMEPLUGIN_API UClass* StaticClass<UCreaturePackAnimationAsset>()
	{
		return UCreaturePackAnimationAsset::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCreaturePackAnimationAsset(Z_Construct_UClass_UCreaturePackAnimationAsset, &UCreaturePackAnimationAsset::StaticClass, TEXT("/Script/CreaturePackRuntimePlugin"), TEXT("UCreaturePackAnimationAsset"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCreaturePackAnimationAsset);
	IMPLEMENT_FSTRUCTUREDARCHIVE_SERIALIZER(UCreaturePackAnimationAsset)
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
