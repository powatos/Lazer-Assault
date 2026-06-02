
#include <Game/Actors/Player.hpp>

#include <Debug/Debug.hpp>

#include "Lazer.hpp"

Lazer::Lazer() {
    SetMovability(ActorMovability::Static);
    SetCollisionType(CollisionType::Overlap);
    SetSimulatingPhysics(true);
    CheckCollisions = false;
}

void Lazer::OnHit(const HitResult& hit) {

    if (!CheckCollisions) { return; }


    if (Player* p = dynamic_cast<Player*>(hit.otherActor)) {
        p->AddHealth(-10);
        LOG_DEFAULT(LogType::INFO, "player hit!");
        CheckCollisions = false; // debounce additional hits for this wave
    }

}