#include "Systems/Physics/PhysicsSystem.h"

namespace Motherload
{
    namespace Physics
    {
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
                        normal = glm::vec2(-1.0f, 0.0f);
                    }
                    else
                    {
                        normal = glm::vec2(1.0f, 0.0f);
                    }

                    return new Collision(a->entity, b->entity, normal, xOverlap);
                }
                else
                {
                    // Point toward B knowing that deltaDirection points from A to B
                    if (deltaDirection.y < 0.0f)
                    {
                        normal = glm::vec2(0.0f, -1.0f);
                    }
                    else
                    {
                        normal = glm::vec2(0.0f, 1.0f);
                    }

                    return new Collision(a->entity, b->entity, normal, yOverlap);
                }
            }
            return nullptr;
        }

        void PhysicsSystem::resolveCollision(Collision* collision)
        {
            DebugSystem::addDebugLine
            (
                collision->a->transform->positionWorldSpace,
                collision->normal,
                50.0f,
                Constants::debugLineColor,
                0.1f
            );

            DebugSystem::addDebugLine
            (
                collision->a->transform->positionWorldSpace,
                collision->b->transform->positionWorldSpace,
                collision->penetration, Constants::debugPenetrationColor,
                0.1f
            );
        }

        // Public
        void PhysicsSystem::step(float deltaTime)
        {
            /* Update dynamic entity positions */
            for (auto& entity : Game::instance->dynamicPhysicsEntities)
            {
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
            std::vector<Collision*> collisions = detectCollisions();
            if (!collisions.empty())
            {
                resolveCollisions(collisions);
            }

            /* Resolve collisions */
        }

        std::vector<Collision*> PhysicsSystem::detectCollisions()
        {
            std::vector<Collision*> collisions = std::vector<Collision*>();
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
            return collisions;
        }

        void PhysicsSystem::resolveCollisions(std::vector<Collision*> collisions)
        {
            for (auto& collision : collisions)
            {
                resolveCollision(collision);
            }
        }
    } // namespace Physics
} // namespace Motherload