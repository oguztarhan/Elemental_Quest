// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Manager.h"
//#include "EnemyManager.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


AGame_Manager::AGame_Manager()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	CurrentExp = 0;
	CurrentLevel = 1;
	StatPoints = 0;
	MaxHealth = 200.0f;
	MaxMana = 150.0f;
	Health = 150.0f;
	RespawnLocation = FVector(-14724.718781,14335.967971,198.150005);
	bIsRespawning = false;
}


void AGame_Manager::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGame_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Health <= 0)
	{
		if (!bIsRespawning)
		{
			bIsRespawning = true;
			
			if (GameOverWidgetClass && !GameOverWidgetInstance)
			{
				UE_LOG(LogTemp, Warning, TEXT("widgetbuldum"));
				GameOverWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
				if (GameOverWidgetInstance)
				{
					ACharacter* Ronan = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
					GameOverWidgetInstance->AddToViewport();
					Ronan->SetActorLocation(RespawnLocation);
					GetWorldTimerManager().SetTimer(TimerHandle_GameOverWidget, this, &AGame_Manager::RespawnAfterDelay, 4.0f, false);

				}
			}
		}
	}

}
void AGame_Manager::RespawnAfterDelay()
{
	RespawnCharacter();
	bIsRespawning = false;

	if (GameOverWidgetInstance)
	{
		ACharacter* Ronan = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		GameOverWidgetInstance->RemoveFromViewport();
		GameOverWidgetInstance = nullptr;
	
	}
}

void AGame_Manager::AddExp(int32 Amount)
{
	CurrentExp += Amount;
	RequiredExp = CurrentLevel * 100;

	if (CurrentExp >= RequiredExp)
	{
		CurrentExp -= RequiredExp;
		LevelUp();
	}
}

void AGame_Manager::LevelUp()
{
	CurrentLevel++;
	StatPoints++;
	if (CurrentLevel == 10 && EnemyManager)
	{
		EnemyManager->ClearAllEnemies();
		EnemyManager->SpawnBoss();
	}
}
void AGame_Manager::IncreaseMaxHealth()
{
    if (StatPoints > 0)
    {
        MaxHealth += 10.0f;
		StatPoints--;
       
    }
    
}

void AGame_Manager::IncreaseMaxMana()
{
    if (StatPoints > 0)
    {
        MaxMana += 10.0f ;
		StatPoints--;
    }
}

void AGame_Manager::IncreaseAttackDamage()
{
    if (StatPoints > 0)
    {
        attackDamage += 5.0f;
        StatPoints--;
    }
}
void AGame_Manager::RespawnCharacter()
{
	// Get the player character
	ACharacter* Ronan = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (Ronan)
	{
		// Set the character's location to the respawn location

		// Reset the character's health
		Health = MaxHealth;

		// Optionally, reset other stats or effects
	}
}
