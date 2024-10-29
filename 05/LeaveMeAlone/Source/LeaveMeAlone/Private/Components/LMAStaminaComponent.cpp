// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Components/LMAStaminaComponent.h"

ULMAStaminaComponent::ULMAStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void ULMAStaminaComponent::BeginPlay()
{
	Super::BeginPlay();	
	Stamina = MaxStamina;
}