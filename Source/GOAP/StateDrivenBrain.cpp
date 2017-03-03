// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP.h"
#include "StateDrivenBrain.h"
#include "WorldState.h"
#include "Goal.h"
#include "Actions/Action.h"
#include "Actions/PatrolAction.h"
#include "Astar.h"

// Sets default values for this component's properties
UStateDrivenBrain::UStateDrivenBrain()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
	this->brain = this;
}


// Called when the game starts
void UStateDrivenBrain::BeginPlay()
{
	Super::BeginPlay();

	// ...
	currentGoal = new Goal();

	Action * patrol = new PatrolAction("Patrol", 1, brain, TacticalStates::Patrol);
	patrol->SetEffect(Atom::OnGuard, true);
	actions.Add(patrol);

	startWS = new WorldState();
	startWS->SetValue(Atom::OnGuard, false);


	Goal * patrolGoal = new Goal(1);
	patrolGoal->condition.SetValue(Atom::OnGuard, true);
	goals.Add(patrolGoal);
	currentGoal = patrolGoal;
	GenerateAStarPlan();
}


// Called every frame
void UStateDrivenBrain::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

Goal * UStateDrivenBrain::GetGoal()
{
	Goal * temp = nullptr;
	for (int i = 0; i < goals.Num(); i++)
	{
		Goal * g = goals[i];

		if (temp == nullptr)
		{
			temp = g;
		}
		else
		{
			if (temp->priority < g->priority)
			{
				temp = g;
			}
		}
	}
	return temp;
}

void UStateDrivenBrain::GenerateAStarPlan()
{
	UE_LOG(LogTemp, Warning, TEXT("Generating Plan"));
	Astar * astar = new Astar(actions);

	currentGoal = GetGoal();
	plan = *astar->GetPlan(*startWS, *currentGoal);

	if (plan.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Assigning Default Goal"));
		currentGoal = goals[0];
		plan = *astar->GetPlan(*startWS, *currentGoal);

		for (int i = 0; i < actions.Num(); i++)
		{
			//display action
			Action * a = actions[i];
			FString s = *a->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Action: %s"), *s);

		}
		return;
	}
	for (int i = 0; i < actions.Num(); i++)
	{
		//display action
		Action * a = actions[i];
		FString s = *a->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Action: %s"), *s);

	}
	currentAction = plan.Pop();

	//Set Init State FSM
}

void UStateDrivenBrain::CheckForNewGoal()
{

}