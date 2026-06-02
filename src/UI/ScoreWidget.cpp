
#include <UI/Widgets/TextElement.hpp>
#include <Core/Control/GameInstance.hpp>

#include "LazerAssault.hpp"
#include "ScoreWidget.hpp"

ScoreWidget::ScoreWidget(std::string UID) : Widget(UID) {

    TextElement* scoreDisplay = AddElement<TextElement>("scoreDisplay");
    scoreDisplay->SetScreenPosition(Vector2(0,0));
    scoreDisplay->SetScreenSize(Vector2(10,1));
    scoreDisplay->field = "Score: .";
    scoreDisplay->SetVisibility(true);

    TextElement* healthDisplay = AddElement<TextElement>("healthDisplay");
    healthDisplay->SetScreenPosition(Vector2(0,1));
    healthDisplay->SetScreenSize(Vector2(10,1));
    healthDisplay->field = "Health: .";
    healthDisplay->SetVisibility(true);

    SetTicking(true);
}

void ScoreWidget::Tick([[maybe_unused]] float dt) {
    LazerAssault* gm = dynamic_cast<LazerAssault*>(GameInstance::Get()->GetGamemode());
    Player* player = GameInstance::Get()->GetPlayerController()->GetPlayer();

    TextElement* scoreDisplay = dynamic_cast<TextElement*>(GetElement("scoreDisplay"));
    TextElement* healthDisplay = dynamic_cast<TextElement*>(GetElement("healthDisplay"));

    int Score = gm->GetScore();
    
    scoreDisplay->field = "Score: " + std::to_string(Score);
    healthDisplay->field = "Health: " + std::to_string(static_cast<int>(player->GetHealth()));

}