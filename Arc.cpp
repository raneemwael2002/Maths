#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 22/7
void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle) {

    int pointsCount = shape.getPointCount();
    float startRad = startAngle * PI / 180;   
    float endRad = endAngle * PI / 180;       
    float deltaAngle = (endRad - startRad) / (pointsCount - 2); 

    
    shape.setPoint(0, center);

    
    float angle = startRad;
    for (int i = 1; i < pointsCount; ++i) {
        sf::Vector2f point;
        point.x = center.x + radius * cos(angle);
        point.y = center.y + radius * sin(angle);
        shape.setPoint(i, point);
        angle += deltaAngle;  
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Arc");

    
    sf::ConvexShape arc(30);  
    arc.setFillColor(sf::Color::Green);


    updateArc(arc, sf::Vector2f(200, 200), 100, 250, 180); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(arc);
        window.display();
    }

    return 0;
}
