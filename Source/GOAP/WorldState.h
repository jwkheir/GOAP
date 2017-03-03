// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WSType.h"
#include <iostream>
/**
 * 
 */
enum Atom { PlayerDead, HaveGun, HaveAmmo, InRange, InPlayerRoom, LocatedAtWindow, LocatedAtDoor, LocatedAtGun, KnowledgeOfGun, KnowledgeOfAmmo, KnowledgeOfWindow, KnowledgeOfDoor, DoorLocked, OnGuard };
class GOAP_API WorldState
{
private:
	TMap<Atom, WSType> state;
public:
	WorldState();
	bool GetValue(Atom a);
	void SetValue(Atom a, bool value);
	bool AreEqual(WorldState ws);
	bool AreEnabledEqual(WorldState ws);
	bool GoalAchieved(WorldState goal);
	bool PreConditionsMeet(WorldState preconditions);
	WorldState GetWSWithEffectsApplied(WorldState effects);
	uint8 GetNumberMismatchingAtoms(WorldState to);
	void ApplyEffects(WorldState effects);
	~WorldState();
};
