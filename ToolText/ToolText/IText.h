#pragma once
#include <string>

using namespace std;

class  IText
{
public:
	IText()
	{}

	virtual	~IText()
	{}

	virtual void ReadFile(const char *fileName) = 0;
	virtual void WriteFile(const char *fileName) = 0;
	virtual wstring GetText() = 0;
	virtual void SetText(wstring wstr) = 0;
};
