#include "Physics.h"
#include "colliding.h"

Object::Object(float r, sf::Vector2f g,sf::Vector2f pos)
	: shape(r),gravity(g)
{
	shape.setFillColor(sf::Color(0, 0, 255));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1);
	shape.setPosition(pos);
	rect = r;
}

void Object::move_simulate()
{
	force -= gravity;
	shape.setPosition(shape.getPosition() + force);
}

void Object::collide_simulate()
{
	for (int i = 0; i < c_object.size(); i++)
	{
		if (ColC::isColliding(ColC::Circle(c_object[i]->shape.getRadius(), c_object[i]->shape.getPosition()), ColC::Circle(shape.getRadius(), shape.getPosition())))
		{
			float dis = ColC::getDistance(ColC::Circle(c_object[i]->shape.getRadius(), c_object[i]->shape.getPosition()), ColC::Circle(shape.getRadius(), shape.getPosition()));
			float overlap = 0.5 * (dis - c_object[i]->shape.getRadius() - shape.getRadius());
			std::cout << "overlap:" << overlap << std::endl;
			shape.setPosition(shape.getPosition() + sf::Vector2f(1, 1) * (overlap / 2));
			c_object[i]->shape.setPosition(c_object[i]->shape.getPosition() - sf::Vector2f(1, 1) * (overlap / 2));
		}
	}
}

sf::CircleShape Object::get_shape()
{
	return shape;
}

sf::VertexArray Object::get_force_line()
{
	return DRW::line(shape.getPosition()+sf::Vector2f(rect,rect), force*5.0f + shape.getPosition()+ sf::Vector2f(rect, rect),sf::Color::White);
}


void object_collider::collide_simulate()
{
	for (int i[2] = { 0,0 }; i[0] < c_object.size(); i[0]++)
	{
		for (i[1]=0; i[1] < c_object.size(); i[1]++)
		{
			if (i[0] == i[1]) continue;
			else
			{
				ColC::col_result r = 
					ColC::fixed_isColliding(
						ColC::Circle(c_object[i[0]]->shape.getRadius(), c_object[i[0]]->shape.getPosition()), 
						ColC::Circle(c_object[i[1]]->shape.getRadius(), c_object[i[1]]->shape.getPosition())
					);

				if (r.isColliding)
				{
					float overlap = 0.5 * (r.distance.distance - c_object[i[0]]->shape.getRadius() - c_object[i[1]]->shape.getRadius());
					c_object[i[1]]->shape.setPosition(c_object[i[1]]->shape.getPosition() + sf::Vector2f(r.distance.x, r.distance.y) * (overlap / 2));
					c_object[i[0]]->shape.setPosition(c_object[i[0]]->shape.getPosition() - sf::Vector2f(r.distance.x, r.distance.y) * (overlap / 2));
				}
			}
		}
	}
}