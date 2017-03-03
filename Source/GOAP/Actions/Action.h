// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GOAPAction.h"
/**
 * 
 */
class GOAP_API Action : public GOAPAction
{
protected:
	UStateDrivenBrain * brain;
public:
	Action(FString name, uint8 cost, UStateDrivenBrain *
	 brain, UStateDrivenBrain::TacticalStates moveToState);
	Action();
	ActionStates Initialise();
	void CleanUp();
	~Action();
};