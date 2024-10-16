// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;
	
	UPROPERTY(EditDefaultsOnly)
	FName SocketName = "hand_r_Weapon_socket";

public:	
	ULMAWeaponComponent();

private:
	UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;

	void SpawnWeapon();
};
