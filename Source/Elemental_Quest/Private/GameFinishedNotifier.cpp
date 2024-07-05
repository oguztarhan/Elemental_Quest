// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFinishedNotifier.h"
#include "GameFramework/HUD.h"
#include "UMG.h"
#include "Engine/World.h"

// Sets default values
AGameFinishedNotifier::AGameFinishedNotifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGameFinishedNotifier::ShowGameFinishedWidget()
{
    UUserWidget* hud = Cast<UUserWidget>(GetWorld()->GetFirstPlayerController()->GetHUD());
    if (hud)
    {
        //UUserWidget* gameFinishedWidget = hud->~UWidget;
       // if (gameFinishedWidget)
       // {
        //    gameFinishedWidget->AddToViewport();
       // }
    }
}

// Called when the game starts or when spawned
void AGameFinishedNotifier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameFinishedNotifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

