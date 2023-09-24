#include "editor.hpp"

BezierEditor::BezierEditor(Bezier& bezier, sf::Vector2f position, sf::Vector2f size) : TargetBezier(bezier) {
    
    Options.SelectedPoint = 0;
    
    Visual.Point1 = sf::CircleShape(5);
    Visual.Point2 = sf::CircleShape(5);
    Visual.Container = sf::RectangleShape();
    
    Visual.Buffer = sf::VertexBuffer(sf::PrimitiveType::TriangleStrip, sf::VertexBuffer::Usage::Stream);
    Visual.Buffer.create(VERTEX_COUNT);
    
    Visual.Point1.setOrigin(5, 5);
    Visual.Point2.setOrigin(5, 5);
    
}

void BezierEditor::Update(sf::Vector2f mouse) {
    UpdatePoints(mouse);
}

void BezierEditor::RestrainPoint(sf::CircleShape& point) {
    
}

void BezierEditor::UpdatePoints(sf::Vector2f mouse) {
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    bool isMouseOnPoint1 = Visual.Point1.getGlobalBounds().contains(mouse);
    bool isMouseOnPoint2 = Visual.Point2.getGlobalBounds().contains(mouse);
    
    if (!isMousePressed) {
        Options.SelectedPoint = 0;
    }
    
    bool canStartDraggingPoint1 = isMousePressed && isMouseOnPoint1 && Options.SelectedPoint == 0;
    bool canStartDraggingPoint2 = isMousePressed && isMouseOnPoint2 && Options.SelectedPoint == 0;
    
    if (canStartDraggingPoint1 || Options.SelectedPoint == 1) {
        Visual.Point1.setPosition(mouse);
        Options.SelectedPoint = 1;
    }
    
    if (canStartDraggingPoint2 || Options.SelectedPoint == 2) {
        Visual.Point2.setPosition(mouse);
        Options.SelectedPoint = 2;
    }
    
    RestrainPoint(Visual.Point1);
    RestrainPoint(Visual.Point2);
}

void BezierEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(Visual.Container);
    target.draw(Visual.Point1);
    target.draw(Visual.Point2);
}