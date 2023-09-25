#pragma once
#include <SFML/Graphics.hpp>
#include "bezier.hpp"

/// Animate a ball along a Bezier path.
/// The path is determined by 2 dimensions of beziers. (Bezier X and Bezier Y)
class BezierVisual : public sf::Drawable {
    private:
        /// The number of dots in the visualized path.
        static const int STEPS_IN_PATH = 40;
        
        Bezier& BezierX;
        Bezier& BezierY;
        
        /// Variables for calculating animation
        struct {
            sf::Vector2f  Start;
            sf::Vector2f  End;
            bool          IsMovingForward;
            float         Time;
            float         Speed;
        } Animation;
        
        /// Visual components of the animation
        struct {
            sf::CircleShape Start, End, Ball, Steps[STEPS_IN_PATH];
        } Visual;
        
    private:
        /// Get the position with respect to `BezierX` and `BezierY`.
        sf::Vector2f GetPosition(float time);
        
        /// Accumulate time by speed. Stay within the domain `[0, 1]`.
        void UpdateTime();
        
        /// Update the visualized path.
        void UpdateVisualizedPath();
        
        /// Render the visuals to the window.
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
    public:
        /// Provide 2 bezier dimensions, start point, end point, and animation speed.
        BezierVisual(Bezier& bezierX, Bezier& bezierY, sf::Vector2f start, sf::Vector2f end, float speed);
        
        /// Update the animation each frame.
        void Update();
        
        /// Reverse the ball's direction at any time.
        void Redirect();
};

