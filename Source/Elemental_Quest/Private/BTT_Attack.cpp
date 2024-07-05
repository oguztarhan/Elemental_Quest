// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyKeys.h"


UBTT_Attack::UBTT_Attack(FObjectInitializer const& pObjectInit)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& pTreeComp, uint8* pNodeMem)
{
	AEnemyController* pAIController = Cast<AEnemyController>(pTreeComp.GetAIOwner());
	AEnemy* pEnemy = Cast<AEnemy>(pAIController->GetPawn());

	if (AttackMontageFinished(pEnemy))
	{
		bool bCanAttack = pAIController->GetBlackBoard()->GetValueAsBool(EnemyKeys::isInRange);
		if (bCanAttack)
		{
			pEnemy->Attack();
			UE_LOG(LogTemp, Warning, TEXT("ATAK YAPTÝM"));
		}
	}
	FinishLatentTask(pTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

bool UBTT_Attack::AttackMontageFinished(AEnemy* pEnemy)
{
	UAnimInstance* pAnimInstance = pEnemy->GetMesh()->GetAnimInstance();
	if (pAnimInstance != nullptr)
	{
		return pAnimInstance->Montage_GetIsStopped(pEnemy->pAttackMontage);
	}
	return false;
}
