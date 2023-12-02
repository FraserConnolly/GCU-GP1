#pragma once


enum CellColour : short
{
	Fore_Black = 0x0000,
	Fore_Blue = 0x0001,
	Fore_Green = 0x0002,
	Fore_Red = 0x0004,
	Fore_White = 0x0007,

	Fore_Cyan = Fore_Blue | Fore_Green,
	Fore_Magenta = Fore_Blue | Fore_Red,
	Fore_Yellow = Fore_Red | Fore_Green,

	Back_Black = 0x0000,
	Back_Blue = 0x0010,
	Back_Green = 0x0020,
	Back_Red = 0x0040,
	Back_White = 0x0070,

	Back_Cyan = Back_Blue | Back_Green,
	Back_Magenta = Back_Blue | Back_Red,
	Back_Yellow = Back_Red | Back_Green,
};

typedef struct _renderCellData
{
	_renderCellData ( ) :
		Char ( ' ' ),
		Attributes ( CellColour::Fore_White | CellColour::Back_Black )
	{
	}

	_renderCellData ( char symbol ) :
		Char ( symbol ),
		Attributes ( CellColour::Fore_White | CellColour::Back_Black )
	{
	}

	_renderCellData ( char symbol, CellColour colour ) :
		Char ( symbol ),
		Attributes ( colour )
	{
	}

	char  Char;
	short Attributes;

} RenderCellData, *pRenderCellData;