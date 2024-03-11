#pragma once
#include <iostream>
#include "Menu.h"
#include "Console.h"
#include "FileCryptor.h"
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
const fs::path Testspath = "D:\\Mein Progectos/MyStatV3.0/Tests/";
const fs::path Studentpath = "D:\\Mein Progectos/MyStatV3.0/Students/";
class Question
{
private:
	std::string question;
	std::vector<std::string> answer;
	size_t rightnum;
public:
	Question(const std::string question, const std::vector<std::string>& answers, const size_t rightnum)
	{
		generate(question, answers, rightnum);
	}
	Question()
	{
		rightnum = 0;
	}
	void generate(const std::string question, const std::vector<std::string>& answers, const size_t rightnum)
	{
		this->question = question;
		this->answer = answers;
		this->rightnum = rightnum;
	}
	void printall()
	{
		std::cout << this->question << '\n';
		for (size_t i{}; i < answer.size(); i++)
		{
			std::cout << i + 1 << ": " << answer[i] << '\n';
		}
		std::cout << "Right answer: " << answer[rightnum - 1] << '\n';
	}
	std::vector<std::string> getanswers()
	{
		return answer;
	}
	size_t getrightnum()
	{
		return rightnum;
	}
	std::string getquestion()
	{
		return question;
	}
};
class Test
{
private:
	std::vector<Question> Quiz;
	std::string name;
public:
	Test() {}
	Test(const std::string question, const std::vector<std::string>& answers, const size_t rightnum)
	{
		generate(question, answers, rightnum);
	}
	Test(std::string name)
	{
		this->name = name;
		load(Testspath.string() + name);
	}
	void setname(std::string name)
	{
		this->name = name;
	}
	void generate(const std::string question, const std::vector<std::string>& answers, const size_t rightnum)
	{
		Quiz.push_back({ question, answers, rightnum });
	}
	void load(fs::path path)
	{
		FileCryptor crypter;
		crypter.decryptDirectory(path);
		this->name = path.filename().string();
		Quiz.clear();
		size_t rightnum;
		std::vector<std::string>answers;
		std::string name;
		std::string buffer;
		for (const auto& i : fs::directory_iterator(path))
		{
			std::ifstream in(i.path());
			std::getline(in, name);
			std::getline(in, buffer);
			rightnum = stoi(buffer);
			while (std::getline(in, buffer))
			{
				answers.push_back(buffer);
			}
			generate(name, answers, rightnum);
			answers.clear();
			in.close();
		}
		crypter.cryptDirectory(path);
	}
	std::pair<size_t, std::chrono::duration<double>> StartTest() {
		
		auto start = std::chrono::system_clock::now();
		size_t points = 0;
		size_t current = 0;
		StudentMenu menu(Quiz[current].getanswers(), Quiz[current].getquestion());
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
				points += Quiz[current].getrightnum() - 1 == menu.getSelectedOption();
				system("cls");
				current++;
				if (Quiz.size() <= current)
				{
					auto end = std::chrono::system_clock::now();
					std::chrono::duration<double> testtime =  end - start;
					return { points,testtime };
				}
				menu.generate(Quiz[current].getanswers(), Quiz[current].getquestion());
				menu.drawOptions();
				break;
			}
			}	
		}
	}
	WCHAR testmenu()
	{
		fs::path testpath = "D:\\Mein Progectos/MyStatV3.0/Tests";
		std::vector<std::string> paths;
		bool work = true;
		for (const auto& i : fs::directory_iterator(testpath))
		{
			paths.push_back(i.path().filename().string());
		}
		Menu menu(paths);
		menu.drawOptions();
		while (work)
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
				system("cls");
				testpath += '/' + paths[menu.getSelectedOption()];
				load(testpath);
				work = false;
				return 0;
				break;
			}
			case ESC:
				system("cls");
				return ESC;
			}
			if (!work) { work = true; break; }
		}
		system("cls");
	}
	std::pair<size_t, std::chrono::duration<double>> run()
	{
		std::chrono::duration<double> time;
		if(testmenu() == ESC)
		return { -1,time };
		return StartTest();
	}
	std::string getname()
	{
		return name;
	}
	std::vector<Question> getcurrenttest()
	{
		return Quiz;
	}
};
