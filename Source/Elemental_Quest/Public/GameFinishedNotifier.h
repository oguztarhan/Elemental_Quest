// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFinishedNotifier.generated.h"

UCLASS()
class ELEMENTAL_QUEST_API AGameFinishedNotifier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameFinishedNotifier();

	UFUNCTION(BlueprintCallable, Category = "Game Finished")
	void ShowGameFinishedWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
