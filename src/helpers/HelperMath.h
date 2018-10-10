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
};
#endif //!_HELPERMATH_H_