#include <SFML/Graphics.hpp>
#include "Physics Engine/Physics.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define FPS 60

std::vector<Object> objects;
object_collider col;

void addObject(Object n)
{
	objects.push_back(n);
}

void addCollider()
{
	for (int i = 0; i < objects.size(); i++) col.c_object.push_back(&objects[i]);
}

int main()
{
	srand(time(NULL));



	sf::RenderWindow window(sf::VideoMode(1280,1024),"DRW and emils_physics");
	window.setFramerateLimit(FPS);

	sf::View view(sf::Vector2f(400, 300),sf::Vector2f(1280, 1024));

	float slowness = ((float)FPS*2) / (60.0f);
	std::cout << "Slowness:" << slowness << std::endl;

	for (int j = 0; j < 15; j++)
	{
		addObject(Object(rand()%250+1, sf::Vector2f(0, 0), sf::Vector2f(rand() % 1600, rand() % 1200)));
	}

	addCollider();

	bool right = false, left = false, up = false, down = false;
	view.setSize(800, 600);
	while (window.isOpen())
	{
		view.setCenter(objects[0].shape.getPosition()+sf::Vector2f(objects[0].shape.getRadius(), objects[0].shape.getRadius()));
		window.setView(view);
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) window.close();
			else if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::W) up = true;
				else if (e.key.code == sf::Keyboard::S) down = true;
				else if (e.key.code == sf::Keyboard::A) left = true;
				else if (e.key.code == sf::Keyboard::D) right = true;
			}
			else if (e.type == sf::Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::W) up = false;
				else if (e.key.code == sf::Keyboard::S) down = false;
				else if (e.key.code == sf::Keyboard::A) left = false;
				else if (e.key.code == sf::Keyboard::D) right = false;
			}
			else if (e.type == sf::Event::MouseWheelScrolled)
			{
				view.setSize(view.getSize() + sf::Vector2f(4,3)*e.mouseWheelScroll.delta*-25.0f);
				std::cout << e.mouseWheelScroll.delta << std::endl;
			}
		}
#define MOVE_SPEED 0.1/slowness
		if (up) objects[0].force += sf::Vector2f(0, -MOVE_SPEED);
		else if (down) objects[0].force += sf::Vector2f(0, MOVE_SPEED);
		else if (left) objects[0].force += sf::Vector2f(-MOVE_SPEED, 0);
		else if (right) objects[0].force += sf::Vector2f(MOVE_SPEED, 0);
		else objects[0].force = objects[0].force / 2.0f;

		window.clear();
		for (int i = 0; i < objects.size(); i++)
		{
			window.draw(objects[i].get_shape());
			window.draw(objects[i].get_force_line());
			col.collide_simulate();
			col.collide_simulate();
			objects[i].move_simulate();
		}
		window.display();
	}

	return 0;
}