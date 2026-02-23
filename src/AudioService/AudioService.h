#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdint>

class AudioService
{
public:
	AudioService();
	void loadSound(const std::string& soundFile);
	void playSound();

	bool checkSoundFinished(const int fftSize);

	std::size_t currentSample;
	const std::int16_t* samples;
	std::size_t sampleCount;

	sf::SoundBuffer buffer;
	sf::Sound sound;
private:
};
