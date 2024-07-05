// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"


UCLASS()
class ELEMENTAL_QUEST_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController(FObjectInitializer const& pObjectInit);

	void BeginPlay() override;
	void OnPossess(APawn* pPawn) override;

	class UBlackboardComponent* GetBlackBoard();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	class UBehaviorTreeComponent* pBehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* pBehaviorTree;

private:
	class UBlackboardComponent* pBlackBoard;
	FTimerHandle TimerHandle_BeginPlayDelay;
	void DelayedBeginPlay();
};
