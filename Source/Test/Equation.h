// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>

enum operand {
	addition,
	subtraction,
	multiplication,
	division
};

/**
 * 
 */
class TEST_API Equation
{
public:
	Equation();
	~Equation();
	Equation(int x, int y, operand opNew);
	void SetEquation(int x, int y, operand opNew);
	int GetAnswer();
private:
	int var1, var2, answer;
	operand op;
};
