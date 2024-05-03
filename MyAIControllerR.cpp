// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIControllerR.h"
#include "CReserch2/TestUnitC.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

ATestUnitC* actorr;

AMyAIControllerR::AMyAIControllerR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))){}

// Wait - стоит
// Move - получен приказ двигаться игнорирование врага
// Movego - приказ двигаться выполняется игнорирование врага
// MoveAAttack - получен приказ движение с возможностью атаки
// MoveAAttackgo - получен приказ движение с возможностью атаки
// MoveAttack - движение на замеченного врага
// Attack - бой
void AMyAIControllerR::MainLogic()
{
	if (actorr->orderType == "Wait")
	{
		//стою
		return;
	}
	if (actorr->orderType == "Move" || actorr->orderType == "MoveAAttack")
	{
		if ((actorr->orderTarget - actorr->GetActorLocation()).Size() > 80.0f)
		{
			MoveToLocation(actorr->orderTarget, 80.0f, true, false, false, false, DefaultNavigationFilterClass, true);
			
			//actorr->AddMovementInput(UKismetMathLibrary::GetDirectionUnitVector(actorr->GetActorLocation(), actorr->orderTarget), 1);
			
			actorr->SetActorRelativeRotation(FQuat(UKismetMathLibrary::FindLookAtRotation(actorr->GetActorLocation(), actorr->orderTarget)),false, 0, ETeleportType::None);
			
			if (actorr->orderType == "Move")
				actorr->orderType = "Movego";
			else
				actorr->orderType = "MoveAAttackgo";

			return;
		}
		else
		{
			actorr->orderType = "Wait";
			StopMovement();
			return;
		}
	}
	if (actorr->orderType == "MoveAAttackgo" || actorr->orderType == "Movego")
	{
		//actorr->AddMovementInput(UKismetMathLibrary::GetDirectionUnitVector(actorr->GetActorLocation(), actorr->orderTarget), 1);
		//MoveToLocation(actorr->orderTarget, 80.0f, true, false, false, false, DefaultNavigationFilterClass, true);
	}
	if (actorr->orderType == "MoveAttack")
	{
		if (actorr->orderEnemy == nullptr)
			return;

		if ((actorr->orderEnemy->GetActorLocation() - actorr->GetActorLocation()).Size() > 160.0f)
		{
			if ((actorr->orderEnemy->GetActorLocation() - actorr->GetActorLocation()).Size() > 1500.0f)
			{
				actorr->orderType = "Wait";
				StopMovement();
				return;
			}
			else
			{
				MoveToLocation(actorr->orderEnemy->GetActorLocation(), 80.0f, true, false, false, false, DefaultNavigationFilterClass, true);

				//actorr->AddMovementInput(UKismetMathLibrary::GetDirectionUnitVector(actorr->GetActorLocation(), actorr->orderEnemy->GetActorLocation()), 1);

				actorr->SetActorRelativeRotation(FQuat(UKismetMathLibrary::FindLookAtRotation(actorr->GetActorLocation(), actorr->orderEnemy->GetActorLocation())), false, 0, ETeleportType::None);
				return;
			}
		}
		else
		{
			actorr->orderType = "Attack";
			StopMovement();
			return;
		}
	}
	if (actorr->orderType == "Attack")
	{
		if ((actorr->orderEnemy->GetActorLocation() - actorr->GetActorLocation()).Size() > 1500.0f)
		{
			actorr->orderType = "Wait";
			actorr->isAttack = false;
			return;
		}
		else
		{
			ATestUnitC* Target = Cast<ATestUnitC>(actorr->orderEnemy);
			if (Target != nullptr)
			{
				if (Target->HP - actorr->Damage <= 0)
				{
					Target->Destroy();
					actorr->orderType = "Wait";
					actorr->isAttack = false;
					return;
				}
				else
				{
					actorr->SetActorRelativeRotation(FQuat(UKismetMathLibrary::FindLookAtRotation(actorr->GetActorLocation(), actorr->orderEnemy->GetActorLocation())), false, 0, ETeleportType::None);
					actorr->isAttack = true;
					Target->HP -= actorr->Damage;
					return;
				}
			}
			else
			{
				actorr->orderType = "Wait";
				actorr->isAttack = false;
				return;
			}
		}
	}
}

