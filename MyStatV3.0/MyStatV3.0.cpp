
#include "Tests.h"
#include "Shift.h"
using namespace std;
using namespace shift;
int main()
{
	Student student;
	Teacher teacher;
	Menu menu({"Student","Teacher","Exit"});
	while (true)
	{
		menu.drawOptions();
		switch (keymenu())
		{
		case VK_UP:
		{
			menu.up();
			menu.drawOptions();
			break;
		}
		case VK_DOWN:
		{
			menu.down();
			menu.drawOptions();
			break;
		}
		case ENTER:
		{
			system("cls");
			switch (menu.getSelectedOption())
			{
			case STUDENT:
				student.run();
				break;
			case TEACHER:
				teacher.run();
				break;
			case MainMenuOptions::EXIT:
				return 0;
			}
		}
		}
	}
}