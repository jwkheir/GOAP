// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <stack>

#include "Node.h"
#include "Goal.h"
/**
 * 
 */
class GOAP_API Astar
{
public:
	TArray<Node*> considerNodes;
	TArray<Node*> visistedNodes;
	TArray<Action*> actions;
	TArray<Action*> plan;
	TArray<Action*> tempPlans;
	Node * currNode;
	Node * lowestNode;
public:
	Astar(TArray<Action*> actions);
	TArray<Action*> * GetPlan(WorldState start, Goal currentGoal);
	~Astar();
private:
	Node * GetMatchingNodeInConsidered(WorldState ws);
	Node * GetMatchingNodeInVisited(WorldState ws);
	TArray<Action*> GetPossibleTransitions(WorldState from, TArray<WorldState> &tos);
	TArray<Action*> ReconstructPlan(Node goalNode);
};

