// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class ULMAWeaponComponent;
class UAnimMontage;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALMADefaultCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; } 

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsSprinting = false;	

	virtual void BeginPlay() override;

private:
	float YRotation = -75.0f;
	float ArmLength = 2000.0f;
	float FOV = 55.0f;
	float MinArmLength = 500.0f;
	float MaxArmLength = 3000.0f;
	float ZoomSpeed = 100.0f;
		
	float DefaultWalkSpeed;
	float SprintSpeedMultiplier = 2.0f; 
	float Stamina = 100.0f;				
	float MaxStamina = 100.0f;			
	float StaminaDrainRate = 50.0f;		
	float StaminaRecoveryRate = 25.0f;	
	bool CanSprint = true;				

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Zoom(float Value);
	void StartSprinting();
	void StopSprinting();

	void OnDeath();
	void RotationPlayerOnCursor();

	void OnHealthChanged(float NewHealth);
};
