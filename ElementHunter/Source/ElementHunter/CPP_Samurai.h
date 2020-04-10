// Fill out your copyright notice in the Description page of Project Settings.
//---  ---//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"
#include "Engine.h"
#include "Engine/World.h"
/*
*/
#include "CPP_Samurai.generated.h"
/**
 *
 */
UCLASS()
class ELEMENTHUNTER_API ACPP_Samurai : public ACharacter
{
	GENERATED_BODY()

		//--- Get/Set Gobal Time Dilation.  ---//
	UFUNCTION(BlueprintCallable, Category = "Utilities|Time", meta = (WorldContext = "WorldContextObject"))
		static void SetGlobalTimeDilation(const UObject* WorldContextObject, float TimeDilation);

public:

	// Sets default values for this character's properties
	ACPP_Samurai();

//--- Stop Movement Immediately  ---//
	void Func_StopMovementImmediately();

//--- Teleport ---//
	void TeleportToIrval();

//--- Gravity ---//
	float disabledGravity = 0.0F;
	float enabledGravity = 1.0F;

	void SwitchGravity(bool gravityEnabled, float gravityScale);

//--- Time Dilation ---//
	float slowMotionSpeed = 0.01F;
	float RegularSpeed = 1.0F;
	float slowMoDuration = 10.0F;
	float skillCooldown = 10.0F;

	void TimeStop();
	void TimeResume();
	float TimeDilationRegulator(float regulatedTime);
	void Delay(float TimeSeconds, UWorld* World);

//--- Decoy ---//
	bool isDecoyHit;

	void DecoyHit();

//---- Do once -----//
	bool b_DoOnce;

	void DoOnce();
	void ResetDoOnce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};



