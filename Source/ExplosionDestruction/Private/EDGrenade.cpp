// Fill out your copyright notice in the Description page of Project Settings.


#include "EDGrenade.h"


// Construct grenade with default values
AEDGrenade::AEDGrenade()
{
	// Projectile properties
	DestroyOnHit = false;
	DestroyOnOverlap = false;
	HitShooter = false;
	OverlapShooter = false;
	HitOthers = false;
	OverlapOthers = false;
	LifeSpan = 2.5f;

	Damage = 40.f;
	SelfDamage = true;
	SelfDamageScale = 0.5f;

	MovementComp->InitialSpeed = 1000.f;
	MovementComp->MaxSpeed = 1000.f;
	MovementComp->bSimulationEnabled = true;
	MovementComp->bShouldBounce = true;
	MovementComp->Bounciness = 0.4f;
	MovementComp->ProjectileGravityScale = 1.2f;


	// Explosive properties
	BlastRadius = 300.f;
	CausesKnockback = true;

	RadialForceComp->Radius = BlastRadius;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->ImpulseStrength = 2000.f;
	RadialForceComp->ForceStrength = 0.f; // we aren't using the force
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
}