// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

AEnemyController::AEnemyController(FObjectInitializer const& pObjectInit)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> treeFinder(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_EnemyBT.BT_EnemyBT'"));
	if (treeFinder.Succeeded())
	{
		pBehaviorTree = treeFinder.Object;
	}

	pBehaviorTreeComponent = pObjectInit.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree Component"));
	pBlackBoard = pObjectInit.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard Component"));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(pBehaviorTree);
	pBehaviorTreeComponent->StartTree(*pBehaviorTree);
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle_BeginPlayDelay, this, &AEnemyController::DelayedBeginPlay, 2.0f, false);

	
}
void AEnemyController::DelayedBeginPlay()
{
	
}

void AEnemyController::OnPossess(APawn* pPawn)
{
	Super::OnPossess(pPawn);

	if (pBlackBoard)
	{
		pBlackBoard->InitializeBlackboard(*pBehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* AEnemyController::GetBlackBoard()
{
	return pBlackBoard;
}
