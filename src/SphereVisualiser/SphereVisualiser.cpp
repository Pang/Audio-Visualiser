#include "SphereVisualiser.h"

SphereVisualiser::SphereVisualiser(int newBarCount) {
	sphere = sf::VertexArray(sf::PrimitiveType::LineStrip, newBarCount);
	barCount = newBarCount;
}

void SphereVisualiser::drawSphere(std::vector<float>& magnitudes, sf::RenderWindow& window)
{
    sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);

    int half = barCount / 2;
    std::vector<float> peaks(barCount, 0.f);
    float decay = 0.95f;

    for (int i = 0; i < barCount; i++)
    {
        int wrappedIndex = i % half;
        float m = magnitudes[wrappedIndex];

        if (m > peaks[wrappedIndex]) peaks[wrappedIndex] = m;
        else peaks[wrappedIndex] *= decay; // fall slowly

        float amplitude = peaks[wrappedIndex] * 100.f;
        amplitude = (amplitude * (wrappedIndex + 1)) / barCount; // dampen lower frequency visual range

        float angle = (float)i / barCount * 2.f * M_PI;
        float radius = BASE_RADIUS + amplitude;

        float x = center.x + cos(angle) * radius;
        float y = center.y + sin(angle) * radius;
        sphere[i].position = { x, y };

        sphere[i].color = sf::Color(
            100 + i % 155,
            255 - i % 200,
            255
        );
    }

	window.draw(sphere);
}
