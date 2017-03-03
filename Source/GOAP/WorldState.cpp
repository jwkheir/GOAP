// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP.h"
#include "WorldState.h"

WorldState::WorldState()
{
	//state.Reserve(14);
	for (size_t i = PlayerDead - 1; i != OnGuard; i++)
	{
		WSType * ws = new WSType();
		state.Add(static_cast<Atom>(i + 1), *ws);
	}
}

bool WorldState::GetValue(Atom a)
{
	return state[a].value;
}

void WorldState::SetValue(Atom a, bool value)
{
	state[static_cast<Atom>(a)].value = value;
	state[static_cast<Atom>(a)].enabled = true;
}

bool WorldState::AreEqual(WorldState ws)
{
	for (size_t i = PlayerDead; i != OnGuard; i++)
	{
		Atom a = static_cast<Atom>(i);
		if (state[a].value != ws.state[a].value)
		{
			return false;
		}
	}
	return true;
}

bool WorldState::AreEnabledEqual(WorldState ws)
{
	for (size_t i = PlayerDead; i != OnGuard; i++)
	{
		Atom a = static_cast<Atom>(i);
		if (ws.state[a].enabled)
		{
			if (state[a].value != ws.state[a].value)
			{
				return false;
			}
		}
	}
	return true;
}

bool WorldState::GoalAchieved(WorldState goal)
{
	return AreEnabledEqual(goal);
}

bool WorldState::PreConditionsMeet(WorldState preconditions)
{
	return AreEnabledEqual(preconditions);
}

WorldState WorldState::GetWSWithEffectsApplied(WorldState effects)
{
	WorldState ws;
	for (size_t i = PlayerDead; i != OnGuard; i++)
	{
		Atom a = static_cast<Atom>(i);
		ws.state[a].value = state[a].value;
		ws.state[a].enabled = state[a].enabled;
	}

	for (size_t i = PlayerDead; i != OnGuard; i++)
	{
		Atom a = static_cast<Atom>(i);
		if (effects.state[a].value)
		{
			Atom a = static_cast<Atom>(i);
			ws.state[a].value = state[a].value;
			ws.state[a].enabled = state[a].enabled;
		}
	}
	return ws;
}

uint8 WorldState::GetNumberMismatchingAtoms(WorldState to)
{
	int mismatch = 0;
	for (size_t i = PlayerDead; i != OnGuard; i++)
	{
		Atom a = static_cast<Atom>(i);
		if (to.state[a].enabled)
		{
			if (state[a].value != to.state[a].value) mismatch++;
		}
	}
	return mismatch;
}

void WorldState::ApplyEffects(WorldState effects)
{
	for (size_t i = PlayerDead; i != OnGuard; i++)
	{
		Atom a = static_cast<Atom>(i);
		if (effects.state[a].value)
		{
			state[a].value = true;
		}
	}
}

WorldState::~WorldState()
{
}
