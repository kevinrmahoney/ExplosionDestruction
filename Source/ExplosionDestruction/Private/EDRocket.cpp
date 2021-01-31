// Fill out your copyright notice in the Description page of Project Settings.


#include "EDRocket.h"

AEDRocket::AEDRocket()
{
	// Projectile properties
	DestroyOnHit = true;
	DestroyOnOverlap = false;
	HitShooter = false;
	OverlapShooter = false;
	HitOthers = true;
	OverlapOthers = false;
	LifeSpan = 100.f;

	Damage = 50.f;
	SelfDamage = true;
	SelfDamageScale = 0.5f;

	MovementComp->InitialSpeed = 2000.f;
	MovementComp->MaxSpeed = 2000.f;
	MovementComp->bSimulationEnabled = true;
	MovementComp->bShouldBounce = false;
	MovementComp->Bounciness = 0.f;
	MovementComp->ProjectileGravityScale = 0.f;


	// Explosive properties
	BlastRadius = 300.f;
	CausesKnockback = true;

	RadialForceComp->Radius = BlastRadius;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->ImpulseStrength = 1500.f;
	RadialForceComp->ForceStrength = 0.f; // we aren't using the force
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
}
