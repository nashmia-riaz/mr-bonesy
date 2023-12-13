#include "Equation.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Equation.h"


Equation::Equation()
{
	var1 = var2 = 0;
	op = addition;
}

Equation::~Equation()
{
}

void Equation::SetEquation(int x, int y, operand opNew) {
	var1 = x;
	var2 = y;
	op = opNew;

	switch (op) {
		case addition:
			answer = var1 + var2;
			break;

		case subtraction:
			answer = var1 - var2;
			break;

		case multiplication:
			answer = var1 * var2;
			break;

		case division:
			answer = var1 / var2;
			break;
	}
}

int Equation::GetAnswer()
{
	return answer;
}
