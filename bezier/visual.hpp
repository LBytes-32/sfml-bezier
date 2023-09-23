#pragma once
#include <SFML/Graphics.hpp>
#include "bezier.hpp"

class BezierVisual : public sf::Drawable {
    private:
        static const int STEPS_IN_PATH = 40;
        
        Bezier BezierX;
        Bezier BezierY;
        
        struct {
            sf::Vector2f  Start;
            sf::Vector2f  End;
            bool          IsMovingForward;
            float         Time;
            float         Speed;
        } Animation;
        
        struct {
            sf::CircleShape Start, End, Ball, Steps[STEPS_IN_PATH];
        } Visual;
        
        sf::Vector2f GetPosition(float time);
        void UpdateTime();
        void UpdatePath();
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
    public:
        BezierVisual(sf::Vector2f start, sf::Vector2f end, float speed);
        
        void Update();
        void Redirect();
};

