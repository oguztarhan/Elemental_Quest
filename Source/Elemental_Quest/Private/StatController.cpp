// Fill out your copyright notice in the Description page of Project Settings.


#include "StatController.h"
#include "Game_Manager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStatController::AStatController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStatController::BeginPlay()
{
	Super::BeginPlay();
   /* InputComponent->BindAction("IncreaseHealth", IE_Pressed, this, &AStatController::IncreaseHealth);
    InputComponent->BindAction("IncreaseMana", IE_Pressed, this, &AStatController::IncreaseMana);
    InputComponent->BindAction("IncreaseDamage", IE_Pressed, this, &AStatController::IncreaseDamage);*/
	
}

// Called every frame
void AStatController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStatController::IncreaseHealth()
{
    UE_LOG(LogTemp, Warning, TEXT("IncreaseHealth fonksiyonu cagirdimmm"));
    AGame_Manager* GameManager = Cast<AGame_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGame_Manager::StaticClass()));
    if (GameManager)
    {
        GameManager->IncreaseMaxHealth();
    }
}

void AStatController::IncreaseMana()
{
    UE_LOG(LogTemp, Warning, TEXT("IncreaseHmanah fonksiyonu çaðrýldý!"));
    AGame_Manager* GameManager = Cast<AGame_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGame_Manager::StaticClass()));
    if (GameManager)
    {
        GameManager->IncreaseMaxMana();
    }
}

void AStatController::IncreaseDamage()
{
    UE_LOG(LogTemp, Warning, TEXT("Increasedmaage fonksiyonu çaðrýldý!"));
    AGame_Manager* GameManager = Cast<AGame_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGame_Manager::StaticClass()));
    if (GameManager)
    {
        GameManager->IncreaseAttackDamage();
    }
}