// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyController.h"
#include "EnemyKeys.h"
#include "Kismet/GameplayStatics.h"

UBTT_ChasePlayer::UBTT_ChasePlayer(FObjectInitializer const& pObjectInit)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& pTreeComp, uint8* pNodeMem)
{
	auto const pAIController = Cast<AEnemyController>(pTreeComp.GetAIOwner());

	UNavigationSystemV1* pNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());


	if (pNavSystem)
	{
		FVector pLocation = pAIController->GetBlackBoard()->GetValueAsVector(EnemyKeys::targetLocation);

		pAIController->MoveToLocation(pLocation);
	}

	FinishLatentTask(pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
