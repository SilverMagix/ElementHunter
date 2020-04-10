// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "IrvalPawnC.generated.h"

/**
 * 
 */
class UInputComponent;
class UPawnMovementComponent;
class USphereComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS(config = Game, Blueprintable, BlueprintType)
class ELEMENTHUNTER_API AIrvalPawnC : public APawn
{
	
		GENERATED_UCLASS_BODY()

	// Begin Pawn overrides
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;
	virtual void UpdateNavigationRelevance() override;
	// End Pawn overrides

	/**
	 * Input callback to move forward in local space (or backward if Val is negative).
	 * @param Val Amount of movement in the forward direction (or backward if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void MoveForward(float Val);

	/**
	 * Input callback to strafe right in local space (or left if Val is negative).
	 * @param Val Amount of movement in the right direction (or left if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void MoveRight(float Val);

	/**
	 * Input callback to move up in world space (or down if Val is negative).
	 * @param Val Amount of movement in the world up direction (or down if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void MoveUp_World(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void TurnAtRate(float Rate);

	/**
	* Called via input to look up at a given rate (or down if Rate is negative).
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		virtual void LookUpAtRate(float Rate);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;

public:
	/** Name of the MovementComponent.  Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName MovementComponentName;
	static FName MeshComponentName;

protected:
	/** DefaultPawn movement component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UPawnMovementComponent* MovementComponent;

public:
	/** Name of the CollisionComponent. */
	static FName CollisionComponentName;

private:
	/** DefaultPawn collision component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* CollisionComponent;
public:

	/** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName SkeletalComponentName;

private:
	/** The mesh associated with this Pawn. */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* SkeletalMeshComponent;
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	 void HitIrval(float WeaponInputDamage);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void AwakeIrval();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	 void EnableDamage(bool isAttack);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	 void Death();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	 void GoSleep();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	 void GoNuts();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	 void SetColor(FLinearColor Color);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	 void Testing(FLinearColor Color);
	/** If true, adds default input bindings for movement and camera look. */
	UPROPERTY(Category = Pawn, EditAnywhere, BlueprintReadOnly)
		uint32 bAddDefaultMovementBindings : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Awake = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* LookAT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HP = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MAX_HP = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACharacter* Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Dead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstanceDynamic* IrvalSkin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor AttackColor = FColor(1,1,1,1);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Enraged = false;


	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;
	/** Returns CollisionComponent subobject **/
	USphereComponent* GetCollisionComponent() const { return CollisionComponent; }
	/** Returns MeshComponent subobject **/
	USkeletalMeshComponent* GetMeshComponent() const { return SkeletalMeshComponent; }
	

};
