#pragma once
#include <iostream>
#include <string>

using namespace std;

class Screen
{
private:

public:
	Screen();
	~Screen();

	static const int HEIGHT_SCREEN = 500;
	static const int WIDTH_SCREEN = 400;

	void Print(std::wstring wstr);
};

