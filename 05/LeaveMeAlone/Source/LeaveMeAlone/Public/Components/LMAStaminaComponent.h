// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAStaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStamina);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULMAStaminaComponent();
	
	UFUNCTION(BlueprintCallable)
	float GetStamina() const { return Stamina; }

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChanged OnStaminaChanged;

protected:
	virtual void BeginPlay() override;		
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxStamina = 100.0f;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaDrainRate = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaRecoveryRate = 10.0f;	

private:
	float Stamina = 0.0f;
};
