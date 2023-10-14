#pragma once
#include "Window.h"
#include <mutex>

using namespace std;

class MusicPlayer
{
public:
   
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
        Note(Tone frequency, Duration time)
        {
            toneVal = frequency;
            durVal = time;
        }
    
    };

    void PlaySong()
    {
        // Declare the first few notes of the song, "Mary Had A Little Lamb".
        Note * Mary = new Note [ 13 ]
        {
        Note(Tone::B, Duration::QUARTER),
        Note(Tone::A, Duration::QUARTER),
        Note(Tone::GbelowC, Duration::QUARTER),
        Note(Tone::A, Duration::QUARTER),
        Note(Tone::B, Duration::QUARTER),
        Note(Tone::B, Duration::QUARTER),
        Note(Tone::B, Duration::HALF),
        Note(Tone::A, Duration::QUARTER),
        Note(Tone::A, Duration::QUARTER),
        Note(Tone::A, Duration::HALF),
        Note(Tone::B, Duration::QUARTER),
        Note(Tone::D, Duration::QUARTER),
        Note(Tone::D, Duration::HALF)
        };

        // Play the song
        Play(Mary, 13);
    }


    void tick(float deltaTime)
    {
        if (tune == NULL)
        {
            return;
        }

        if (noteIndex >= tuneLength)
        {
            tune = NULL;
            return;
        }

        timer -= deltaTime;

        if ( timer <= 0 )
        {

            Note n = tune[noteIndex++];
            
            this->timer = n.durVal;

            if (n.toneVal != Tone::REST)
            {
                Beep(n.toneVal, n.durVal);
            }
        }
    }

    float timer;
    Note * tune = NULL;
    int tuneLength;
    int noteIndex;

private:

    // Play the notes in a song.
    void Play(Note * tune, int length )
    {
        timer = 0;
        this->tune = tune;
        this->tuneLength = length;
        this->noteIndex = 0;
    }

};
