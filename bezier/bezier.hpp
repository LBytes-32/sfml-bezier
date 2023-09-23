#pragma once
#include <cmath>

// Backend for calculating Bezier equations. Does not directly display anything.
class Bezier {
    public:
        struct ControlPoint {
            float X, Y;
        };
        
    private:
        // Abstracted equation for calculating the curve per dimension.
        // Pass values of the same dimension. (Both `X1` and `X2`, or, both `Y1` and `Y2`)
        // `time`: The position changes with respect to time.
        float BaseEquation (const float& dim1, const float& dim2, const float& time);
        
    public:
        const int CURVE_PRECISION = 10;
        ControlPoint Point1;
        ControlPoint Point2;
        
        Bezier ();
        
        // Calculate the curve's X dimension at any given `time`.
        float CalcDimensionX (const float& time);
        
        // Calculate the curve's Y dimension at any given `time`.
        float CalcDimensionY (const float& time);
        
        // Approximate the height at the `target_time`.
        float ApproxCurveHeight (const float& target_time);
};

