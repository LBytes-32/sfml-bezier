#pragma once
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

// Backend for calculating Bezier equations. Does not directly display anything.
// Control points are restricted to the domain and range of [0, 1].
// The curve may be used as a ratio, and scaled as needed.
class Bezier {
    private:
        // Abstracted equation for calculating the curve per dimension.
        // Pass values of the same dimension. (Both `X1` and `X2`, or, both `Y1` and `Y2`)
        // `time`: The position changes with respect to time.
        float BaseEquation (const float& dim1, const float& dim2, const float& time);
        
    public:
        const int CURVE_PRECISION = 10;
        
        sf::Vector2f Control1;
        sf::Vector2f Control2;
        
        Bezier ();
        
        // Calculate the curve's X dimension at any given `time`.
        float CalcDimensionX (const float& time);
        
        // Calculate the curve's Y dimension at any given `time`.
        float CalcDimensionY (const float& time);
        
        // Approximate the height at the `target_time`.
        float ApproxCurveHeight (const float& time_target);
        
        // Given 2 bezier curves (representing the `X` and `Y` dimensions) 
        static sf::Vector2f GetScaled2DPoint(Bezier& bezierX, Bezier& bezierY, sf::Vector2f start, sf::Vector2f end, float time);
};
