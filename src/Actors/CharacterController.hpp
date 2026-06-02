#pragma once

#include <Game/Control/PlayerController.hpp>

class CharacterController : public PlayerController
{
public:
    CharacterController();

    virtual void SetupInputBindings() override;

protected:

private:
    void moveUp();
    void moveDown();
    void moveLeft(); 
    void moveRight();

    float moveSpeed;

};