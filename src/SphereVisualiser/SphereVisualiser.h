#include <SFML/Graphics.hpp>

#ifndef M_PI
#   define M_PI 3.1415926535897932384626433832
#endif

class SphereVisualiser {
public:
	SphereVisualiser(int barCount);
	void drawSphere(std::vector<float>& magnitudes, sf::RenderWindow& window);

private:
	const float BASE_RADIUS = 100.f;
	sf::VertexArray sphere;
	int barCount;
};