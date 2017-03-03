// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP.h"
#include "Astar.h"


Astar::Astar(TArray<Action*> actions)
{
	this->actions = actions;
	lowestNode = nullptr;
}

Node * Astar::GetMatchingNodeInConsidered(WorldState ws)
{
	for (int i = 0; i < considerNodes.Num(); i++) {
		Node * node = new Node();
		node = considerNodes[i];
		if (node->ws.AreEqual(ws)) return node;
	}
	return nullptr;
}

Node * Astar::GetMatchingNodeInVisited(WorldState ws)
{
	for (int i = 0; i < visistedNodes.Num(); i++) {
		Node * node = new Node();
		node = visistedNodes[i];
		if (node->ws.AreEqual(ws)) return node;
	}
	return nullptr;
}

TArray<Action*> Astar::GetPossibleTransitions(WorldState from, TArray<WorldState> &tos)
{
	TArray<Action*> transitions;
	for (int i = 0; i < actions.Num(); i++) {
		Action a = *actions[i];

		if (from.PreConditionsMeet(a.preConditions))
		{
			transitions.Add(&a);
			tos.Add(from.GetWSWithEffectsApplied(a.effects));
		}
	}
	return transitions;
}

TArray<Action*> Astar::ReconstructPlan(Node goalNode)
{
	Node * currentNode = new Node();
	currentNode = &goalNode;

	while (currentNode != nullptr && &currentNode->action != nullptr)
	{
		plan.Push(currentNode->action);
		currentNode = GetMatchingNodeInVisited(currentNode->parentWS);
	}
	return plan;
}

TArray<Action*> * Astar::GetPlan(WorldState start, Goal currentGoal)
{
	considerNodes.Empty();
	visistedNodes.Empty();
	WorldState goal = currentGoal.condition;

	Node * n0 = new Node();
	n0->ws = start;

	n0->g = 0;
	n0->h = start.GetNumberMismatchingAtoms(goal);
	n0->f = n0->g + n0->h;
	n0->action = nullptr;

	considerNodes.Add(n0);

	do
	{
		if (considerNodes.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("could not find plan"));
			return nullptr;
		}

		uint32 lowestVal = 100000;
		lowestNode = nullptr;
		for (int i = 0; i < considerNodes.Num(); i++) 
		{
			Node n = *considerNodes[i];

			if (n.f < lowestVal)
			{
				lowestVal = n.f;
				lowestNode = &n;
			}
		}

		currNode = lowestNode;
		if (considerNodes.Num() != 0)
		{
			uint32 foundIndex = considerNodes.Find(lowestNode);
			if (considerNodes.IsValidIndex(foundIndex))
			{
				considerNodes.RemoveAt(foundIndex);
			}
		}

		if (currNode->ws.GoalAchieved(goal))
		{
			tempPlans = ReconstructPlan(*currNode);
			return &tempPlans;
		}

		visistedNodes.Add(currNode);
		TArray<WorldState> tos;
		TArray<Action*> transitionActions = GetPossibleTransitions(currNode->ws, tos);

		uint8 index = 0;

		for (int i = 0; i < transitionActions.Num(); i++) 
		{
			Action * a = transitionActions[i];

			WorldState to = tos[index];
			index++;

			int cost = currNode->g + a->cost;

			Node * openNode = GetMatchingNodeInConsidered(to);

			Node * closedNode = GetMatchingNodeInVisited(to);

			if (openNode != nullptr && cost < closedNode->g)
			{
				uint32 foundIndex = visistedNodes.Find(closedNode);
				if (visistedNodes.IsValidIndex(foundIndex))
				{
					visistedNodes.RemoveAt(foundIndex);
				}
			}

			if (openNode == nullptr && closedNode == nullptr)
			{
				Node nb = Node();

				nb.ws = to;
				nb.g = cost;

				nb.h = nb.ws.GetNumberMismatchingAtoms(goal);
				nb.f = nb.g + nb.h;
				nb.action = a;

				nb.parentWS = currNode->ws;
				considerNodes.Add(&nb);
			}
		}
	} while (true);
}

Astar::~Astar()
{
	delete lowestNode;
}
