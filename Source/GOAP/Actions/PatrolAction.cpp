// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP.h"
#include "PatrolAction.h"

PatrolAction::PatrolAction(FString name, uint8 cost, UStateDrivenBrain * tbrain, UStateDrivenBrain::TacticalStates moveToState):Action(name, cost, tbrain, moveToState)
{
}

ActionStates PatrolAction::Initialise()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Action : Patrol"));
	return ActionStates::Running;
}

ActionStates PatrolAction::Update()
{
	return ActionStates::Running;
}

void PatrolAction::CleanUp()
{
	UE_LOG(LogTemp, Warning, TEXT("End Action : Patrol"));
}

PatrolAction::~PatrolAction()
{
}
