#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../DRW/DRW.h"
#include <iostream>
class Object
{
private:
	sf::Vector2f gravity; float rect;
public:
	sf::CircleShape shape;
	sf::Vector2f force;
	std::vector<Object*> c_object;
	void move_simulate();
	void collide_simulate();
	sf::CircleShape get_shape();
	sf::VertexArray get_force_line();
	Object(float rect, sf::Vector2f gravity= sf::Vector2f(0,-9.81), sf::Vector2f pos=sf::Vector2f(0,50));
};
class object_collider
{
public:
	std::vector<Object*> c_object;
	void collide_simulate();
};