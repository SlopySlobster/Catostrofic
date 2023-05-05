#include <iostream>
#include "SFML/Graphics.hpp"
#include "globals.h"

using namespace std;

int main() {

	sf::RenderWindow screen(sf::VideoMode(1000, 1000), "Catostrofic");
	sf::Event event;
	sf::Clock clock;
	const float FPS = 60.0f;
	screen.setFramerateLimit(FPS);

	//load in images
	sf::Texture metal;
	metal.loadFromFile("wall.jpg");
	sf::Sprite wall;
	wall.setTexture(metal);

	sf::Texture panel;
	panel.loadFromFile("floor.png");
	sf::Sprite floor;
	floor.setTexture(panel);

	sf::Texture neko;
	neko.loadFromFile("cat.png");
	sf::IntRect cat(0, 0, 32, 32);
	sf::Sprite playerImg(neko, cat);


	//animation variables
	int ticker = 0;
	int rowNum = 0;
	int frameNum = 0;
	int direction = 0;

	int map[20][20] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,1,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,1,
		1,2,2,1,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,1,
		1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,2,2,2,2,1,
		1,2,2,2,2,1,2,2,2,2,2,1,2,1,2,1,2,1,1,1,
		1,2,1,1,1,1,2,1,1,1,2,1,2,1,2,1,2,2,2,1,
		1,2,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,1,
		1,2,1,2,1,1,2,1,1,2,2,1,2,1,1,1,1,1,2,1,
		1,2,1,2,1,2,2,1,2,2,2,1,2,2,2,2,2,2,2,1,
		1,2,1,2,1,2,2,1,2,2,2,1,2,1,1,1,1,1,2,1,
		1,2,2,2,1,2,2,1,1,2,2,1,2,2,2,2,2,2,2,1,
		1,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,1,2,2,1,
		1,2,1,1,1,1,1,1,1,1,2,1,2,2,2,2,1,1,2,1,
		1,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,1,2,2,1,
		1,2,1,2,2,1,2,1,1,1,2,1,1,1,2,2,1,2,1,1,
		1,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2,2,1,
		1,2,1,2,2,1,1,1,2,2,2,1,2,2,2,2,1,1,2,1,
		1,2,1,2,2,1,2,2,2,1,2,2,2,1,2,2,1,2,2,1,
		1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

	};


	//player setup 

	int xpos = 100;
	int ypos = 100;
	int vx = 0;
	int vy = 0;
	int sizex = 32;
	int sizey = 32;
	sf::RectangleShape player(sf::Vector2f(sizex, sizey));
	bool keys[] = { false, false, false, false };



	//enemys


	//Game loop--------------------------------------------------------------------------------------------

	while (screen.isOpen()) {

		while (screen.pollEvent(event)) { //event loop

			//checks if the x button on the top right corner of the window has been clicked
			if (event.type == sf::Event::EventType::Closed)
				screen.close();
			//Key input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				keys[LEFT] = true;
			}
			else keys[LEFT] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				keys[RIGHT] = true;
			}
			else keys[RIGHT] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				keys[UP] = true;
			}
			else keys[UP] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				keys[DOWN] = true;
			}
			else keys[DOWN] = false;

		} //end event loop

		//Movent Algorithm
		if (keys[LEFT] == true)
			vx = -2;

		else if (keys[RIGHT] == true)
			vx = 2;

		else
			vx = 0;

		if (keys[UP] == true)
			vy = -2;

		else if (keys[DOWN] == true)
			vy = 2;

		else {
			vy = 0;
		}

		//Colition----------------------------------


		//RIGHT collision
		if (vx > 0 && (map[(ypos) / 50][(xpos + sizex + vx) / 50] == 1 || map[(ypos + sizey) / 50][(xpos + sizex + vx) / 50] == 1))
		{
			cout << "right collision" << endl;
			vx = 0;
		}
		//LEFT collision
		if (vx < 0 && (map[(ypos) / 50][(xpos + vx) / 50] == 1 || map[(ypos + sizey) / 50][(xpos + vx) / 50] == 1))
		{
			cout << "left collision" << endl;
			vx = 0;
		}
		//UP collision
		if (vy < 0 && (map[(ypos + vy) / 50][(xpos) / 50] == 1 || map[(ypos + vy) / 50][(xpos + sizex) / 50] == 1))
		{
			cout << "up collision" << endl;
			vy = 0;
		}
		//DOWN collision
		if (vy > 0 && (map[(ypos + sizey + vy) / 50][(xpos) / 50] == 1 || map[(ypos + sizey + vy) / 50][(xpos + sizex) / 50] == 1))
		{
			cout << "down collision" << endl;
			vy = 0;
		}



		//player position
		xpos += vx;
		ypos += vy;
		player.setPosition(xpos, ypos);


		//Animation-----------------------------------------------

		if (vx != 0 || vy != 0) {
			ticker += 1;
			if (ticker % 10 == 0)
				frameNum += 1;

			if (frameNum > 3)
				frameNum = 0;

		}

		if (keys[DOWN] == true) rowNum = 0;
		else if (keys[RIGHT] == true) rowNum = 1;
		else if (keys[UP] == true) rowNum = 2;
		else if (keys[LEFT] == true) rowNum = 3;

		cat = sf::IntRect(frameNum * 32, rowNum * 32, 32, 32);
		sf::Sprite playerImg(neko, cat);
		playerImg.setPosition(xpos, ypos);


		//Game states-----------------------------------------------
		/*switch (current_state) {
		case MAP:
			

			break;
		case FIGHT:



		}*/




		//Render section-----------------------------------------------------------
		screen.clear();

		//map
		for (int rows = 0; rows < 20; rows++)
			for (int cols = 0; cols < 20; cols++) {

				if (map[rows][cols] == 1) {
					wall.setPosition(cols * 50, rows * 50);
					screen.draw(wall);
				}

				 if (map[rows][cols] == 2) {
					floor.setPosition(cols * 50, rows * 50);

					screen.draw(floor);

				}
			}

		screen.draw(playerImg);
		screen.display();

	}//end game loop-----------------------------------------------------------------------------------------------------------------------

}
