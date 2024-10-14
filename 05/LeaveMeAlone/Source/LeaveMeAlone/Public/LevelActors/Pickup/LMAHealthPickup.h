// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMAHealthPickup.generated.h"

class USphereComponent;
class ALMADefaultCharacter;

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Mobility,
	Static
};

UCLASS()
class LEAVEMEALONE_API ALMAHealthPickup : public AActor
{
	GENERATED_BODY()

public:
	ALMAHealthPickup();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "5.0", ClampMax = "100.0"))
	float HealthFromPickup = 100.0f;

	UPROPERTY(EditInstanceOnly)
	float Frequency = 2.0;

	UPROPERTY(EditInstanceOnly)
	float Amplitude = 35.0;

	UPROPERTY(VisibleAnywhere)
	FVector InitialLocation;

	UFUNCTION(BlueprintCallable)
	FVector GetInitialLocation();

	UFUNCTION(BlueprintCallable)
	void SetInitialLocation(FVector location);

	UFUNCTION(BlueprintCallable)
	void SinMovement();

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	bool GivePickup(ALMADefaultCharacter* Character);
	void PickupWasTaken();
	void RespawnPickup();
};