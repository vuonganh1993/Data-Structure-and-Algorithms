#include <iostream>
#include "Screen.h"
#include "Text.h"

using namespace std;

int main()
{
	Text *text = new Text("poem.txt");
	text->Read();

	Screen screen;
	screen.Print(text->GetTextSource()->GetText());

	system("pause");
	return 0;
}