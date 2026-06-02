#pragma once

#include <vector>
#include <Util/Vector2.hpp>

#include <Core/Control/Gamemode.hpp>

#include "Actors/Lazer.hpp"

class LazerAssault : public Gamemode
{
    
public:
    LazerAssault();
    virtual ~LazerAssault() = default;

    virtual void BeginPlay() override;

    void StartWave();
    void ActivateLazers();
    void FinishWave();

    void Flash();

    int GetScore();

private:
    Vector2 GetRandomPosition();
    bool GetRandomBool();
    bool bOn; 
    int currentIt; 
    int totalIts;

    int Score;

    std::vector<Lazer*> activeLazers;
};
