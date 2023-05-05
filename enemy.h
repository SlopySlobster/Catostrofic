#pragma once
#include "SFML/Graphics.hpp"
#include "globals.h"

class enemy {

public:
	enemy();
	void initEnemy(int x, int y, bool dead, int speed);
	bool isdead();
	void drawEnemy(sf::RenderWindow);
	void printInfo();
	bool chase(int x, int y);
	int getXpos();
	int getYpos();


private:
	int xpos;
	int ypos;
	bool dead;
	int speed;



};
