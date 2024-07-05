// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bossSpawned = false;
}

void AEnemyManager::SpawnFirstGroup()
{
	if (pEnemies.Num() > 0)
	{
		int spawnCount = 0;

		for (int i = 0;i < pEnemies.Num(); i++)
		{
			if (spawnCount== FirstGroupSpawnCount)
			{
				break;
			}

			AEnemy* pEnemy = Cast<AEnemy>(pEnemies[i]);

			pEnemy->SetActorEnableCollision(false);
			pEnemy->TeleportTo(mSpawnAreas[FMath::RandRange(0, mSpawnAreas.Num()-1)],pEnemy->GetActorRotation());
			pEnemy->SetActorEnableCollision(true);
			UE_LOG(LogTemp, Error, TEXT("spawnladik ilkgrup"));
			pEnemy->isInCombat = true;

			spawnCount++;
		}
	}
}

void AEnemyManager::updateGroupParameters()
{
	CurrentGroup += 1;
	KillCount = 0;
	CurrentGroupSize += 4;
	MaxEnemiesInArea += 2;

	if (MaxEnemiesInArea >= pEnemies.Num() - 2)
	{
		MaxEnemiesInArea = pEnemies.Num() - 2;
	}

	GlobalMaxWalkSpeed += 100.0f;
	if (GlobalMaxWalkSpeed > 400.0f)
	{
		GlobalMaxWalkSpeed = 400.0f;
	}
	GlobalMinWalkSpeed += 50.0f;
	if (GlobalMinWalkSpeed > 350.0f)
	{
		GlobalMinWalkSpeed = 350.0f;
	}
}

void AEnemyManager::startNextGroup()
{
	int spawnCount = 0;
	for (int i = 0;i < pEnemies.Num();i++)
	{
		if (spawnCount == MaxEnemiesInArea || spawnCount == CurrentGroupSize)
		{
			break;
		}
		AEnemy* pEnemy = Cast<AEnemy>(pEnemies[i]);

		if (!pEnemy->isInCombat)
		{
			pEnemy->SetActorEnableCollision(false);
			pEnemy->TeleportTo(mSpawnAreas[FMath::RandRange(0, mSpawnAreas.Num() - 1)], pEnemy->GetActorRotation());
			pEnemy->SetActorEnableCollision(true);
			UE_LOG(LogTemp, Error, TEXT("spawnladik nextgroup"));
			pEnemy->isInCombat = true;

			spawnCount++;
		}
	}
	ModifyGroupSpeeds();
}

void AEnemyManager::spawnMoreEnemy()
{
	int neededKill = CurrentGroupSize - KillCount;
	if (neededKill > 0)
	{
		if (GetAllEnemiesInCombat().Num() < neededKill)
		{
			if (GetAllEnemiesInCombat().Num() < MaxEnemiesInArea)
			{
				for (int i = 0;i < pEnemies.Num();i++)
				{
					AEnemy* pEnemy = Cast<AEnemy>(pEnemies[i]);

					if (!pEnemy->isInCombat)
					{
						pEnemy->SetActorEnableCollision(false);
						pEnemy->TeleportTo(mSpawnAreas[FMath::RandRange(0, mSpawnAreas.Num() - 1)], pEnemy->GetActorRotation());
						pEnemy->SetActorEnableCollision(true);
						UE_LOG(LogTemp, Error, TEXT("spawnladik morenemy"));
						pEnemy->isInCombat = true;
						
						break;
					
					}
				}
			}
		}
	}
}

TArray<AActor*> AEnemyManager::GetAllEnemiesInCombat()
{
	TArray<AActor*> pEnemiesInCombat = TArray<AActor*>();
	for (AActor* actor : pEnemies)
	{
		AEnemy* pEnemy = Cast<AEnemy>(actor);
		if (pEnemy->isInCombat)
		{
			pEnemiesInCombat.Add(actor);
		}
	}
	return pEnemiesInCombat;
}

void AEnemyManager::ModifyGroupSpeeds()
{
	for (int i = 0;i < pEnemies.Num();i++)
	{
		AEnemy* pEnemy = Cast<AEnemy>(pEnemies[i]);
		pEnemy->GetCharacterMovement()->MaxWalkSpeed = FMath::RandRange(GlobalMinWalkSpeed, GlobalMaxWalkSpeed);
	}
}
void AEnemyManager::ClearAllEnemies()
{
	for (AActor* actor : pEnemies)
	{
		if (actor)
		{
			actor->Destroy();
		}
	}
	pEnemies.Empty();
}

void AEnemyManager::SpawnBoss()
{
	if (bossSpawned == true)
	{
		return;
	}
	if (BossClass != nullptr && BossSpawnArea != nullptr)
	{
		bossSpawned = true;
		UE_LOG(LogTemp, Error, TEXT("spawnladik"));
		FVector BossSpawnLocation = BossSpawnArea->GetActorLocation();
		FRotator BossSpawnRotation = BossSpawnArea->GetActorRotation();

		AEnemy* boss = GetWorld()->SpawnActor<AEnemy>(BossClass, BossSpawnLocation, BossSpawnRotation);
		if (boss != nullptr)
		{
			boss->isInCombat = true;
			boss->SpawnDefaultController();
			
			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn boss!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Boss class or spawn area is not set!"));
	}
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), pEnemies);
	FTimerHandle pTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(pTimerHandle, [&]()
		{
			SpawnFirstGroup();
			ModifyGroupSpeeds();
		}, 3, false);

	CurrentGroupSize = FirstGroupSpawnCount;
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

