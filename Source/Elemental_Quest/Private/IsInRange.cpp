// Fill out your copyright notice in the Description page of Project Settings.


#include "IsInRange.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyKeys.h"
UIsInRange::UIsInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is player in Range");

}

void UIsInRange::OnBecomeRelevant(UBehaviorTreeComponent& pTreeComp, uint8* pNodeMem)
{
	
	Super::OnBecomeRelevant(pTreeComp, pNodeMem);

	AEnemyController* pAIController = Cast<AEnemyController>(pTreeComp.GetAIOwner());
	APawn* pEnemy = pAIController->GetPawn();

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	pAIController->GetBlackBoard()->SetValueAsBool(EnemyKeys::isInRange, pEnemy->GetDistanceTo(pPlayerController->GetPawn()) <= fRange);
	
}
