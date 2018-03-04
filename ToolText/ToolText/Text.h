#pragma once
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "ASCIIText.h"
#include "UnicodeText.h"


using namespace std;

enum class CHARACTER_ENCODING
{
	ASCII,
	Unicode
};

class Text
{
private:
	string fileName;
	IText *text;
	CHARACTER_ENCODING typeText;
private:
	CHARACTER_ENCODING get_text_file_encoding(const char *filename)
	{
		CHARACTER_ENCODING encoding;
		unsigned char uniTxt[] = { 0xFF, 0xFE };// Unicode file header
		DWORD dwBytesRead = 0;
		HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			CloseHandle(hFile);
		}
		BYTE *lpHeader = new BYTE[2];
		ReadFile(hFile, lpHeader, 2, &dwBytesRead, NULL);
		CloseHandle(hFile);
		if (lpHeader[0] == uniTxt[0] && lpHeader[1] == uniTxt[1])// Unicode file
			encoding = CHARACTER_ENCODING::Unicode;
		else
			encoding = CHARACTER_ENCODING::ASCII;   //Ascii

		delete[]lpHeader;
		return encoding;
	}
public:
	Text(string filename) :
		fileName(filename),
		text(nullptr),
		typeText(get_text_file_encoding(fileName.c_str()))
	{
		
	}

	~Text()
	{
		delete text;
	}

	void Read()
	{
		if (typeText == CHARACTER_ENCODING::Unicode)
		{
			text = new UnicodeText();
		}else
			if (typeText == CHARACTER_ENCODING::ASCII)
			{
				text = new ASCIIText();
			}

		text->ReadFile(fileName.c_str());
	}
	
	IText *GetTextSource()
	{
		return text;
	}

};

