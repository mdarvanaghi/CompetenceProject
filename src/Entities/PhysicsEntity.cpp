#include "Entities/PhysicsEntity.h"

namespace Motherload
{
    namespace Physics
    {
        void PhysicsEntity::addForce(glm::vec2 force)
        {
            this->velocity += force;
        }

        void PhysicsEntity::setMass(float mass)
        {
            this->mass = mass;
            this->inverseMass = mass ? 1.0f / mass : 0.0f;
        }
    } // namespace Physics
} // namespace Motherload
