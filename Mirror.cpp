#include <SFML/Graphics.hpp>
#include <cmath>


sf::Vector2f reflectPoint(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd, const sf::Vector2f& point) {
    sf::Vector2f lineVec = lineEnd - lineStart;
    sf::Vector2f toPoint = point - lineStart;

    float projLength = (toPoint.x * lineVec.x + toPoint.y * lineVec.y) / (lineVec.x * lineVec.x + lineVec.y * lineVec.y);

    sf::Vector2f closestPoint = lineStart + projLength * lineVec;

    sf::Vector2f reflection = closestPoint + (closestPoint - point);

    return reflection;
}


bool isPointClicked(const sf::Vector2f& point, const sf::Vector2i& mousePos, float radius = 10.f) {
    return (std::hypot(point.x - mousePos.x, point.y - mousePos.y) <= radius);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mirror ");
    window.setFramerateLimit(60);

   
    sf::CircleShape pointA(7), pointB(7);
    pointA.setFillColor(sf::Color::Red);
    pointB.setFillColor(sf::Color::Red);
    pointA.setPosition(400, 100);
    pointB.setPosition(400, 500);

    sf::CircleShape triangleP1(5), triangleP2(5), triangleP3(5);
    triangleP1.setFillColor(sf::Color::Cyan);
    triangleP2.setFillColor(sf::Color::Cyan);
    triangleP3.setFillColor(sf::Color::Cyan);
    triangleP1.setPosition(525, 300);
    triangleP2.setPosition(600, 350);
    triangleP3.setPosition(500, 350);

    bool draggingA = false, draggingB = false;
    bool draggingP1 = false, draggingP2 = false, draggingP3 = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                
                if (isPointClicked(pointA.getPosition(), mousePos)) draggingA = true;
                else if (isPointClicked(pointB.getPosition(), mousePos)) draggingB = true;
                else if (isPointClicked(triangleP1.getPosition(), mousePos)) draggingP1 = true;
                else if (isPointClicked(triangleP2.getPosition(), mousePos)) draggingP2 = true;
                else if (isPointClicked(triangleP3.getPosition(), mousePos)) draggingP3 = true;
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                draggingA = draggingB = draggingP1 = draggingP2 = draggingP3 = false;
            }
        }
      
        if (draggingA) pointA.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        if (draggingB) pointB.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        if (draggingP1) triangleP1.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        if (draggingP2) triangleP2.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        if (draggingP3) triangleP3.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

       
        sf::Vector2f A = pointA.getPosition(), B = pointB.getPosition();
        sf::Vector2f P1 = triangleP1.getPosition(), P2 = triangleP2.getPosition(), P3 = triangleP3.getPosition();
        sf::Vector2f R1 = reflectPoint(A, B, P1);
        sf::Vector2f R2 = reflectPoint(A, B, P2);
        sf::Vector2f R3 = reflectPoint(A, B, P3);

       
        window.clear();


        sf::Vertex line[] = {
            sf::Vertex(A, sf::Color::White),
            sf::Vertex(B, sf::Color::White)
        };
        window.draw(line, 2, sf::LinesStrip);

        window.draw(pointA);
        window.draw(pointB);

        
        sf::Vertex triangle[] = {
            sf::Vertex(P1, sf::Color::Cyan),
            sf::Vertex(P2, sf::Color::Cyan),
            sf::Vertex(P3, sf::Color::Cyan),
            sf::Vertex(P1, sf::Color::Cyan) 
        };
        window.draw(triangle, 4, sf::LinesStrip);

        
        sf::Vertex reflectedTriangle[] = {
            sf::Vertex(R1, sf::Color::Yellow),
            sf::Vertex(R2, sf::Color::Yellow),
            sf::Vertex(R3, sf::Color::Yellow)
        };
        window.draw(reflectedTriangle, 3, sf::TrianglesStrip);

        
        window.draw(triangleP1);
        window.draw(triangleP2);
        window.draw(triangleP3);

        window.display();
    }

    return 0;
}
