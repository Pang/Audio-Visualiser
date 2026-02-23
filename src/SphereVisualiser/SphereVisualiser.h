#include <SFML/Graphics.hpp>
#include <fftw3.h>

#ifndef M_PI
#   define M_PI 3.1415926535897932384626433832
#endif

class SphereVisualiser {
public:
	SphereVisualiser(int barCount);
	void drawSphere(sf::RenderWindow& window);
	void SetMagnitudes(fftw_complex* out);

private:
	const float BASE_RADIUS = 100.f;

	std::vector<float> magnitudes;
	sf::VertexArray sphere;
	int barCount;
};