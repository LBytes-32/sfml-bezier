#include "editor.hpp"

BezierEditor::BezierEditor(Bezier& bezier, sf::Vector2f position, sf::Vector2f size) : TargetBezier(bezier) {
    
    Properties.SelectedPoint = 0;
    Properties.Position      = position;
    Properties.Size          = size;
    Properties.Origin        = {position.x, position.y + 2*size.y / 3};
    Properties.Scale         = {size.x, size.y / 2};
    
    Visual.Point1 = sf::CircleShape(5);
    Visual.Point2 = sf::CircleShape(5);
    Visual.Container = sf::RectangleShape();
    
    Visual.Buffer = sf::VertexBuffer(sf::PrimitiveType::TriangleStrip, sf::VertexBuffer::Usage::Stream);
    Visual.Buffer.create(VERTEX_COUNT);
    
    Visual.Point1.setPosition(position);
    Visual.Point2.setPosition(position.x + size.x, position.y + size.y);
    Visual.Point1.setOrigin(5, 5);
    Visual.Point2.setOrigin(5, 5);
    
    Visual.Container.setFillColor(sf::Color(16, 16, 16));
    Visual.Container.setPosition(position);
    Visual.Container.setSize(size);
}

void BezierEditor::Update(sf::Vector2f mouse) {
    UpdatePoints(mouse);
    UpdateBezier();
    UpdateGraph();
}

void BezierEditor::RestrainPoint(sf::CircleShape& point) {
    auto pos = point.getPosition();
    
    if (pos.x < Properties.Position.x)
        pos.x = Properties.Position.x;
    
    if (pos.x > Properties.Position.x + Properties.Size.x)
        pos.x = Properties.Position.x + Properties.Size.x;
        
    if (pos.y < Properties.Position.y)
        pos.y = Properties.Position.y;
    
    if (pos.y > Properties.Position.y + Properties.Size.y)
        pos.y = Properties.Position.y + Properties.Size.y;
    
    point.setPosition(pos);
}

void BezierEditor::UpdatePoints(sf::Vector2f mouse) {
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    bool isMouseOnPoint1 = Visual.Point1.getGlobalBounds().contains(mouse);
    bool isMouseOnPoint2 = Visual.Point2.getGlobalBounds().contains(mouse);
    
    if (!isMousePressed) {
        Properties.SelectedPoint = 0;
    }
    
    bool canStartDraggingPoint1 = isMousePressed && isMouseOnPoint1 && Properties.SelectedPoint == 0;
    bool canStartDraggingPoint2 = isMousePressed && isMouseOnPoint2 && Properties.SelectedPoint == 0;
    
    if (canStartDraggingPoint1 || Properties.SelectedPoint == 1) {
        Visual.Point1.setPosition(mouse);
        Properties.SelectedPoint = 1;
    }
    
    if (canStartDraggingPoint2 || Properties.SelectedPoint == 2) {
        Visual.Point2.setPosition(mouse);
        Properties.SelectedPoint = 2;
    }
    
    RestrainPoint(Visual.Point1);
    RestrainPoint(Visual.Point2);
}

void BezierEditor::UpdateBezier() {
    auto point1 = Visual.Point1.getPosition();
    auto point2 = Visual.Point2.getPosition();
    auto origin = Properties.Origin;
    auto scale  = Properties.Scale;
    
    TargetBezier.Control1.x = (point1.x - origin.x) / scale.x;
    TargetBezier.Control2.x = (point2.x - origin.x) / scale.x;
    TargetBezier.Control1.y = (point1.y - origin.y) / -scale.y;
    TargetBezier.Control2.y = (point2.y - origin.y) / -scale.y;
}

void BezierEditor::UpdateGraph() {
    float x = 0;
    float t = 0;
    
    float dx = Visual.Container.getSize().x / (float)(PRECISION);
    float dt = 1 / (float)(PRECISION);
    
    float eval, slope, evalLast = 0;
    
    for (int i = 0; i < VERTEX_COUNT; i += 2) {
        eval     = -TargetBezier.ApproxCurveHeight(t) * Properties.Scale.y;
        slope    = eval - evalLast;
        evalLast = eval;
        
        sf::Color temperature = sf::Color (127-slope*8, 0, 127+slope*8, 255);
        
        Visual.Vertices[i+0].position = sf::Vector2f(x + Properties.Origin.x, eval + fabs(slope) + 2 + Properties.Origin.y);
        Visual.Vertices[i+1].position = sf::Vector2f(x + Properties.Origin.x, eval - fabs(slope) - 2 + Properties.Origin.y);
        
        Visual.Vertices[i+0].color = temperature;
        Visual.Vertices[i+1].color = temperature;
        
        x += dx;
        t += dt;
    }
    
    Visual.Buffer.update(Visual.Vertices);
}

void BezierEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(Visual.Container);
    target.draw(Visual.Buffer);
    target.draw(Visual.Point1);
    target.draw(Visual.Point2);
}