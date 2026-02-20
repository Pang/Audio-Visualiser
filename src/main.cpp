#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fftw3.h>

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdint>

const int FFT_SIZE = 1024;
const int BAR_COUNT = 360;

#ifndef M_PI
#   define M_PI 3.1415926535897932384626433832
#endif

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Audio Sphere Visualizer");
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("music.mp3"))
    {
        std::cout << "Failed to load audio\n";
        return -1;
    }

    sf::Sound sound(buffer);
    sound.play();

    const std::int16_t* samples = buffer.getSamples();
    std::size_t sampleCount = buffer.getSampleCount();

    // FFT
    double in[FFT_SIZE];
    fftw_complex out[FFT_SIZE];
    fftw_plan plan = fftw_plan_dft_r2c_1d(FFT_SIZE, in, out, FFTW_ESTIMATE);

    std::vector<float> magnitudes(BAR_COUNT);
    float baseRadius = 100.f;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        float seconds = sound.getPlayingOffset().asSeconds();
        std::size_t currentSample = seconds * buffer.getSampleRate() * buffer.getChannelCount();
        if (currentSample + FFT_SIZE >= sampleCount) continue;

        // Fill FFT buffer
        for (int i = 0; i < FFT_SIZE; i++) {
            in[i] = (samples[currentSample + i] / 32768.0) / 2;
        }

        fftw_execute(plan);

        for (int i = 0; i < BAR_COUNT; i++)
        {
            double real = out[i][0];
            double imag = out[i][1];

            magnitudes[i] = std::sqrt(real * real + imag * imag);
        }

        window.clear(sf::Color::Black);

        sf::Vector2f center(
            window.getSize().x / 2.f,
            window.getSize().y / 2.f
        );

        sf::VertexArray sphere(sf::PrimitiveType::Triangles, BAR_COUNT);

        for (int i = 0; i < BAR_COUNT; i++)
        {
            int index = i % BAR_COUNT;
            float angle = (float)index / BAR_COUNT * 2.f * M_PI;

            float amplitude = magnitudes[index] * 100.f;
			amplitude = (amplitude * (i + 1)) / BAR_COUNT; // weight higher frequencies more
            float radius = baseRadius + amplitude;

            float x = center.x + cos(angle) * radius;
            float y = center.y + sin(angle) * radius;

            sphere[i].position = { x, y };

            sphere[i].color = sf::Color(
                100 + index % 155,
                255 - index % 200,
                255
            );
        }

        window.draw(sphere);
        window.display();
    }

    fftw_destroy_plan(plan);
}