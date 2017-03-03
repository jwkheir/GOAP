// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef GOAL_H
#define GOAL_H
#include "WorldState.h"
/**
 * 
 */
class GOAP_API Goal
{
public:
	WorldState condition;
	uint8 priority;
public:
	Goal(uint8 priority);
	Goal();
};
#endif