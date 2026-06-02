
#include <Core/PotatoEngine.hpp>
#include <Core/Control/GameInstance.hpp>
#include <Core/Input/InputController.hpp>

#include <Debug/Debug.hpp>

#include "CharacterController.hpp"

SET_DEFAULT_SUBCLASS(PlayerController, CharacterController)

CharacterController::CharacterController() {
    moveSpeed = 1.f;
    CameraFollow = false;
}

void CharacterController::SetupInputBindings() {
    // skip base method call for custom movement

    IInputController* controller = PotatoEngine::Get().GetInputController();

    controller->RegisterInputBinding({
        InputBinding(Keycode::W, InputType::Triggered, "MoveUp", this, &CharacterController::moveUp),
        InputBinding(Keycode::S, InputType::Triggered, "MoveDown", this, &CharacterController::moveDown),
        InputBinding(Keycode::A, InputType::Triggered, "MoveLeft", this, &CharacterController::moveLeft),
        InputBinding(Keycode::D, InputType::Triggered, "MoveRight", this, &CharacterController::moveRight),
    });

}

void CharacterController::moveUp() { GetPlayer()->AddLocalOffset(Vector2::Up() * moveSpeed); }
void CharacterController::moveDown() { GetPlayer()->AddLocalOffset(-Vector2::Up() * moveSpeed); }
void CharacterController::moveLeft() { GetPlayer()->AddLocalOffset(-Vector2::Right() * moveSpeed); }
void CharacterController::moveRight() { GetPlayer()->AddLocalOffset(Vector2::Right() * moveSpeed); }
