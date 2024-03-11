#pragma once
#include <filesystem>
#include "Questions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#pragma warning(disable : 4996)
namespace fs = std::filesystem;
class Teacher
{
private:
	Test test;
public:
	Teacher() {}
	void createquestion(size_t num)
	{
		std::string question;
		std::vector<std::string> answers;
		size_t rightnum;
		size_t amount;
		std::string buffer;
		drawnameframe(80, 10, 0, 0);
		SetCursorPosition(1, 1);
		std::cout << "Enter name of question " << num << ": ";
		std::getline(std::cin, question);
		SetCursorPosition(1, 2);
		std::cout << "Enter amount of answers: ";
		std::cin >> amount;
		std::cin.ignore(99999, '\n');
		system("cls");
		drawnameframe(80, 3, 0, 0);
		SetCursorPosition(1, 1);
		std::cout << "Enter Answers: ";
		drawnameframe(80, amount + 4, 0, 2);
		for (size_t i{}; i < amount; i++)
		{
			SetCursorPosition(1, (short)i + 3);
			std::cout << i + 1 << ": ";
			std::getline(std::cin, buffer);
			answers.push_back(buffer);
		}
		system("cls");
		StudentMenu rights(answers, "Select right answer");
		rights.drawOptions();
		while (true)
		{
			switch (keymenu())
			{
			case VK_UP:
			{
				rights.up();
				rights.drawOptions();
				break;
			}
			case VK_DOWN:
			{
				rights.down();
				rights.drawOptions();
				break;
			}
			case ENTER:
			{
				system("cls");
				rightnum = rights.getSelectedOption() + 1;
				std::ofstream out(Testspath.string() + test.getname() + "/Question " + std::to_string(num) + ".txt", std::ios::out);
				out << question << '\n';
				out << rightnum << '\n';
				for (const auto& i : answers)
				{
					out << i << '\n';
				}
				warnmessage("Success!", GREEN);
				out.close();
				return;
			}
			}
		}
	}
	void createtest()
	{
		FileCryptor crypter;
		std::string name;
		size_t amount;
		drawnameframe(55, 10, 0, 0);
		SetCursorPosition(1, 1);
		std::cout << "Enter name of Test: ";
		std::getline(std::cin, name);
		SetCursorPosition(1, 2);
		test.setname(name);
		std::cout << "Enter amount of questions: ";
		std::cin >> amount;
		std::cin.ignore(99999, '\n');
		system("cls");
		fs::create_directory(Testspath.string() + name);
		for (size_t i{}; i < amount; i++)
		{
			createquestion(i + 1);
		}
		system("cls");
		crypter.cryptDirectory(Testspath.string() + name);
	}
	void run()
	{
		Menu menu({ "Create test","Exit" });
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
				case CREATETEST:
					system("cls");
					createtest();
					break;
				case TeacherOptions::EXIT1:
					return;

				}
				break;
			}
			case ESC:
			{
				system("cls");
				return;
			}
			}
		}
	}
};
class Student
{
private:
	Test test;
	fs::path login;
public:
	Student()
	{

	}
	void writepass(std::string name,fs::path path)
	{
	std::ofstream out(path, std::ios::out);
	out << name << '\n';
	out.close();
	}
	bool Login()
	{
		std::string name;
		std::string password;
		FileCryptor crypter;
		drawnameframe(75, 11, 35, 8);
		SetCursorPosition(36, 9);
		std::cout << "Enter name: ";
		std::getline(std::cin, name);
		if (!fs::exists(Studentpath.string() + name))
		{
			system("cls");
			warnmessage("No such login exists!", RED);
			return false;
		}
		if (name == "")
		{
			warnmessage("Username cannot be empty!", RED);
			return false;
		}
		else
		{
			system("cls");
			drawnameframe(75, 11, 35, 8);
			SetCursorPosition(36, 9);
			std::cout << "Enter password: ";
			SetColor(WHITE,WHITE);
			std::getline(std::cin,password);
			SetColor(WHITE, BLACK);
			crypter.decrypt(Studentpath.string() + name + "/password.txt");
			std::ifstream pass(Studentpath.string() + name + "/password.txt");
			std::string buffer;
			std::getline(pass, buffer);
			system("cls");
			if (password == buffer)
			{
				this->login = Studentpath.string() + name;
				warnmessage("Success!", GREEN);
			}
			else warnmessage("Incorrect password!", RED);
			pass.close();
			crypter.crypt(Studentpath.string() + name + "/password.txt");
			return password == buffer;
		}
	}
	bool Register()
	{
		std::string name;
		std::string password;
		std::string password2;
		FileCryptor crypter;
		drawnameframe(75, 11, 35, 8);
		SetCursorPosition(36, 9);
		std::cout << "Enter name: ";
		std::getline(std::cin, name);
		if (fs::exists(Studentpath.string() + name))
		{
			warnmessage("This account already exists!", RED);
			return false;
		}
		if (name == "")
		{
			warnmessage("Username cannot be empty!", RED);
			return false;
		}
		system("cls");
		drawnameframe(75, 11, 35, 8);
		SetCursorPosition(36, 9);
		std::cout << "Enter password: ";
		std::getline(std::cin, password);
		system("cls");
		drawnameframe(75, 11, 35, 8);
		SetCursorPosition(36, 9);
		std::cout << "Confirm password: ";
		std::getline(std::cin, password2);
		system("cls");
		if (password == password2)
		{
			login = Studentpath.string() + name;
			fs::create_directory(login);
			writepass(password, login.string() + "/password.txt");
			crypter.crypt(login.string() + "/password.txt");		
			fs::create_directory(login.string() + "/Results");
			warnmessage("Success!", GREEN);
		}
		else warnmessage("Passwords don't match!", RED);
		system("cls");
		return password == password2;
	}
	size_t start()
	{
		Menu menu({ "Login","Register","Exit" });
		while (true)
		{
			menu.drawOptions();
			switch (keymenu())
			{
			case VK_UP:
				menu.up();
				menu.drawOptions();
				break;
			case VK_DOWN:
				menu.down();
				menu.drawOptions();
				break;
			case ENTER:
			{
				system("cls");
				switch (menu.getSelectedOption())
				{
				case LOGIN:
					if (Login())
					{
						return 0;
					}
					break;
				case REGISTER:
					if (Register())
					{
						return 0;
					}
					break;
				case MainMenuOptions::EXIT:
					return EXIT;
				}
				break;
			}
			case ESC:
			{
				system("cls");
				return 0;
			}
			}
		}
	}
	void run()
	{
		switch (start())
		{
		case EXIT:
			return;
		}
		while (true)
		{
			std::pair<size_t, std::chrono::duration<double>> result = test.run();
			long long points = result.first;
			if (points == -1) { return; }
			time_t now = time(0);
			std::string timetook = std::to_string(result.second.count());
			timetook = timetook.substr(0, timetook.find('.')) + " Seconds";
			std::string dt = ctime(&now);
			std::cout << "You scored " << points << " Out of " << test.getcurrenttest().size() << '\n';
			std::cout << "Total score: " << (double)points / test.getcurrenttest().size() * 100 << "%\n";
			std::ofstream out(login.string() + "/results/" + test.getname() + ".txt", std::ios::app);
			out << "Scored " << points << " Out of " << test.getcurrenttest().size() << '\n';
			out << "Finished in: " << dt;
			out << "Total time took: " << timetook << '\n';
			while (keymenu() != ENTER);
			system("cls");
			out.close();
		}
	}
};
