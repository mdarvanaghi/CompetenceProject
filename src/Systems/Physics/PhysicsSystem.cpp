#include "Systems/Physics/PhysicsSystem.h"

namespace Motherload
{
    namespace Physics
    {
        std::vector<Collision*> PhysicsSystem::collisions;
        // Private
        Collision* PhysicsSystem::detectCollision(Collider* a, Collider* b)
        {
            /* Tutorial from https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331 */
            glm::vec2 deltaDirection = b->entity->transform->positionWorldSpace - a->entity->transform->positionWorldSpace;
            
            glm::vec2 aTopLeft = a->getTopLeft();
            glm::vec2 bTopLeft = b->getTopLeft();

            glm::vec2 aBottomRight = a->getBottomRight();
            glm::vec2 bBottomRight = b->getBottomRight();
            
            // Calculate half extents along x axis for each object
            float aExtent = (aBottomRight.x - aTopLeft.x) / 2.0f;
            float bExtent = (bBottomRight.x - bTopLeft.x) / 2.0f;
            
            // Calculate overlap on x axis
            float xOverlap = aExtent + bExtent - glm::abs(deltaDirection.x);
            
            // SAT test on x axis
            if (xOverlap < 0)
            {
                return nullptr;
            }
            // Calculate half extents along y axis for each object
            aExtent = (aBottomRight.y - aTopLeft.y) / 2.0f;
            bExtent = (bBottomRight.y - bTopLeft.y) / 2.0f;
        
            // Calculate overlap on y axis
            float yOverlap = aExtent + bExtent - glm::abs(deltaDirection.y);
        
            // SAT test on y axis
            if (yOverlap > 0.0f)
            {
                glm::vec2 normal;
                float penetration;

                // Find out which axis is axis of least penetration
                if (xOverlap < yOverlap)
                {
                    // Point towards B knowing that deltaDirection points from A to B
                    if (deltaDirection.x < 0.0f)
                    {
                        normal = Constants::right;
                    }
                    else
                    {
                        normal = Constants::left;
                    }

                    return new Collision(a->entity, b->entity, normal, xOverlap);
                }
                else
                {
                    // Point toward B knowing that deltaDirection points from A to B
                    if (deltaDirection.y < 0.0f)
                    {
                        normal = Constants::down;
                    }
                    else
                    {
                        normal = Constants::up;
                    }

                    return new Collision(a->entity, b->entity, normal, yOverlap);
                }
            }
            return nullptr;
        }

        void PhysicsSystem::resolveCollision(Collision* collision, float deltaTime)
        {
            DebugSystem::addDebugLine
            (
                collision->a->transform->positionWorldSpace,
                collision->normal,
                40.0f,
                Constants::debugLineColor
            );

            glm::vec2 relativeVelocity = (collision->a->velocity - collision->b->velocity) * deltaTime;
            float velocityAlongNormal = glm::dot(relativeVelocity, collision->normal);

            if (velocityAlongNormal > 0.0f)
            {
                return;
            }

            float minRestitution = glm::min(collision->a->restitution, collision->b->restitution);

            float impulseScalar = -(1.0f + minRestitution) * velocityAlongNormal;
            float massSum = collision->a->mass + collision->b->mass;
            glm::vec2 impulse = Constants::baseImpulse * impulseScalar * collision->normal;
            impulseScalar /= 1.0f / collision->a->mass + 1 / collision->b->mass;
            
            // Apply impulse to a
            float ratio = collision->a->mass / massSum;
            collision->a->addForce(ratio * impulse);

            // Apply impulse to b
            ratio = collision->b->mass / massSum;
            collision->b->addForce(ratio * impulse);

            // Adjust for sinking by correcting positions
            glm::vec2 correction = 
                glm::max(collision->penetration - Constants::correctionSlop, 0.0f)
                / (collision->a->inverseMass + collision->b->inverseMass)
                * Constants::correctionPercent * -collision->normal;

            collision->a->transform->positionWorldSpace -= collision->a->inverseMass * correction;
            collision->b->transform->positionWorldSpace += collision->b->inverseMass * correction;
        }

        // Public
        void PhysicsSystem::initialize()
        {
            collisions = std::vector<Collision*>();
        }

        void PhysicsSystem::step(float deltaTime)
        {
            /* Update dynamic entity positions */
            for (auto& entity : Game::instance->dynamicPhysicsEntities)
            {
                if (!entity->isDynamic)
                {
                    continue;
                }
                // Call physicsUpdate()
                entity->physicsUpdate(deltaTime);
                
                // Add gravity
                entity->velocity.y += Constants::gravity * deltaTime;

                // Limit velocity
                if (entity->velocity.x > entity->maxSpeedX) entity->velocity.x = entity->maxSpeedX;
                if (entity->velocity.x < -entity->maxSpeedX) entity->velocity.x = -entity->maxSpeedX;
                if (entity->velocity.y < -entity->maxSpeedY) entity->velocity.y = -entity->maxSpeedY;
                if (entity->velocity.y > entity->maxSpeedY) entity->velocity.y = entity->maxSpeedY;

                // Translate entity by velocity
                entity->transform->positionWorldSpace += entity->velocity;
            }
            /* Detect collisions */
            detectCollisions();
            if (!collisions.empty())
            {
                resolveCollisions(deltaTime);
            }

            /* Resolve collisions */
        }

        void PhysicsSystem::detectCollisions()
        {
            if (!Game::instance->player->isDynamic)
            {
                return;
            }
            for (auto& entity : Game::instance->staticPhysicsEntities)
            {
                /* Don't check for collisions if entities are far apart */
                if(glm::distance(Game::instance->player->transform->positionWorldSpace, entity->transform->positionWorldSpace) > 100.0f)
                {
                    continue;
                }

                Collision* collision = detectCollision(Game::instance->player->collider, entity->collider);
                
                if (collision != nullptr)
                {
                    collisions.push_back(collision);
                }
            }
        }

        void PhysicsSystem::resolveCollisions(float deltaTime)
        {
            for (auto& collision : collisions)
            {
                if (!collision->a->collider->isTrigger && !collision->b->collider->isTrigger)
                {
                    resolveCollision(collision, deltaTime);
                }
                collision->a->isColliding(collision->b);
                collision->b->isColliding(collision->a);
            }
            collisions.clear();
        }
    } // namespace Physics
} // namespace Motherload