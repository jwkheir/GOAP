// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP.h"
#include "Action.h"

Action::Action(FString name, uint8 cost, UStateDrivenBrain *
	brain, UStateDrivenBrain::TacticalStates moveToState):GOAPAction(name, cost, moveToState)
{
	this->brain = brain;
}
Action::Action():GOAPAction(name, cost, moveToState)
{

}

ActionStates Action::Initialise()
{
	return ActionStates::Running;
}

void Action::CleanUp()
{

}

Action::~Action()
{
}
