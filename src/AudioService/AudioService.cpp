#include "AudioService.h"

AudioService::AudioService()
	: currentSample(0)
	, samples(nullptr)
	, sampleCount(0)
	, buffer()
	, sound(buffer) // construct sound with buffer to avoid requiring a default ctor
{
}

void AudioService::loadSound(const std::string& soundFile)
{
	if (!buffer.loadFromFile(soundFile))
	{
		std::cout << "Failed to load audio\n";
	}

	sound.setBuffer(buffer);

	samples = buffer.getSamples();
	sampleCount = buffer.getSampleCount();
}

void AudioService::playSound()
{
	sound.play();
}

bool AudioService::checkSoundFinished(const int fftSize)
{
	float seconds = sound.getPlayingOffset().asSeconds();
	currentSample = static_cast<std::size_t>(seconds * buffer.getSampleRate() * buffer.getChannelCount());

	if (currentSample + static_cast<std::size_t>(fftSize) >= sampleCount) return true;

	return false;
}