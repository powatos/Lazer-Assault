#pragma once

#include <UI/Widgets/Widget.hpp>

class ScoreWidget : public Widget
{
public:
    ScoreWidget(std::string UID);
    ~ScoreWidget() = default;

protected:
    virtual void Tick([[maybe_unused]] float dt) override;
    
};