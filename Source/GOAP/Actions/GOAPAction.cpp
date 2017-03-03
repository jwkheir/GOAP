// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP.h"
#include "GOAPAction.h"

GOAPAction::GOAPAction(FString name, uint8 cost, UStateDrivenBrain::TacticalStates moveToState)
{
	this->name = name;
	this->moveToState = moveToState;
	this->cost = cost;
	preConditions = WorldState();
	effects = WorldState();
}

UStateDrivenBrain::TacticalStates GOAPAction::GetMoveToState()
{
	return moveToState;
}


FString GOAPAction::GetName()
{
	return name;
}

uint8 GOAPAction::GetCost()
{
	return cost;
}

void GOAPAction::SetPreConditions(Atom a, bool value)
{
	preConditions.SetValue(a, value);
}

void GOAPAction::SetEffect(Atom a, bool value)
{
	effects.SetValue(a, value);
}



GOAPAction::~GOAPAction()
{
}
