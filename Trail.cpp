#include <SFML/Graphics.hpp>
#include <vector>

sf::Color operator*(float value, sf::Color color)
{
    return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

template<class T>
T lerp(const T& start, const T& end, float alpha)
{
    if (alpha < 0) return T(start);
    if (alpha > 1) return T(end);

    return (1 - alpha) * start + alpha * end;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Multiple Balls");

   
    const int numBalls = 5;


    std::vector<sf::CircleShape> balls(numBalls, sf::CircleShape(20));
    for (auto& ball : balls)
        ball.setOrigin(20, 20);

   
    std::vector<sf::Vector2f> positions(numBalls, sf::Vector2f(20, 20));
    std::vector<sf::Vector2f> startPositions(numBalls, sf::Vector2f(20, 20));
    std::vector<sf::Vector2f> targetPositions(numBalls, sf::Vector2f(20, 20));

   
    std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta };
    for (int i = 0; i < numBalls; ++i)
        balls[i].setFillColor(colors[i]);

    sf::Clock clock;
    float time;

    
    std::vector<float> durations = { 0.5, 0.7, 0.9, 1.1, 1.3 };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                
                targetPositions[0] = (sf::Vector2f)sf::Mouse::getPosition(window);
                startPositions[0] = positions[0];
                clock.restart();
            }
        }

        time = clock.getElapsedTime().asSeconds();

        
        for (int i = 0; i < numBalls; ++i)
        {
            float alpha = time / durations[i]; // Use a different duration for each ball

           
            if (i == 0)
            {
                positions[i] = lerp(startPositions[i], targetPositions[i], alpha);
            }
            
            else
            {
                targetPositions[i] = positions[i - 1];
                startPositions[i] = positions[i];
                positions[i] = lerp(startPositions[i], targetPositions[i], alpha);
            }

           
            balls[i].setPosition(positions[i]);
        }

        window.clear();
       
        for (const auto& ball : balls)
            window.draw(ball);

        window.display();
    }

    return 0;
}
