// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Weapon/LMABaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

ALMABaseWeapon::ALMABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponMeshComponent);
}

void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();	
	
	CurrentAmmoWeapon = AmmoWeapon;
}

void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALMABaseWeapon::SpawnTrace(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceEffect, TraceStart);
	if (TraceFX)
	{
		TraceFX->SetNiagaraVariableVec3(TraceName, TraceEnd);
	}
}

void ALMABaseWeapon::Shoot()
{
	const FTransform SocketTransform = WeaponMeshComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	FVector TracerEnd = TraceEnd;

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		TracerEnd = HitResult.ImpactPoint;
	}

	SpawnTrace(TraceStart, TracerEnd);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootWave, TraceStart);
	DecrementBullets();
}

void ALMABaseWeapon::Fire()
{
	if (IsCurrentClipEmpty())
	{
		StopFire();
		return;
	}
	Shoot();
}

void ALMABaseWeapon::ChangeClip()
{
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

bool ALMABaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets == 0;
}

bool ALMABaseWeapon::IsClipFull() const
{
	return CurrentAmmoWeapon.Bullets == AmmoWeapon.Bullets;
}

void ALMABaseWeapon::DecrementBullets()
{
	CurrentAmmoWeapon.Bullets--;
	if (IsCurrentClipEmpty())
	{
		OnAmmoEmpty.Broadcast();
		StopFire();
		ChangeClip();
	}
}

void ALMABaseWeapon::StartFire()
{
	if (!IsCurrentClipEmpty() && !GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ALMABaseWeapon::Fire, 0.1f, true);
	}
}

void ALMABaseWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ALMABaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto Zombie = HitResult.GetActor();
    if (!Zombie) return;

    const auto Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!Pawn) return;

    const auto Controller = Pawn->GetController<APlayerController>();
    if (!Controller) return;

    Zombie->TakeDamage(Damage, FDamageEvent(), Controller, this);
}