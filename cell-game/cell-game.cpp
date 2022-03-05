// cell-game.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "playground.h"
#include <iostream>


int main() {
	Playground arena1(20,0.4f);
	/*Playground arena2(5,10,0.3f);*/
	/*Playground arena3(10);*/
	/*Playground arena4((uint16_t)5, (uint16_t)10);*/
	Playground arena5(5, 5, 6, 6, arena1.GetPlayground());
}