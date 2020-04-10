// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "ElementHunter.h"
#include "Engine.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "IrvalAIController.generated.h" 
/**
 *
 */
UCLASS()
class ELEMENTHUNTER_API AIrvalAIController : public AAIController
{
	GENERATED_BODY()
	
	
	bool InitializeBlackboard(UBlackboardComponent& BlackboardComp, UBlackboardData& BlackboardAsset);
	
public:
	
	AIrvalAIController(const FObjectInitializer& PCIP);
	UFUNCTION(BlueprintCallable)
	void PauseLogic();
	AIrvalAIController();
	UFUNCTION(BlueprintCallable)
	void ContinueLogic();

	/** This sets a Blackboard component*/
	void SetLaser(class ALaserAttractor* InLaser);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
private: 
	float defaultTimer;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTree* BehaviorComp;
	UPROPERTY(EditAnywhere)
		AActor* Irval;
	UPROPERTY(EditAnywhere)
		float FlyingTimer = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Awake;

};
