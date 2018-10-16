#ifndef _HELPERMATH_H_
#define _HELPERMATH_H_
#include <glm/vec2.hpp>
class HelperMath
{
public:

	static const glm::vec2& Lerp(const glm::vec2& a, const glm::vec2& b, const float &_t)
	{
		glm::vec2 ret{ 0.0f, 0.0f };
		ret = a + (_t * (b - a));
		return ret;
	}

	
	static const bool RectContainsPoint(const glm::vec2& posRect, const glm::vec2 sizeRect, const glm::vec2 &point)
	{
		if ((point.x < posRect.x + sizeRect.x && point.x > posRect.x) &&
			(point.y < posRect.y + sizeRect.y && point.y > point.y))
		{
			return true;
		}
		return false;
	}
};
#endif //!_HELPERMATH_H_