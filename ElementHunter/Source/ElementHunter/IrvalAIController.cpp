// Fill out your copyright notice in the Description page of Project Settings.


#include "IrvalAIController.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::White,text)


AIrvalAIController::AIrvalAIController(const FObjectInitializer & PCIP) : Super(PCIP){

	
}

bool AIrvalAIController::InitializeBlackboard(UBlackboardComponent & BlackboardComp, UBlackboardData & BlackboardAsset)
{
	return Super::InitializeBlackboard(BlackboardComp,BlackboardAsset);
	
}

void AIrvalAIController::PauseLogic() {
	
	BrainComponent->StopLogic("Bananas");

}
void AIrvalAIController::ContinueLogic() {
	
	BrainComponent->RestartLogic();
	
}

void AIrvalAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	ACharacter* Samurai = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	
	if (Samurai != nullptr) {
		FVector locationToFollow;
		FlyingTimer -= DeltaTime;
		print("Gonna Fly at " + FString::SanitizeFloat(FlyingTimer));
		if (FlyingTimer <= 0) {

			Blackboard->SetValueAsBool(FName("isFlying"), !Blackboard->GetValueAsBool("isFlying"));
			FlyingTimer = defaultTimer;
		}
		FVector samLocation = Samurai->GetActorLocation();
		locationToFollow = samLocation;
		locationToFollow.Z = GetPawn()->GetActorLocation().Z;
	
		uint8 awakeKey = Blackboard->GetKeyID(FName("PatrolLocation"));
		
		Blackboard->SetValueAsVector(FName("PatrolLocation"),locationToFollow);
	}

}
void AIrvalAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	defaultTimer = FlyingTimer;

	RunBehaviorTree(BehaviorComp);
	Blackboard->SetValueAsBool(FName("isFlying"), false);
	//print("Doing magic");
}