// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP.h"
#include "Goal.h"

Goal::Goal(uint8 priority)
{
	this->priority = priority;
	condition = WorldState();
}

Goal::Goal()
{

}

