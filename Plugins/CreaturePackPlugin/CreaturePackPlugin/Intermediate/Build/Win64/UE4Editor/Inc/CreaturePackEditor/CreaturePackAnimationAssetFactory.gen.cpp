// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CreaturePackEditor/Public/CreaturePackAnimationAssetFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCreaturePackAnimationAssetFactory() {}
// Cross Module References
	CREATUREPACKEDITOR_API UClass* Z_Construct_UClass_UCreaturePackAnimationAssetFactory_NoRegister();
	CREATUREPACKEDITOR_API UClass* Z_Construct_UClass_UCreaturePackAnimationAssetFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_CreaturePackEditor();
// End Cross Module References
	void UCreaturePackAnimationAssetFactory::StaticRegisterNativesUCreaturePackAnimationAssetFactory()
	{
	}
	UClass* Z_Construct_UClass_UCreaturePackAnimationAssetFactory_NoRegister()
	{
		return UCreaturePackAnimationAssetFactory::StaticClass();
	}
	struct Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_CreaturePackEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CreaturePackAnimationAssetFactory.h" },
		{ "ModuleRelativePath", "Public/CreaturePackAnimationAssetFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCreaturePackAnimationAssetFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics::ClassParams = {
		&UCreaturePackAnimationAssetFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCreaturePackAnimationAssetFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCreaturePackAnimationAssetFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCreaturePackAnimationAssetFactory, 3152499272);
	template<> CREATUREPACKEDITOR_API UClass* StaticClass<UCreaturePackAnimationAssetFactory>()
	{
		return UCreaturePackAnimationAssetFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCreaturePackAnimationAssetFactory(Z_Construct_UClass_UCreaturePackAnimationAssetFactory, &UCreaturePackAnimationAssetFactory::StaticClass, TEXT("/Script/CreaturePackEditor"), TEXT("UCreaturePackAnimationAssetFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCreaturePackAnimationAssetFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
