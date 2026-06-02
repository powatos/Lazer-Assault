
#include <random>

#include <Game/World.hpp>
#include <Game/Actors/Block.hpp>
#include <Core/Control/GameInstance.hpp>
#include <Util/TimerManager.hpp>
#include <Util/GameplayHelper.hpp>
#include <Debug/Debug.hpp>

#include "LazerAssault.hpp"

SET_DEFAULT_SUBCLASS(Gamemode, LazerAssault)

LazerAssault::LazerAssault() {
    bOn = false;
    currentFlashIt = 0;
    totalFlashIts = 7;

    Score = 0;
    numLazers = 5;

    waveCooldown = 3.0;
    lazerFinishDelay = 1.5;
    activateLazersDelay = 1.0;
    lazerFlashDB = 0.1;

}

void LazerAssault::BeginPlay() {

    TimerManager* tm = TimerManager::Get();

    tm->AddTimer("waveDB", waveCooldown, this, &LazerAssault::StartWave);
}

void LazerAssault::StartWave() {

    const Vector2 lazerSize = Vector2(80, 1);

    World* world = GameInstance::Get()->GetWorld();
    TimerManager* tm = TimerManager::Get();

    // spawn lazers
    for (int i{}; i < numLazers; ++i) {
        const bool dir = GetRandomBool();
        const Vector2 size = dir ? lazerSize : lazerSize.Swizzled();
        const Vector2 pos = GetRandomPosition();
        const Vector2 spawnPos = dir ? pos : pos.Swizzled()+Vector2(0,24);

        Lazer* lazer = world->SpawnActor<Lazer>(spawnPos);
        lazer->SetSize(size);
        lazer->Texture = dir ? '-' : '|';

        activeLazers.push_back(lazer);
    }

    bOn = true;
    currentFlashIt = 0;
    Flash();

}

void LazerAssault::ActivateLazers() {
    TimerManager* tm = TimerManager::Get();
    Player* p = GameInstance::Get()->GetPlayerController()->GetPlayer();

    for (Lazer* lazer : activeLazers) {
        lazer->SetVisibility(true);
        lazer->CheckCollisions = true;
    }

    tm->AddTimer("waveFinishDelay", lazerFinishDelay, this, &LazerAssault::FinishWave);
}

void LazerAssault::Flash() {

    TimerManager* tm = TimerManager::Get();
    
    for (Lazer* lazer : activeLazers) {
        lazer->SetVisibility(bOn);
    }

    if (++currentFlashIt == totalFlashIts) {
        tm->AddTimer("activateLazers", activateLazersDelay, this, &LazerAssault::ActivateLazers);
        return;
    }

    bOn = !bOn;
    
    tm->AddTimer("flashDebounce", lazerFlashDB, this, &LazerAssault::Flash);

}

void LazerAssault::FinishWave() {
    World* world = GameInstance::Get()->GetWorld();

    LOG_DEFAULT(LogType::INFO, "Wave complete");

    // destroy lazers 
    for (auto it = activeLazers.begin(); it != activeLazers.end();) {
        world->DestroyActor(*it);
        it = activeLazers.erase(it);
    }

    ++Score;
    ++numLazers;

    if (Player* p = GameInstance::Get()->GetPlayerController()->GetPlayer(); p->GetHealth() > 0) {
        TimerManager* tm = TimerManager::Get();
        tm->AddTimer("waveDB", waveCooldown, this, &LazerAssault::StartWave);
    } else {
        GameInstance::Get()->RequestShutdown();
    }
}

int LazerAssault::GetScore() { return Score; }

Vector2 LazerAssault::GetRandomPosition() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.f, 1.f);

    return Vector2{
        0.f,
        distribution(generator) * 24
    };
}
bool LazerAssault::GetRandomBool() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(0, 1);

    return distribution(generator) == 1;
}
