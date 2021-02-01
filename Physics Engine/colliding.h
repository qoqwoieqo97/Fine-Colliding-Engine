#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

namespace Col
{
	struct vector
	{
		float x, y;
		vector(float ix = 0, float iy = 0)
		{
			x = ix; y = iy;
		}
	};
	struct collision
	{
		vector pos, size;
		collision(sf::Vector2f p, sf::Vector2f s)
		{
			pos = { p.x,p.y }; size = { s.x,s.y };
		}
	};

	bool isColliding(float a, float b, float sizeA, float sizeB)
	{
		return a <= b + sizeB && b <= a + sizeA;
	}

	bool isColliding(collision obj1, collision obj2)
	{
		return isColliding(obj1.pos.x, obj2.pos.x, obj1.size.x, obj2.size.x) && isColliding(obj1.pos.y, obj2.pos.y, obj1.size.y, obj2.size.y);
	}
}

namespace ColC
{
	struct Circle
	{
		float ch, x, y;
		Circle(float c, sf::Vector2f position)
		{
			ch = c; x = position.x + c; y = position.y + c;
		}
	};

	struct gdn_result
	{
		float distance; int x, y;
	};

	template<typename T>
	T i(T n)
	{
		if (n < 0)return n * -1;
		else return n;
	}
	template<typename T>
	int nepos(T n)
	{
		if (n < 0)return -1;
		if (n > 0) return 1;
		return 0;
	}

	float getDistance(Circle c1,Circle c2)
	{
		float xDistance = i<float>(c1.x - c2.x) ;
		float yDistance = i<float>(c1.y - c2.y);
		return hypot(xDistance, yDistance);
	}

	gdn_result getDistanceN(Circle c1, Circle c2)
	{
		float xDistance = c1.x - c2.x;
		float yDistance = c1.y - c2.y;
		return { hypot(xDistance, yDistance) ,nepos(xDistance),nepos(yDistance) };
	}

	bool isColliding(Circle c1, Circle c2)
	{
		return getDistance(c1, c2)<=(c1.ch+c2.ch);
	}
}