#pragma once
#include <filesystem>
#include <iostream>
#include <vector>
#include "console.h"
#include<Windows.h>
#include <string>
enum Settings
{
	SetWidth, SetHeight, Exit
};
enum TeacherOptions{CREATETEST,EXIT1};
enum MainMenuOptions { STUDENT, TEACHER, EXIT };
enum StudentOptions {LOGIN,REGISTER};
namespace fs = std::filesystem;
using namespace std;
class Menu {
protected:
	long long activeOption = 0;
	vector<string> options;
public:
	Menu() {}
	Menu(const vector<string>& options) {
		this->options = options;
	}
	void generate(const std::vector<std::string> options)
	{
		this->options = options;
	}
	void drawFrame() {
		size_t width = getFrameWidth();
		size_t height = getFrameHeight();
		for (short y = 0; y < height; y++)
		{
			for (short x = 0; x < width; x++)
			{
				if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
	}
	void drawOptions() {
		drawFrame();
		short startX = 3;
		short startY = 2;
		size_t max = getMaxItemSize();
		for (size_t i = 0; i < options.size(); i++)
		{
			SetCursorPosition(startX, startY + (short)i);
			if (activeOption == i) {
				SetColor(RED, WHITE);
			}
			else {
				SetColor(WHITE, BLACK);
			}
			std::string item = options[i];
			item.append(string(max - item.size(), ' '));
			cout << item;
		}
	}
	void down() {
		activeOption++;
		if (activeOption >= (long long)options.size()) {
			activeOption = 0;
		}
	}
	void up() {
		activeOption--;
		if (activeOption < 0) {
			activeOption = options.size() - 1;
		}
	}
	size_t getSelectedOption() const {
		return activeOption;
	}
	size_t getMaxItemSize() const {
		size_t max = 0;
		for (string item : options)
		{
			if (item.size() > max) {
				max = item.size();
			}
		}
		return max;
	}
	size_t getFrameWidth() const {
		return getMaxItemSize() + 6;
	}
	size_t getFrameHeight() const {
		return options.size() + 4;
	}
};
class StudentMenu : public Menu {
private:
	string question;
public:
	StudentMenu(const std::vector<std::string>& options, const std::string question) {
		this->question = question;
		this->options = options;
	}
	void generate(const std::vector<std::string> options, const std::string question)
	{
		this->options = options;
		this->question = question;
	}
	void drawQuestion()
	{
		size_t width = question.size() + 2 > getFrameWidth() ? question.size() + 2 : getFrameWidth();
		for (short y = 0; y < 3; y++)
		{
			for (short x = 0; x < width; x++)
			{
				if (x == 0 || x == width - 1 || y == 0 || y == 2) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
		SetCursorPosition(1, 1);
		std::cout << question;
	}
	void drawFrame() {
		size_t width = getFrameWidth() > question.size() ? getFrameWidth() : question.size() + 2;
		size_t height = getFrameHeight() + 2;
		drawQuestion();
		for (short y = 0; y < height; y++)
		{
			for (short x = 0; x < width; x++)
			{
				if (x == 0 || x == width - 1 || y == 2 || y == height - 1) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
	}
	void drawOptions() {
		drawFrame();
		short startX = 3;
		short startY = 4;
		size_t max = getMaxItemSize();
		for (size_t i = 0; i < options.size(); i++)
		{
			SetCursorPosition(startX, startY + (short)i);
			if (activeOption == i) {
				SetColor(RED, WHITE);
			}
			else {
				SetColor(WHITE, BLACK);
			}
			std::string item = options[i];
			item.append(string(max - item.size(), ' '));
			cout << item;
		}
	}
};
	WCHAR keymenu()
{
	WCHAR key;
	while (true)
	{
		SetColor(WHITE, BLACK);
		key = GetKey();
		if (key == -1) {
			Sleep(10);
			continue;
		}
		else return key;
	}
}
	void drawnameframe(const size_t width, const size_t height, const size_t startX, const size_t startY)
	{
		for (size_t y = startY; y < height; y++)
		{
			for (size_t x = startX; x < width; x++)
			{
				if (x == startX or x == width - 1 or y == startY or y == height - 1) {
					SetCursorPosition((short)x, (short)y);
					SetColor(ConsoleColor::WHITE, GRAY);
					std::cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
	}
	void warnmessage(const std::string message, ConsoleColor color)
	{
		system("cls");
		std::string mes = message + " Press Enter:";
		drawnameframe(75, 12, 35, 8);
		SetCursorPosition(55 - (short)message.size() / 2, 10);
		SetColor(color, BLACK);
		std::cout << message;
		WCHAR key = -1;
		while (true)
		{
			key = GetKey();
			if (key == ENTER or key == ESC) {
				SetColor(WHITE, BLACK);
				system("cls");
				return;
			}
		}
	}
size_t mainmenu(std::vector<std::string> mes)
{
	Menu menu(mes);
	menu.drawOptions();
	while (true)
	{
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
			return menu.getSelectedOption();
		}
		}
	}
}
