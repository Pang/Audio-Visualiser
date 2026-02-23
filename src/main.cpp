#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fftw3.h>

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdint>

#include "SphereVisualiser/SphereVisualiser.h"
#include "FftwService/FftwService.h"

const int FFT_SIZE = 1024;
const int BAR_COUNT = 360;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Audio Sphere Visualizer");
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("robotvoice.mp3"))
    {
        std::cout << "Failed to load audio\n";
        return -1;
    }

    sf::Sound sound(buffer);
    sound.play();

    const std::int16_t* samples = buffer.getSamples();
    std::size_t sampleCount = buffer.getSampleCount();

    FftwService fftService(FFT_SIZE);
    std::vector<float> magnitudes(BAR_COUNT);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {   
            if (event->is<sf::Event::Closed>()) window.close();
        }

        float seconds = sound.getPlayingOffset().asSeconds();
        std::size_t currentSample = seconds * buffer.getSampleRate() * buffer.getChannelCount();
        if (currentSample + FFT_SIZE >= sampleCount) continue;

		fftService.fillFftwBuffer(samples, currentSample);

		// Create a vector of magnitudes from the FFT output
        for (int i = 0; i < BAR_COUNT; i++)
        {
            double real = fftService.out[i][0];
            double imag = fftService.out[i][1];

            magnitudes[i] = std::sqrt(real * real + imag * imag);
        }

        window.clear(sf::Color::Black);
        SphereVisualiser sphere (BAR_COUNT);
		sphere.drawSphere(magnitudes, window);
        window.display();
    }

    fftw_destroy_plan(fftService.plan);
}