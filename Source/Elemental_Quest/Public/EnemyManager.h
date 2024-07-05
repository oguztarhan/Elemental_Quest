// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class ELEMENTAL_QUEST_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

	TArray<AActor*> pEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager");
	TArray<FVector> mSpawnAreas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager");
	int FirstGroupSpawnCount = 10;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager");
	int CurrentGroup = 1;

	int CurrentGroupSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager");
	int KillCount = 0;

	void SpawnFirstGroup();
	void updateGroupParameters();
	void startNextGroup();
	void spawnMoreEnemy();
	void ClearAllEnemies();
	void SpawnBoss();
	bool bossSpawned;
	TArray<AActor*> GetAllEnemiesInCombat();
	void ModifyGroupSpeeds();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	TSubclassOf<AActor> BossClass;

	UPROPERTY(EditAnywhere, Category = "Boss")
	AActor* BossSpawnArea;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private: 
	float GlobalMaxWalkSpeed = 800.0f;
	float GlobalMinWalkSpeed = 250.0f;

	int MaxEnemiesInArea = 25;

};
