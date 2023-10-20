#include "MusicPlayer.h"

void MusicPlayer::PlayNote(const Tone tone)
{
    if (tone == Tone::REST)
    {
        return;
    }

    Beep(tone, 250);
}

void MusicPlayer::tick(const float deltaTime)
{
    if (tune == NULL)
    {
        return;
    }

    if (noteIndex >= tuneLength)
    {
        if (tune != NULL)
        {
            delete[] tune;
        }

        tune = NULL;
        return;
    }

    timer -= deltaTime;

    if (timer <= 0 && !notePlaying)
    {

        Note n = tune[noteIndex++];

        timer = n.durVal;

        if (n.toneVal != Tone::REST)
        {
            //Beep(n.toneVal, n.durVal);
            asyncBeep(n.toneVal, n.durVal);
        }
    }
}

// Play the notes in a song.

void MusicPlayer::Play(Note* tune, int length)
{
    timer = 0;
    this->tune = tune;
    this->tuneLength = length;
    this->noteIndex = 0;
}

inline void MusicPlayer::asyncBeep(int tone, int duration)
{
    if (this->notePlaying)
    {
        cout << "Can not play note at the moment" << endl;
        return;
    }

    asyncResult =
        std::async(std::launch::async, &MusicPlayer::playBeepAsync, this, tone, duration);
}

inline void MusicPlayer::playBeepAsync(int frequency, int duration) {
    this->notePlaying = true;
    Beep(frequency, duration);
    this->notePlaying = false;
}
