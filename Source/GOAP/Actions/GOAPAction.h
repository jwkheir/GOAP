// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WorldState.h"
#include "StateDrivenBrain.h"
/**
 * 
 */

enum ActionStates { Success, Failed, Running };
class GOAP_API GOAPAction
{
public:
	WorldState preConditions;
	WorldState effects;
protected:
	FString name;
	UStateDrivenBrain::TacticalStates moveToState;
public:
	uint8 cost;
public:
	GOAPAction(FString name, uint8 cost, UStateDrivenBrain::TacticalStates moveToState);
	UStateDrivenBrain::TacticalStates GetMoveToState();
	FString GetName();
	uint8 GetCost();
	void SetPreConditions(Atom a, bool value);
	void SetEffect(Atom a, bool value);
	virtual ActionStates Initialise() { return ActionStates::Failed; };
	virtual ActionStates Update() { return ActionStates::Running; };
	virtual void CleanUp() {};
	~GOAPAction();
};
