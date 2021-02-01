#include "DRW.h"

namespace DRW
{
	sf::VertexArray line(sf::Vector2f point1, sf::Vector2f point2, sf::Color c)
	{
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = point1;
		lines[1].position = point2;
		lines[0].color = c;
		lines[1].color = c;
		return lines;
	}
}