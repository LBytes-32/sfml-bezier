#include "visual.hpp"

BezierVisual::BezierVisual(sf::Vector2f start, sf::Vector2f end, float speed) {
    BezierX.Control1 = sf::Vector2f {0, 0};
    BezierX.Control2 = sf::Vector2f {1, 1};
    
    BezierY.Control1 = sf::Vector2f {0, 0};
    BezierY.Control1 = sf::Vector2f {1, 1};
    
    Animation.Start = start;
    Animation.End   = end;
    Animation.Speed = speed;
    
    Animation.Time = 0;
    Animation.IsMovingForward = false;
    
    Visual.Start = sf::CircleShape(3);
    Visual.End   = sf::CircleShape(3);
    Visual.Ball  = sf::CircleShape(10);
    
    for (int i = 0; i < STEPS_IN_PATH; i++) {
        Visual.Steps[i].setRadius(1);
        Visual.Steps[i].setFillColor(sf::Color(120, 120, 120, 255));
    }
    
    Visual.Start .setOrigin (3, 3);
    Visual.End   .setOrigin (3, 3);
    Visual.Ball  .setOrigin (10, 10);
}

sf::Vector2f BezierVisual::GetPosition(float time) {
    return Bezier::GetScaled2DPoint(BezierX, BezierY, Animation.Start, Animation.End, time);
}

void BezierVisual::UpdateTime() {
    Animation.Time += Animation.Speed * (Animation.IsMovingForward ? 1 : -1);
    
    if (Animation.Time > 1)
        Animation.Time = 1;
    
    if (Animation.Time < 0)
        Animation.Time = 0;
}

void BezierVisual::UpdatePath() {
    float t = 0;
    float dt = 1 / (float)(STEPS_IN_PATH);
    sf::Vector2f pos;
    
    for (int i = 0; i < STEPS_IN_PATH; i++) {
        pos = GetPosition(t);
        Visual.Steps[i].setPosition(pos);
        t += dt;
    }
}

void BezierVisual::Update() {
    UpdateTime();
    UpdatePath();
    
    sf::Vector2f ballPosition = GetPosition(Animation.Time);
    
    Visual.Start .setPosition (Animation.Start);
    Visual.End   .setPosition (Animation.End);
    Visual.Ball  .setPosition (ballPosition);
}

void BezierVisual::Redirect() {
    Animation.IsMovingForward = !Animation.IsMovingForward;
}

void BezierVisual::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    for (int i = 0; i < STEPS_IN_PATH; i++)
        target.draw(Visual.Steps[i]);
        
    target.draw(Visual.Start);
    target.draw(Visual.End);
    target.draw(Visual.Ball);
}

