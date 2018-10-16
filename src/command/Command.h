#ifndef _COMMAND_H_
#define _COMMAND_H_
#include <glm/vec2.hpp>
class Entity;
class Command
{
public:
	virtual ~Command() = default;

	virtual void Execute(const glm::vec2& inputPosition) = 0;
	virtual void Undo() = 0;

};
#endif // !_COMMAND_H_