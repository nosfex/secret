#ifndef _JEWEL_H_
#define _JEWEL_H_

#include "Entity.h"
#include "JewelType.h"
namespace entity
{
	class Jewel : public entity::Entity
	{
	public:
		Jewel();
		Jewel(const glm::vec2 pos, const King::Engine::Texture& tex);
		Jewel(const Jewel& other);
		virtual ~Jewel();

		void Update() override;
		void Update(const float& dt) override;
		void UpdateType(const JewelType& type);

		const JewelType& GetType() const { return mType; }

		glm::vec2 mGridPosition;
		float mDropSpeed;
	private:
		JewelType mType;
	};
}
#endif //!_JEWEL_H_