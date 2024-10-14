// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#include "LevelActors/Pickup/LMAHealthPickup.h"
#include "Components/LMAHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Player/LMADefaultCharacter.h"

ALMAHealthPickup::ALMAHealthPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereComponent);
}

void ALMAHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = this->GetActorLocation();
}

void ALMAHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALMAHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Charcter = Cast<ALMADefaultCharacter>(OtherActor);
	if (GivePickup(Charcter))
	{
		PickupWasTaken();
	}
}

bool ALMAHealthPickup::GivePickup(ALMADefaultCharacter* Character)
{
	const auto HealthComponent = Character->GetHealthComponent();
	if (!HealthComponent)
		return false;

	return HealthComponent->AddHealth(HealthFromPickup);
}

void ALMAHealthPickup::PickupWasTaken()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMAHealthPickup::RespawnPickup, RespawnTime);
}

void ALMAHealthPickup::RespawnPickup()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}

void ALMAHealthPickup::SinMovement()
{
	InitialLocation.Z += FMath::Sin(Frequency * GetWorld()->GetTimeSeconds()) * Amplitude;
	this->SetActorLocation(InitialLocation);
}

FVector ALMAHealthPickup::GetInitialLocation()
{
	return InitialLocation;
}

void ALMAHealthPickup::SetInitialLocation(FVector location)
{
	InitialLocation = location;
}