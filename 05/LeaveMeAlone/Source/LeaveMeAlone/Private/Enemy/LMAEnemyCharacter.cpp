// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "Enemy/LMAEnemyCharacter.h"
#include "Components/LMAHealthComponent.h"


ALMAEnemyCharacter::ALMAEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
}

void ALMAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();		
	HealthComponent->OnHealthChanged.AddDynamic(this, &ALMAEnemyCharacter::OnHealthChanged);
}

void ALMAEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
