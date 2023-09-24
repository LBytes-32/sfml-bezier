#include "bezier.hpp"

Bezier::Bezier() {
    Control1 = sf::Vector2f { 0, 0 };
    Control2 = sf::Vector2f { 0, 0 };
}

float Bezier::BaseEquation (const float& dim1, const float& dim2, const float& time) {
    // Demo using the Desmos graphing calculator.
    // https://www.desmos.com/calculator/hm49hrbq7r
    float e1 = 3 * dim1 * pow(1-time, 2) * time;
    float e2 = 3 * dim2 * pow(time, 2) * (1-time);
    return e1 + e2 + pow(time, 3);
}

float Bezier::CalcDimensionX (const float& time) {
    return BaseEquation(Control1.x, Control2.x, time);
}

float Bezier::CalcDimensionY (const float& time) {
    return BaseEquation(Control1.y, Control2.y, time);
}

float Bezier::ApproxCurveHeight (const float& time_target) {
    float pivot = 0.5;
    float delta = 0.5;
    
    // Use a binary search algorithm to approximate the height.
    for (int i = 0; i < CURVE_PRECISION; i++) {
        // Change time by smaller and smaller amounts each iteration.
        delta /= 2;
        
        // CalcDimensionX(pivot) will approach the time_target.
        bool overshoot = CalcDimensionX(pivot) > time_target;
        
        // Direct "time" change TOWARDS target_time.
        if (overshoot)
            pivot -= delta;
        else
            pivot += delta;
    }
    
    return CalcDimensionY(pivot);
}

sf::Vector2f Bezier::GetScaled2DPoint(Bezier& bezierX, Bezier& bezierY, sf::Vector2f start, sf::Vector2f end, float time) {
    sf::Vector2f position;
    
    float xRatio = bezierX.ApproxCurveHeight(time);
    float yRatio = bezierY.ApproxCurveHeight(time);
    
    // Calculate the parallel path. (Bezier X Component)
    position.x = (end.x - start.x) * xRatio + start.x;
    position.y = (end.y - start.y) * xRatio + start.y;
    
    // Calculate the perpendicular path. (Bezier Y Component)
    
    
    return position;
}
