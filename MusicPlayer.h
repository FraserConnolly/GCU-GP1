#pragma once
#include "Window.h"
#include <future>

using namespace std;

// Define the frequencies of notes in an octave, as well as
// silence (rest).
enum Tone : DWORD
{
    REST = 0,
    GbelowC = 196,
    A = 220,
    Asharp = 233,
    B = 247,
    C = 262,
    Csharp = 277,
    D = 294,
    Dsharp = 311,
    E = 330,
    F = 349,
    Fsharp = 370,
    G = 392,
    Gsharp = 415,
};

// Define the duration of a note in units of milliseconds.
enum Duration : DWORD
{
    WHOLE = 1600,
    HALF = WHOLE / 2,
    QUARTER = HALF / 2,
    EIGHTH = QUARTER / 2,
    SIXTEENTH = EIGHTH / 2,
};

// Define a note as a frequency (tone) and the amount of
// time (duration) the note plays.
struct Note
{
    Tone     toneVal;
    Duration durVal;

    // Define a constructor to create a specific note.
    Note ( Tone frequency, Duration time )
    {
        toneVal = frequency;
        durVal = time;
    }

};

class MusicPlayer
{
public:

    // Play the notes in a song.
    void Play ( Note * tune, int length );
    void PlayNote ( const Tone tone );

    void tick ( const float deltaTime );

private:

    inline void asyncBeep ( int tone, int duration );
    void playBeepAsync ( int frequency, int duration );

    std::future<void> m_asyncResult;
    bool m_notePlaying = false;
    float m_timer;
    Note * m_tune = NULL;
    int m_tuneLength;
    int m_noteIndex;

};
