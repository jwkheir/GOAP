// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Actions/Action.h"
/**
 * 
 */
class GOAP_API PatrolAction : public Action
{
public:
	PatrolAction(FString name, uint8 cost, UStateDrivenBrain * tbrain, UStateDrivenBrain::TacticalStates moveToState);
	virtual ActionStates Initialise() override;
	virtual ActionStates Update() override;
	virtual void CleanUp() override;
	~PatrolAction();
};
