
//----- Includes -----//
#include "CPP_Samurai.h"
#include "Engine.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IrvalPawnC.h"

//----- Others  -----//
AIrvalPawnC* Irval;


//----- Functions -----//
#pragma region DefaultFunctions




// Sets default values
ACPP_Samurai::ACPP_Samurai()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPP_Samurai::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_Samurai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DecoyHit();
}

// Called to bind functionality to input
void ACPP_Samurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_Samurai::DecoyHit()
{
	if (isDecoyHit) //If decoy is hit.
	{
		DoOnce(); //Do it once
	}
	else return;
}

#pragma endregion

//----- Do once related Functions -----//
#pragma region Do Once 
				//Prevent method from being used over and over again.//
void ACPP_Samurai::DoOnce()
{
	if (b_DoOnce == false)
	{
		b_DoOnce = true;                       //Set variable to true, so it does not repeat
		TimeStop();							   //Stops time
		SwitchGravity(false, disabledGravity); //Disables gravity so player can stay mid-air
		TeleportToIrval();				       //Teleport player to Irval + position.z + 10.


		GetCharacterMovement()->StopMovementImmediately();             //Stops the inertial of the player above Irval.


		Delay(slowMoDuration, GetWorld());	  //Delay to let the player attack Irval.//

		TimeResume();						 //Resume time. 
		SwitchGravity(true, enabledGravity); //To let player fall back on the ground.

		Delay(skillCooldown, GetWorld());	 //Delay so player cannot use it another time.//

		ResetDoOnce();						 //Reset do once to allow it once again.//

		return;
	}
	else return;
}
//Resets DoOnce bool.//
void ACPP_Samurai::ResetDoOnce()
{
	b_DoOnce = false;
	return;
}
#pragma endregion

//----- Disable player's functionalities related Functions. -----//
#pragma region Player functionalities
				//Disables gravity to allow player to 
void ACPP_Samurai::SwitchGravity(bool gravityEnabled, float gravityScale)
{
	GetCapsuleComponent()->SetEnableGravity(gravityEnabled);
	GetMesh()->SetEnableGravity(gravityEnabled);
	GetCharacterMovement()->GravityScale = gravityScale;

	return;
}
//Stops the inertia of the player.//
void ACPP_Samurai::Func_StopMovementImmediately()
{
	GetCharacterMovement()->StopMovementImmediately();
	return;
}
#pragma endregion

//----- Time Related Functions. -----//
#pragma region Time functionalities
void ACPP_Samurai::TimeStop()
{
	//Variables.//
	float PlayerTimeDilation = 0.0F;

	PlayerTimeDilation = TimeDilationRegulator(slowMotionSpeed);


	SetGlobalTimeDilation(GetWorld(), slowMotionSpeed); //Set Global time Dilation
	SetGlobalTimeDilation(this, PlayerTimeDilation); //Player's time dilation != Global time Dilation, Player is equivalent to '1'

	return;
}
void ACPP_Samurai::TimeResume()
{	//Variables.//
	float PlayerTimeDilation = RegularSpeed;

	isDecoyHit = false;

	SetGlobalTimeDilation(GetWorld(), RegularSpeed); //Set Global time Dilation
	SetGlobalTimeDilation(this, PlayerTimeDilation);

	return;
}
//Custom Dilatation will always be '1' for the player, only one value to adjust. >If you adjust the Global time Dilation to be 2, the custom dilation will stil be the equivalent to be '1'.
float ACPP_Samurai::TimeDilationRegulator(float regulatedTime)
{
	//Exemple : Slowmotion time is 0.01 - to have the player move at 'normal speed' it would need to compensated for the 0.01 or 100x that speed. (0.01/0.01)/0.01 = 100;
	regulatedTime = ((slowMotionSpeed / slowMotionSpeed) / slowMotionSpeed);

	return regulatedTime;
}

void ACPP_Samurai::Delay(float TimeSeconds, UWorld* World)
{
	TimeSeconds = TimeDilationRegulator(slowMotionSpeed);
	float EndTime = World->TimeSeconds + TimeSeconds;
	for (; World->TimeSeconds < EndTime;);
	return;
}
void ACPP_Samurai::SetGlobalTimeDilation(const UObject * WorldContextObject, float TimeDilation)
{
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World != nullptr)
	{
		AWorldSettings* const WorldSettings = World->GetWorldSettings();
		if (WorldSettings != nullptr)
		{
			float const ActualTimeDilation = WorldSettings->SetTimeDilation(TimeDilation);
			if (TimeDilation != ActualTimeDilation)
			{
				UE_LOG(LogBlueprintUserMessages, Warning, TEXT("Time Dilation must be between %f and %f.  Clamped value to that range."), WorldSettings->MinGlobalTimeDilation, WorldSettings->MaxGlobalTimeDilation);
			}
		}
	}
}
#pragma endregion

//----- Teleport Functions. -----//
void ACPP_Samurai::TeleportToIrval()
{
	//Variables.//
	FVector IrvalLocation = Irval->GetActorLocation();
	FRotator IrvalRotation = Irval->GetActorRotation();

	//Adjustment.//
	IrvalLocation.Z += 10.0F;

	//Teleport to Irval's location and rotation.//
	this->SetActorLocationAndRotation(IrvalLocation, IrvalRotation);

	return;
}