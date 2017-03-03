// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Engine.h"
//#include "Kismet/KismetStringLibrary.h"
#include <stack>
#include "Components/ActorComponent.h"
#include "StateDrivenBrain.generated.h"

class WorldState;
class Goal;
class Action;
class Astar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOAP_API UStateDrivenBrain : public UActorComponent
{
	GENERATED_BODY()
private:
	UStateDrivenBrain * brain;
public:
	WorldState * startWS;
	enum TacticalStates { Goto, Animate, UseSmartObject, Patrol };
	Goal * currentGoal;
	Action * currentAction;
	TArray<Goal*> goals;
	TArray<Action*> actions;
	TArray<Action*> plan;
public:	
	// Sets default values for this component's properties
	UStateDrivenBrain();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	void GenerateAStarPlan();
	Goal * GetGoal();
	void CheckForNewGoal();
	
};
