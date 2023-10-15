/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
*/

#include "GameSource.h"
#include "MusicPlayer.h"

GameSource game;
MusicPlayer music;
int toneIndex = 0xffff;

void quit(KEY_EVENT_RECORD);
void spacebarPressed(KEY_EVENT_RECORD ker);
void musicNote(KEY_EVENT_RECORD key);
void playMessage(KEY_EVENT_RECORD key);
void rotateNote(KEY_EVENT_RECORD key);

int main()
{
	game.initaliseGame();

	game.kInput.registerOnKey(VK_SPACE, spacebarPressed);
	game.kInput.registerOnKey(VK_ESCAPE, quit);
	
	game.kInput.registerOnKey('A', musicNote);
	game.kInput.registerOnKey('B', musicNote);
	game.kInput.registerOnKey('C', musicNote);
	game.kInput.registerOnKey('D', musicNote);
	game.kInput.registerOnKey('E', musicNote);
	game.kInput.registerOnKey('F', musicNote);
	game.kInput.registerOnKey('G', musicNote);
	game.kInput.registerOnKey('Q', rotateNote);
	game.kInput.registerOnKey('W', playMessage);

	game.gameLoop();

	return 0;
}

void playMessage(KEY_EVENT_RECORD key)
{
	if (!key.bKeyDown) return;

	UINT sounds[] = {
		MB_ICONASTERISK,
		MB_ICONEXCLAMATION,
		MB_OK,
		MB_ICONWARNING,
		MB_ICONSTOP,
		MB_ICONQUESTION,
		MB_ICONINFORMATION,
		MB_ICONHAND,
		MB_ICONERROR,
		MB_ICONEXCLAMATION,
		MB_ICONASTERISK
	};

	if (toneIndex >= 11)
	{
		toneIndex = 0;
	}

	cout << toneIndex << endl;

	MessageBeep(sounds[toneIndex++]);
}

void rotateNote(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown)
	{
		return;
	}

	MusicPlayer::Tone tones[] = {
		MusicPlayer::Tone::GbelowC,
		MusicPlayer::Tone::A,
		MusicPlayer::Tone::Asharp,
		MusicPlayer::Tone::B ,
		MusicPlayer::Tone::C ,
		MusicPlayer::Tone::Csharp ,
		MusicPlayer::Tone::D ,
		MusicPlayer::Tone::Dsharp ,
		MusicPlayer::Tone::E ,
		MusicPlayer::Tone::F ,
		MusicPlayer::Tone::Fsharp ,
		MusicPlayer::Tone::G ,
		MusicPlayer::Tone::Gsharp 
	};

	toneIndex++;

	if (toneIndex >= 13)
	{
		toneIndex = 0;
	}

	music.PlayNote(tones[toneIndex]);

	//if (toneIndex > 0x7fff)
	//{
	//	toneIndex = 0x25;
	//}

	//music.PlayNote((MusicPlayer::Tone)toneIndex);
	//toneIndex += 100;
	//cout << toneIndex << endl;
}


void musicNote(KEY_EVENT_RECORD ker)
{
	MusicPlayer::Tone tone;

	switch (ker.wVirtualKeyCode)
	{	
		case 'A':
			tone = MusicPlayer::Tone::A;
			break;
		case 'B':
			tone = MusicPlayer::Tone::B;
			break;
		case 'C':
			tone = MusicPlayer::Tone::C;
			break;
		case 'D':
			tone = MusicPlayer::Tone::D;
			break;
		case 'E':
			tone = MusicPlayer::Tone::E;
			break;
		case 'F':
			tone = MusicPlayer::Tone::F;
			break;
		case 'G':
			tone = MusicPlayer::Tone::G;
			break;
		default:
			tone = MusicPlayer::Tone::REST;
	}

	if (ker.bKeyDown)
	{
		music.PlayNote(tone);
	}
}

void spacebarPressed(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown)
	{
		return;
	}

	game.playMusic();

}

void quit(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown)
	{
		return;
	}

	game.quit();
}