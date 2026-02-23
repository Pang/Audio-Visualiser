#include "main.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Audio Sphere Visualizer");

	AudioService audioService;
	audioService.loadSound("robotvoice.mp3");

    FftwService fftService(FFT_SIZE);
    SphereVisualiser sphere(BAR_COUNT);

    audioService.playSound();
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {   
            if (event->is<sf::Event::Closed>()) window.close();
        }

		if (audioService.checkSoundFinished(FFT_SIZE)) continue;

		fftService.fillFftwBuffer(audioService.samples, audioService.currentSample);
		sphere.SetMagnitudes(fftService.out);

        window.clear(sf::Color::Black);
		sphere.drawSphere(window);
        window.display();
    }

    fftw_destroy_plan(fftService.plan);
}