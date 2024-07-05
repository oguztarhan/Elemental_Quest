// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpell.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Game_Manager.h"


AProjectileSpell::AProjectileSpell()
{
 	
	PrimaryActorTick.bCanEverTick = false;


	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Spell"));
	RootComponent = ProjectileMesh;
    ProjectileMesh->SetNotifyRigidBodyCollision(true);
    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileSpell::OnHit);
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->InitialSpeed = 5000;
	ProjectileComponent->MaxSpeed = 15000;
    
    

}

// Called when the game starts or when spawned
void AProjectileSpell::BeginPlay()
{
	Super::BeginPlay();
    
	
}

// Called every frame
void AProjectileSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectileSpell::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //UE_LOG(LogTemp, Warning, TEXT("ONHIT CALISIYOR"));
    if (OtherActor != nullptr && OtherActor != this)
    {
        if (ExplosionEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
        }
        if (ExplosionSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
        }
        AEnemy* HitEnemy = Cast<AEnemy>(OtherActor);
        if (HitEnemy != nullptr)
        {
            AGame_Manager* GameManager = Cast<AGame_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGame_Manager::StaticClass()));
            if (GameManager)
            {
                float Damage = GameManager->attackDamage;
                HitEnemy->TakeDamageX(Damage);
            }
        }
       
        Destroy();
    }
}

