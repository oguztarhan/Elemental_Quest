// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyManager.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Game_Manager.generated.h"

UCLASS()
class ELEMENTAL_QUEST_API AGame_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGame_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddExp(int32 Amount);
	void LevelUp();
	void RespawnCharacter();

	FVector RespawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CurrentExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 StatPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 RequiredExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float attackDamage = 20.0f;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void IncreaseMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void IncreaseMaxMana();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void IncreaseAttackDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TSubclassOf<class UUserWidget> GameOverWidgetClass;

	class UUserWidget* GameOverWidgetInstance;

	FTimerHandle TimerHandle_GameOverWidget;

	bool bIsRespawning;
	void RespawnAfterDelay();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyManager")
	AEnemyManager* EnemyManager;

};
