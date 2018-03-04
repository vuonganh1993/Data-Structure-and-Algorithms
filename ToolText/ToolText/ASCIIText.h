#pragma once
#include "IText.h"
#include <fstream>

using namespace std;

class ASCIIText :public IText
{
private:
	string asciiText;
public:
	ASCIIText() : 
		asciiText("")
	{}
	~ASCIIText();

	void ReadFile(const char *fileName)
	{
		ifstream myfile(fileName);
		string temp;
		if (myfile.is_open())
		{
			while (getline(myfile, temp))
			{
				asciiText += temp;
				asciiText += "\n";
			}
			myfile.close();
		}
		asciiText.pop_back();
	}

	void WriteFile(const char *fileName)
	{
		ofstream myfile(fileName);
		if (myfile.is_open())
		{
			myfile << asciiText;
			myfile.close();
		}
	}

	wstring GetText()
	{
		std::wstring wsTmp(asciiText.begin(), asciiText.end());
		return wsTmp;
	}

	void SetText(wstring wstr)
	{
		std::string str(wstr.begin(), wstr.end());
		asciiText = str;
	}

};

