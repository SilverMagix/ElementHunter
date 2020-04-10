// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIController.h"
#include "Animation/AnimMontage.h"
#include "BTTask_RandomGroundedAttackC.generated.h"


/**
 * 
 */
UCLASS()
class ELEMENTHUNTER_API UBTTask_RandomGroundedAttackC : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UBTTask_RandomGroundedAttackC(const FObjectInitializer& ObjectInitializer);
public:

	UPROPERTY(BlueprintReadWrite,Category="Components")
	USceneComponent* HandLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Particle Effects")
	UParticleSystem*  GroundPound;
	UPROPERTY(BlueprintReadWrite, Category = "Particle Effects")
	UParticleSystem* IceBreath;
	UPROPERTY(BlueprintReadWrite, Category = "Ice Breath Variables")
	FVector CenterLocation = FVector(-180,340,320);
	UPROPERTY(BlueprintReadWrite, Category = "Ice Breath Variables")
	float IceRotationTimer;
	UPROPERTY(BlueprintReadWrite, Category = "Ice Breath Variables")
	float IceRotationMax;
	UPROPERTY(BlueprintReadWrite, Category = "Color Switch")
	UMaterialInstanceDynamic* IrvalSkin;
	UPROPERTY(BlueprintReadWrite, Category = "Color Switch")
	TArray<FLinearColor> Colors = TArray<FLinearColor>(); 

	UPROPERTY(BlueprintReadWrite)
	TArray<UAnimMontage*> Attacks;
	//UPROPERTY(BlueprintReadWrite)
	
};
