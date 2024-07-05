// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game_Manager.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AEnemy::HandleOnMontageEnded);

    worldspawnLocation = GetActorLocation();

    pEnemyManager = Cast<AEnemyManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyManager::StaticClass()));

    
	
}
void AEnemy::BeginPlayWithDelay()
{
   
}
// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Attack()
{

    UAnimInstance* pAnimInstance = GetMesh()->GetAnimInstance();
    if (pAnimInstance != nullptr)
    {
        if (pAttackMontage != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Saldýrýyorum"));
            pAnimInstance->Montage_Play(pAttackMontage);
            ACharacter* Ronan = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
            FDamageEvent DamageEvent;
            Ronan->TakeDamage(enemy_damage, DamageEvent, nullptr, this);

            if (pAttackSounds.Num() > 0)
            {
                UGameplayStatics::PlaySoundAtLocation(GetWorld(), pAttackSounds[FMath::RandRange(0, pAttackSounds.Num() - 1)], GetActorLocation());
            }
        }
    }
}

void AEnemy::TakeDamageX(float fDamage)
{
    UAnimInstance* pAnimInstance = GetMesh()->GetAnimInstance();
    if (pAnimInstance != nullptr)
    {
        if (pAnimInstance->Montage_IsPlaying(pDeathMontage))
        {
            return;
        }
    }
    if (pTakingDamageSounds!=nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), pTakingDamageSounds, GetActorLocation());
    }
    enemy_hp -= fDamage;
    if (enemy_hp <= 0)
    {
        AGame_Manager* GameManager = Cast<AGame_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGame_Manager::StaticClass()));
        if (GameManager)
        {
            UE_LOG(LogTemp, Warning, TEXT("5exp ekledim"));
            GameManager->AddExp(5);
        }
        Die();
    }
}
void AEnemy::Die()
{
    GetCharacterMovement()->StopMovementImmediately();
    GetCharacterMovement()->DisableMovement();
  
    DisableInput(nullptr);
    if (pDeathSounds.Num() > 0)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), pDeathSounds[FMath::RandRange(0, pDeathSounds.Num() - 1)], GetActorLocation());
    }

    UAnimInstance* pAnimInstance = GetMesh()->GetAnimInstance();
    if (pAnimInstance != nullptr)
    {
        if (pDeathMontage != nullptr) {
            pAnimInstance->Montage_Play(pDeathMontage);

            UE_LOG(LogTemp, Warning, TEXT("enemy ded"));
        }
        
    }
    
}
void AEnemy::Reset()
{
    if (pEnemyManager->bossSpawned == true)
    {
        Destroy();
        return;
    }
        TeleportTo(worldspawnLocation, GetActorRotation());
        UE_LOG(LogTemp, Error, TEXT("resetledik"));
        enemy_hp = 100.0f;
        isInCombat = false;
   
    
}

void AEnemy::HandleOnMontageEnded(UAnimMontage* Montage, bool Interrupted)
{
    if (Montage->GetName().Contains("Death"))
    {
        Reset();

        pEnemyManager->KillCount++;
        if (pEnemyManager->KillCount >= pEnemyManager->CurrentGroupSize)
        {
            pEnemyManager->updateGroupParameters();
            pEnemyManager->startNextGroup();

        }
        else
        {
            pEnemyManager->spawnMoreEnemy();
        }
    }
}

