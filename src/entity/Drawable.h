#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_
#include <king/Engine.h>
namespace entity
{
	class Drawable
	{
		public:
			virtual ~Drawable() = default;
			virtual const King::Engine::Texture & GetTexture() const = 0;
			virtual void SetTexture(const King::Engine::Texture& _tex) = 0;
	};
}
#endif //_DRAWABLE_H_