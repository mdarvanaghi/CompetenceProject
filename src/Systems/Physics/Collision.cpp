#include "Systems/Physics/Collision.h"

namespace Motherload
{
    namespace Physics
    {
        Collision::Collision(PhysicsEntity* a, PhysicsEntity* b, glm::vec2 normal, float penetration)
        {
            this->a = a;
            this->b = b;
            this->normal = normal;
            this->penetration = penetration;
        }
    } // namespace Physics
} // namespace Motherload