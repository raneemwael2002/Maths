#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14159f;

void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle) {
    int pointsCount = shape.getPointCount();
    float startRad = startAngle * PI / 180;
    float endRad = endAngle * PI / 180;
    float deltaAngle = (endRad - startRad) / (pointsCount - 2);

    shape.setPoint(0, center);  

    float angle = startRad;
    for (int i = 1; i < pointsCount; ++i) {
        sf::Vector2f point;
        point.x = center.x + radius * std::cos(angle);
        point.y = center.y + radius * std::sin(angle);
        shape.setPoint(i, point);
        angle += deltaAngle;
    }
}

bool isArcTouchingCircle(const sf::ConvexShape& arc, const sf::CircleShape& circle) {
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    float radius = circle.getRadius();

    for (size_t i = 1; i < arc.getPointCount(); ++i) {
        sf::Vector2f arcPoint = arc.getPoint(i);
        float dist = std::sqrt(std::pow(arcPoint.x - circleCenter.x, 2) + std::pow(arcPoint.y - circleCenter.y, 2));
        if (dist <= radius) {
            return true;  
        }
    }
    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arc Touch Detection");

   
    sf::CircleShape circleA(20);
    circleA.setFillColor(sf::Color::Cyan);
    circleA.setPosition(240, 300);

    
    sf::CircleShape circleB(10);
    circleB.setFillColor(sf::Color::Red);
    circleB.setPosition(400, 300);  

    
    sf::ConvexShape arc(30);
    arc.setFillColor(sf::Color::Green);

  
    float fovRadius = 150.f;  
    float fovAngle = 90.f;    
    float rotationAngle = 0.f;

    
    float speed = 1.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            circleB.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            circleB.move(0, speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            circleB.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            circleB.move(speed, 0);
        }

        
        sf::Vector2f bPos = circleB.getPosition() + sf::Vector2f(circleB.getRadius(), circleB.getRadius()); 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        rotationAngle = std::atan2(mousePos.y - bPos.y, mousePos.x - bPos.x) * 180 / PI;

        
        updateArc(arc, bPos, fovRadius, rotationAngle - fovAngle / 2, rotationAngle + fovAngle / 2);

        if (isArcTouchingCircle(arc, circleA)) {
            arc.setFillColor(sf::Color::Yellow);  
        }
        else {
            arc.setFillColor(sf::Color::Green);  
        }

        
        window.clear();
        window.draw(circleA);
        window.draw(arc);
        window.draw(circleB);

        window.display();
    }

    return 0;
}

