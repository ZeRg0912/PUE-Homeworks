// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "LMAEnemyCharacter.generated.h"

class ULMAHealthComponent;
class UBehaviorTree;


UCLASS()
class LEAVEMEALONE_API ALMAEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALMAEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
