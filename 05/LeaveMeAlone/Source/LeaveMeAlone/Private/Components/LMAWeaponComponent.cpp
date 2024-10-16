// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Components/LMAWeaponComponent.h"
#include "Weapon/LMABaseWeapon.h"
#include "Player/LMADefaultCharacter.h"

// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();		

	SpawnWeapon();
}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, SocketName);
		}
	}
}