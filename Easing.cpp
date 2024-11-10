#include <SFML/Graphics.hpp>



class Back {

public:

    static float easeIn(float t, float b, float c, float d) {
        float s = 1.70158f;
        float postFix = t /= d;
        return c * (postFix)*t * ((s + 1) * t - s) + b;
    }

    static float easeOut(float t, float b, float c, float d) {
        float s = 1.70158f;
        return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
    }


    static float easeInOut(float t, float b, float c, float d) {
        float s = 1.70158f;
        if ((t /= d / 2) < 1) return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
        float postFix = t -= 2;
        return c / 2 * ((postFix)*t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
    }

};
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Back Easing");
    sf::CircleShape shape(20);
    shape.setOrigin(20, 20);


    sf::Vector2f position(20, 20);
    sf::Vector2f targetPosition(position);
    sf::Vector2f startPosition(position);


    sf::Color color(sf::Color::Red);
    sf::Color targetColor(sf::Color::Yellow);
    sf::Color startColor(sf::Color::Blue);


    sf::Clock clock;
    float time;

    float d = 1;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                targetPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                startPosition = position;
                clock.restart();
            }
        }

        time = clock.getElapsedTime().asSeconds();

        if (time < d)
        {
            position.x = Back::easeInOut(time, startPosition.x, targetPosition.x - startPosition.x, d);
            position.y = Back::easeInOut(time, startPosition.y, targetPosition.y - startPosition.y, d);

            color.r = Back::easeIn(time, startColor.r, targetColor.r - startColor.r, d);
            color.g = Back::easeIn(time, startColor.g, targetColor.g - startColor.g, d);
            color.b = Back::easeIn(time, startColor.b, targetColor.b - startColor.b, d);
        }

        shape.setFillColor(color);
        shape.setPosition(position);

        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}
