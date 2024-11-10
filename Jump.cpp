#include <SFML/Graphics.hpp>
#include <cmath>

const float jumpHeight = 500.0f;    
const float jumpDuration = 1.0f;    


float a, b, c;

bool isJumping = false;
float timeElapsed = 0.0f;


void calculateQuadraticCoefficients() {
    c = 0.0f;  
    b = (4 * jumpHeight) / jumpDuration;     
    a = -(2 * jumpHeight) / (jumpDuration * jumpDuration / 4);  
}

int main() {

    calculateQuadraticCoefficients();


    sf::RenderWindow window(sf::VideoMode(800, 600), "Jump");

    
    sf::CircleShape circle(20.f);
    circle.setFillColor(sf::Color::Blue);


    const float groundLevel = 500.f;
    circle.setPosition(400.f, groundLevel);


    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isJumping) {
                isJumping = true;
                timeElapsed = 0.0f;
            }
        }


        float deltaTime = clock.restart().asSeconds();


        if (isJumping) {
            timeElapsed += deltaTime;

            float y = a * timeElapsed * timeElapsed + b * timeElapsed + c;

            if (y <= 0) {
                isJumping = false;
                circle.setPosition(400.f, groundLevel);  
            }
            else {
                circle.setPosition(400.f, groundLevel - y);  
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
