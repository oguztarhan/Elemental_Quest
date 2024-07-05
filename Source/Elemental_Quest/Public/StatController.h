// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatController.generated.h"

UCLASS()
class ELEMENTAL_QUEST_API AStatController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void IncreaseHealth();

	UFUNCTION(BlueprintCallable)
	void IncreaseMana();

	UFUNCTION(BlueprintCallable)
	void IncreaseDamage();
};
