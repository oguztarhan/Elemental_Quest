// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsInRange.generated.h"


UCLASS()
class ELEMENTAL_QUEST_API UIsInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UIsInRange();

	void OnBecomeRelevant(UBehaviorTreeComponent& pTreeComp, uint8* pNodeMem);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float fRange = 100.0f;
};
