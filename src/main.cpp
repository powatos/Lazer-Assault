
#include <Core/PotatoEngine.hpp>
#include <Core/Control/GameInstance.hpp>
#include <Core/Data/PersistentLevel.hpp>
#include <Game/World.hpp>
#include <UI/HUDController.hpp>

#include "UI/ScoreWidget.hpp"

int main()
{
    /// ENGINE SETUP
    PotatoEngine& engine = PotatoEngine::Get();
    engine.LoadSubclasses();
    GameInstance* instance = GameInstance::Get();
    
    // ENGINE SETTINGS
    instance->MS_REPEAT_THRESHOLD = 0;
    instance->FRAMES_PER_SECOND = 60.f;

    /// LEVEL SETUP
    [[maybe_unused]] World* world = instance->GetWorld();
    PersistentLevel level("save1.json"); // default save
    level.LoadStaticActors();

    /// WORLD SETTINGS
    world->Settings.Size = Vector2(80,24); // restrict level size
    world->Settings.doGravity = false;

    /// PLAYER SETUP
    PlayerController* playerController = instance->GetPlayerController();
    Player* player = playerController->GetPlayer();
    player->SetPosition(Vector2(40,12)); // player spawns in the middle of world
    player->SetSize(Vector2(1,1));
    player->Texture = 'X';

    /// UI SETUP
    [[maybe_unused]] IHUDController* HUDController = engine.GetHUDController();
    ScoreWidget* scoreWidget = HUDController->AddWidget<ScoreWidget>("ScoreWidget");

    /// PLAY
    engine.BeginPlay();

    engine.Resolve();

    return 0;
}