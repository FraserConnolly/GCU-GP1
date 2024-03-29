#include "MusicPlayer.h"

MusicPlayer::~MusicPlayer()
{
    if (m_tune != nullptr)
    {
        delete[] m_tune;
    }
}

void MusicPlayer::PlayNote ( const Tone tone )
{
    if ( tone == Tone::REST )
    {
        return;
    }

    Beep ( tone, 250 );
}

void MusicPlayer::tick ( const float deltaTime )
{
    if ( m_tune == nullptr )
    {
        return;
    }

    if ( m_noteIndex >= m_tuneLength )
    {
        // tune had finished so delete the tune.
        if ( m_tune != nullptr )
        {
            delete [ ] m_tune;
        }

        m_tune = nullptr;
        return;
    }

    m_timer -= deltaTime;

    if ( m_timer <= 0 && !m_notePlaying )
    {

        Note n = m_tune [ m_noteIndex++ ];

        m_timer = ( float ) n.durVal;

        if ( n.toneVal != Tone::REST )
        {
            asyncBeep ( n.toneVal, n.durVal );
        }
    }
}

// Play the notes in a song.
void MusicPlayer::Play ( Note * tune, int length )
{
    if (m_tune != nullptr)
    {
        // delete existing memory
        delete [ ] m_tune;
        m_tune = nullptr;
    }

    m_timer = 0;
    m_tune = tune;
    m_tuneLength = length;
    m_noteIndex = 0;
}

inline void MusicPlayer::asyncBeep ( int tone, int duration )
{
    if ( m_notePlaying )
    {
        cout << "Can not play note at the moment" << endl;
        return;
    }

    m_asyncResult =
        std::async ( std::launch::async, &MusicPlayer::playBeepAsync, this, tone, duration );
}

inline void MusicPlayer::playBeepAsync ( int frequency, int duration )
{
    m_notePlaying = true;
    Beep ( frequency, duration );
    m_notePlaying = false;
}