void AMyAIControllerR::Tick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("AAAAAAAAAAAA2"));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, actorr->GetName());
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::FromInt(a.Num()));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, a[i]->GetClass()->GetName());
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat(actorr->Team));

	Super::Tick(DeltaTime);
	actorr = Cast<ATestUnitC>(GetPawn());

	TArray<AActor*> a;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATestUnitC::StaticClass(), a);

	for (size_t i = 0; i < a.Num(); i++)
	{
		ATestUnitC* Target = Cast<ATestUnitC>(a[i]);
		if (Target != nullptr)
		{
			if (Target != actorr && Target->Team != actorr->Team)
			{
				if ((Target->GetActorLocation() - actorr->GetActorLocation()).Size() <= 500)
				{
					if (actorr->orderType == "MoveAAttackgo" || actorr->orderType == "Wait")
					{
						actorr->orderType = "MoveAttack";
						actorr->orderEnemy = Target;
					}
					if (actorr->orderType == "MoveAttack")
					{
						if (actorr->orderEnemy != nullptr)
						{
							if (Target != actorr->orderEnemy)
							{
								if ((actorr->orderEnemy->GetActorLocation() - actorr->GetActorLocation()).Size() > (Target->GetActorLocation() - actorr->GetActorLocation()).Size())
								{
									actorr->orderEnemy = Target;
								}
							}
						}
						else
						{
							actorr->orderEnemy = Target;
						}
					}
				}
			}
		}
	}

	/*if (actorr->DeltaTimeValue + DeltaTime < 1)
	{
		actorr->DeltaTimeValue += DeltaTime;
		return;
	}
	else
		actorr->DeltaTimeValue = 0;*/
	//actorr->DeltaTimeValue = 0;

	

	/*TArray<AActor*> a;

	TArray<UPrimitiveComponent*> b;

	UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(actorr->FindComponentByClass(UStaticMeshComponent::StaticClass()));
		
	SM->GetOverlappingActors(a);
	SM->GetOverlappingComponents(b);

	for (size_t i = 0; i < b.Num(); i++)
	{
		if (b[i]->GetOwner()->GetClass()->GetName() == TEXT("UnitM_C") && b[i]->GetName() != "TrigerMesh")
		{
			ATestUnitC* Target = Cast<ATestUnitC>(b[i]->GetOwner());

			if (Target != actorr && Target->Team != actorr->Team)
			{
				if (actorr->orderType == "MoveAAttackgo" || actorr->orderType == "Wait")
				{
					actorr->orderType = "MoveAttack";
					actorr->orderEnemy = Target;
				}
				if (actorr->orderType == "MoveAttack")
				{
					if (actorr->orderEnemy != nullptr)
					{
						if (Target != actorr->orderEnemy)
						{
							if ((actorr->orderEnemy->GetActorLocation() - actorr->GetActorLocation()).Size() > (Target->GetActorLocation() - actorr->GetActorLocation()).Size())
							{
								actorr->orderEnemy = Target;
							}
						}
					}
					else
					{
						actorr->orderEnemy = Target;
					}
				}
			}
		}
	}*/

	if (actorr->Team == 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("=================================="));
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::SanitizeFloat(DeltaTime));
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Order:"));
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, actorr->orderType);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("HP:"));
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::SanitizeFloat(actorr->HP));
		if (actorr->orderType == "MoveAttack")
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat((actorr->orderEnemy->GetActorLocation() - actorr->GetActorLocation()).Size()));
		}
	}
	MainLogic();
}

void AMyAIControllerR::BeginPlay()
{
	Super::BeginPlay();
	//actorr = Cast<ATestUnitC>(GetPawn());
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat(actorr->Team));
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("controller2"));
	
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, actorr->GetName());
	//Tick(1);
}