// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Weapon/LMABaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

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

void ALMABaseWeapon::Shoot()
{
	const FTransform SocketTransform = WeaponMeshComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
	}

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
	UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"), *FString::FromInt(CurrentAmmoWeapon.Bullets));
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