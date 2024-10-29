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

	UFUNCTION(BlueprintCallable, Category = "Character")
	float GetStamina() const { return Stamina; };

	UFUNCTION(BlueprintCallable, Category = "Character")
	float GetSprinting() const { return IsSprinting; };

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnHealthChanged(float NewHealth);

	UFUNCTION(BlueprintNativeEvent, Category = "Character")
	void OnDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Weapon")
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
		
	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float SprintSpeedMultiplier = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float MaxStamina = 100.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float StaminaDrainRate = 50.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Components|Stamina")
	float StaminaRecoveryRate = 10.0f;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Stamina")
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
	float Stamina = 0.0f;	
	bool CanSprint = true;				

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Zoom(float Value);

	void StaminaManager();
	void StartSprinting();
	void StopSprinting();

	void RotationPlayerOnCursor();
};
