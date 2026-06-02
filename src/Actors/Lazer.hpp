#pragma once

#include <Game/Actors/Block.hpp>

class Lazer : public Block
{
public:
    Lazer();

    virtual void OnHit(const HitResult&) override;

    bool CheckCollisions;
};