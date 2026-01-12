#include "audio/Jukebox.hpp"

void Jukebox::setVolume(float newVolume)
{
    assert(0.f <= newVolume && newVolume <= 100.f);
    volume = newVolume;
    getCurrentTrack().setVolume(volume);
}

sf::Music& Jukebox::getCurrentTrack()
{
    assert(!currentTrackName.empty());
    return resmgr.getMutable<sf::Music>(currentTrackName);
}

void Jukebox::play(const std::string& trackName, bool loop)
{
    if (currentTrackName == trackName) return;

    currentTrackName = trackName;
    auto& track = getCurrentTrack();
    track.setVolume(volume);
    track.setLooping(loop);
    track.play();
}

void Jukebox::stop()
{
    getCurrentTrack().stop();
}

void Jukebox::resume()
{
    if (currentTrackName.empty()) return;
    getCurrentTrack().play();
}
