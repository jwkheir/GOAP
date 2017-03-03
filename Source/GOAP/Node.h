// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Actions/Action.h"
/**
 * 
 */
class GOAP_API Node
{
public:
	WorldState ws;
	uint8 g;
	uint8 h;
	uint8 f;
	Action * action;
	WorldState parentWS;
};
