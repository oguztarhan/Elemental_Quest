// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyManager.h"
#include "Enemy.generated.h"


UCLASS()
class ELEMENTAL_QUEST_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation")
	UAnimMontage* pAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* pDeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase*> pAttackSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase*> pDeathSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* pTakingDamageSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")

	float enemy_hp = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")

	float enemy_damage = 100.0f;
	FVector worldspawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool isInCombat = false;

	void Attack();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeDamageX(float fDamage);

	void Die();
	void Reset();

	UFUNCTION()
	void HandleOnMontageEnded(UAnimMontage* Montage, bool Interrupted);
private:
	AEnemyManager* pEnemyManager;
	FTimerHandle DelayTimerHandle;

	void BeginPlayWithDelay();
};
