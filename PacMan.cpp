#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.14159265358979323846f


void updatePacMan(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float baseAngle, float mouthAngle) {
    int pointsCount = shape.getPointCount();

    
    float startAngle = (baseAngle - mouthAngle / 2) * PI / 180;
    float endAngle = (baseAngle + mouthAngle / 2) * PI / 180;
    float deltaAngle = (endAngle - startAngle) / (pointsCount - 2);

    
    shape.setPoint(0, center);

    
    float angle = startAngle;
    for (int i = 1; i < pointsCount; ++i) {
        sf::Vector2f point;
        point.x = center.x + radius * cos(angle);
        point.y = center.y + radius * sin(angle);
        shape.setPoint(i, point);
        angle += deltaAngle;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");

    
    sf::CircleShape pacmanBody(100.0f);
    pacmanBody.setFillColor(sf::Color::Yellow);
    pacmanBody.setOrigin(100, 100);  
    pacmanBody.setPosition(400, 300);

    
    sf::ConvexShape pacmanMouth(20);  
    pacmanMouth.setFillColor(sf::Color::Black);

    float baseAngle = 0.0f;           
    float mouthAngle = 45.0f;         
    const float mouthAngleRange = 45.0f;  

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float t = clock.getElapsedTime().asSeconds();
        mouthAngle = 20.0f + 15.0f * std::sin(t * 4);  

        
        updatePacMan(pacmanMouth, pacmanBody.getPosition(), pacmanBody.getRadius(), baseAngle, mouthAngle);

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            baseAngle = 270.0f;  
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            baseAngle = 90.0f;   
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            baseAngle = 180.0f; 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            baseAngle = 0.0f;    

        
        window.clear(sf::Color::Black);
        window.draw(pacmanBody);    
        window.draw(pacmanMouth);   
        window.display();
    }

    return 0;
}
