
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
    currentIt = 0;
    totalIts = 0;
    Score = 0;
}

void LazerAssault::BeginPlay() {

    TimerManager* tm = TimerManager::Get();

    tm->AddTimer("waveDB", 3.0, this, &LazerAssault::StartWave);
}

void LazerAssault::StartWave() {

    const int numLazers = 5;
    const Vector2 lazerSize = Vector2(80, 1);

    World* world = GameInstance::Get()->GetWorld();
    TimerManager* tm = TimerManager::Get();

    // spawn lazers
    for (int i{}; i < numLazers; ++i) {
        const bool b = GetRandomBool();
        const Vector2 size = b ? lazerSize : lazerSize.Swizzled();
        const Vector2 pos = GetRandomPosition();
        const Vector2 spawnPos = b ? pos : pos.Swizzled()+Vector2(0,24);

        Lazer* lazer = world->SpawnActor<Lazer>(spawnPos);
        lazer->SetSize(size);

        activeLazers.push_back(lazer);
    }

    bOn = true;
    currentIt = 0;
    totalIts = 5;
    Flash();

}

void LazerAssault::ActivateLazers() {
    TimerManager* tm = TimerManager::Get();
    Player* p = GameInstance::Get()->GetPlayerController()->GetPlayer();

    for (Lazer* lazer : activeLazers) {
        lazer->SetVisibility(true);
        lazer->CheckCollisions = true;
    }

    tm->AddTimer("waveFinishDelay", 1, this, &LazerAssault::FinishWave);
}

void LazerAssault::Flash() {
    LOG_DEFAULT(LogType::INFO, "{}", bOn);

    TimerManager* tm = TimerManager::Get();
    
    for (Lazer* lazer : activeLazers) {
        lazer->SetVisibility(bOn);
    }

    if (++currentIt == totalIts) {
        ActivateLazers();
        return;
    }

    bOn = !bOn;
    
    tm->AddTimer("flashDebounce", 0.25, this, &LazerAssault::Flash);

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

    if (Player* p = GameInstance::Get()->GetPlayerController()->GetPlayer(); p->GetHealth() > 0) {
        TimerManager* tm = TimerManager::Get();
        tm->AddTimer("waveDB", 3.0, this, &LazerAssault::StartWave);
    } else {
        GameInstance::Get()->RequestShutdown();
    }
}

int LazerAssault::GetScore() { return Score; }

Vector2 LazerAssault::GetRandomPosition() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.f, 1.f);

    return Vector2{
        // distribution(generator) * 80,
        0.f,
        distribution(generator) * 24
    };
}
bool LazerAssault::GetRandomBool() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(0, 1);

    return distribution(generator) == 1;
}
