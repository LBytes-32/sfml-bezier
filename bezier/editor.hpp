#pragma once
#include <SFML/Graphics.hpp>
#include "bezier.hpp"

class BezierEditor : public sf::Drawable {
    private:
        const static int PRECISION = 120;
        const static int VERTEX_COUNT = PRECISION * 2 + 2;
        
        Bezier& TargetBezier;
        
        struct {
            sf::Vector2f Position;
            sf::Vector2f Size;
            sf::Vector2f Scale;
            sf::Vector2f Origin;
            int          SelectedPoint;
        } Properties;
        
        struct {
            sf::RectangleShape Container;
            sf::CircleShape    Point1;
            sf::CircleShape    Point2;
            sf::VertexBuffer   Buffer;
            sf::Vertex         Vertices[VERTEX_COUNT];
        } Visual;
        
        sf::Vector2f RatioToPoint (sf::Vector2f ratio);
        sf::Vector2f PointToRatio (sf::Vector2f position);
        
        void RestrainPoint(sf::CircleShape& point);
        void UpdatePoints(sf::Vector2f mouse);
        void UpdateBezier();
        void UpdateGraph();
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
    public:
        BezierEditor(Bezier& bezier, sf::Vector2f position, sf::Vector2f size);
        void Update(sf::Vector2f mouse);
};

