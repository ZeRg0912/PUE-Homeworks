// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoEmpty);

class USkeletalMeshComponent;
class USoundWave;
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ALMABaseWeapon();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	USoundWave* ShootWave;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UNiagaraSystem* TraceEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FString TraceName = "Tracer";
	void SpawnTrace(const FVector& TraceStart, const FVector& TraceEnd);

	FOnAmmoEmpty OnAmmoEmpty;
	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

	virtual void Tick(float DeltaTime) override;

	void Fire();
	void StartFire();
	void StopFire();
	void ChangeClip();
	bool IsClipFull() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon {30, 0, true};
	
	virtual void BeginPlay() override;

	void Shoot();
	void DecrementBullets();
	bool IsCurrentClipEmpty() const;


private:
	FAmmoWeapon CurrentAmmoWeapon;
	FTimerHandle FireTimerHandle;
};
