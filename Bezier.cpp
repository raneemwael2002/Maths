#include <SFML/Graphics.hpp>
#include <cmath>

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

void updateCurve(sf::VertexArray& curve, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	int pointsCount = curve.getVertexCount();
	float t = 0;
	float delta = 1.f / (pointsCount - 1);

	for (size_t i = 0; i < pointsCount; i++)
	{
		sf::Vector2f p01 = lerp(p0, p1, t);
		sf::Vector2f p12 = lerp(p1, p2, t);
		sf::Vector2f p23 = lerp(p2, p3, t);

		sf::Vector2f p012 = lerp(p01, p12, t);
		sf::Vector2f p123 = lerp(p12, p23, t);

		curve[i].position = lerp(p012, p123, t);
		curve[i].color = lerp(sf::Color::Cyan, sf::Color::Magenta, t);
		t += delta;
	}
}

class DraggablePoint {
	sf::CircleShape shape;
	bool isDragging = false;

public:
	DraggablePoint(const sf::Vector2f& position)
	{
		shape = sf::CircleShape(10);
		shape.setOrigin(10, 10);
		shape.setPosition(position);
		shape.setFillColor(sf::Color::White);
	}

	void beginDrag(const sf::Vector2i& mousePos)
	{
		isDragging = shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
	}

	void drag(const sf::Vector2i& mousePos)
	{
		if (!isDragging) return;
		shape.setPosition(static_cast<sf::Vector2f>(mousePos));
	}

	void endDrag()
	{
		isDragging = false;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	sf::Vector2f getPosition() const
	{
		return shape.getPosition();
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bezier Curve");

	DraggablePoint p0(sf::Vector2f(100, 500));
	DraggablePoint p1(sf::Vector2f(300, 100));
	DraggablePoint p2(sf::Vector2f(500, 100));
	DraggablePoint p3(sf::Vector2f(700, 500));

	sf::VertexArray line(sf::LineStrip, 4);  
	sf::VertexArray curve(sf::LineStrip, 100); 

	sf::CircleShape ball(12);  
	ball.setFillColor(sf::Color::White);
	bool ballMoving = false;
	float t = 0;  
	const float ballSpeed = 0.001f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			
			if (event.type == sf::Event::MouseButtonPressed)
			{
				p0.beginDrag(sf::Mouse::getPosition(window));
				p1.beginDrag(sf::Mouse::getPosition(window));
				p2.beginDrag(sf::Mouse::getPosition(window));
				p3.beginDrag(sf::Mouse::getPosition(window));
			}

			
			if (event.type == sf::Event::MouseButtonReleased)
			{
				p0.endDrag();
				p1.endDrag();
				p2.endDrag();
				p3.endDrag();
			}


			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				ballMoving = true;
				t = 0; 
			}
		}

		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			p0.drag(sf::Mouse::getPosition(window));
			p1.drag(sf::Mouse::getPosition(window));
			p2.drag(sf::Mouse::getPosition(window));
			p3.drag(sf::Mouse::getPosition(window));
		}

		line[0].position = p0.getPosition();
		line[1].position = p1.getPosition();
		line[2].position = p2.getPosition();
		line[3].position = p3.getPosition();


		updateCurve(curve, p0.getPosition(), p1.getPosition(), p2.getPosition(), p3.getPosition());


		if (ballMoving && t <= 1)
		{
			sf::Vector2f p01 = lerp(p0.getPosition(), p1.getPosition(), t);
			sf::Vector2f p12 = lerp(p1.getPosition(), p2.getPosition(), t);
			sf::Vector2f p23 = lerp(p2.getPosition(), p3.getPosition(), t);

			sf::Vector2f p012 = lerp(p01, p12, t);
			sf::Vector2f p123 = lerp(p12, p23, t);

			sf::Vector2f positionOnCurve = lerp(p012, p123, t);
			ball.setPosition(positionOnCurve);

			t += ballSpeed;


			if (t >= 1) ballMoving = false;
		}


		window.clear();


		window.draw(curve);
		window.draw(line);
		p0.draw(window);
		p1.draw(window);
		p2.draw(window);
		p3.draw(window);
		if (ballMoving) window.draw(ball);

		window.display();
	}

	return 0;
}
