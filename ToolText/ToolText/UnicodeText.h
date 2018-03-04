#pragma once
#include "IText.h"
#include <fstream>
#include <sstream>      // std::stringstream
#include <iostream>

using namespace std;

class UnicodeText : public IText 
{
private:
	wstring unicodeText;
public:

	UnicodeText();
	~UnicodeText();

	void ReadFile(const char *fileName)
	{
		std::ifstream wif(fileName);
		std::stringstream wss;
		wss << wif.rdbuf();
		std::string  const &str = wss.str();
		unicodeText.resize(str.size() / sizeof(wchar_t));
		std::memcpy(&unicodeText[0], str.c_str(), str.size()); // copy data into wstring
		wif.close();
	}

	void WriteFile(const char *fileName)
	{

	}

	wstring GetText()
	{
		return unicodeText;
	}

	void SetText(wstring wstr)
	{
		unicodeText = wstr;
	}
};

