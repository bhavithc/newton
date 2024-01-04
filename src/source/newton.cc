#include "newton.hpp"
#include "colors.hpp"
#include "newtonConfig.h"

#include <filesystem>
#include <ctime>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

#ifndef WIN32
#include <unistd.h>
#endif

App::App(const std::string& projectName)
	: m_projectName {projectName}
{
	if (m_projectName.empty()) {
		throw std::runtime_error("Empty project received !");
	}
}

void App::create()
{
	clock_t startTime {0};
	clock_t endTime {0};

	std::cout << GREEN << "Creating directory..." << WHITE << "\n";

	startTime = clock();
	const auto success = createProject();
	if (success) {

		std::cout << GREEN << "Generating Code for main.c and CMakeLists.txt..." 
			<< WHITE << "\n";

		generateCppTemplateFile();
		generateCmakeFile();
		generateNewtonFile();
		generateGitIgnoreFile();
	}
	endTime = clock();

	printf("%sElapsed Time : %8.2fms\nWith great power comes great responsibility\n%s", YELLOW, difftime(endTime, startTime),WHITE);
};

void App::compile()
{
	printf("%sCompile Process has been started...\n%s",BLUE,WHITE);
#ifdef WIN32
	if (!system("cmake -S . -B build -G \"MinGW Makefiles\" "))
	{
		if(!system("mingw32-make -C build"))//if there is any kind of error then don't clear the terminal
		system("cls");
	}
	else
	{
		printf("%s\n[error] Make Sure You are in Your Project's Directory!\n%s",RED,WHITE);
	};
#else
	if (!system("cmake -S . -B build"))
	{
		if(!system("make -C build/"))//if there is any kind of error then don't clear the terminal
		system("clear");
	}
	else
	{
		printf("%s\n[error] Make Sure You are in Your Project's Directory!\n%s",RED,WHITE);
	};
#endif

};

void App::run()
{
	std::string projectName;
	readNewtonFile(projectName);

	std::string run{};
	//printf("%s%s: \n%s", YELLOW, projectName.c_str(),WHITE);
#ifdef WIN32
	run += ".\\build\\";
	run += projectName;
	run += ".exe";
#else
	run += "./build/";
	run += projectName;
#endif // WIN32

	if (system(run.c_str()))
	{
		printf("%s\n[error] Maybe You should Compile First Before run or You have Permission to execute program!\n%s",RED,WHITE);
	};
}

void App::build()
{

	this->compile();
	this->run();
}

void App::setup()
{
	printf("%sAdding newton CLI to path...%s\n", YELLOW, WHITE);

	printf("\n%sthis feature is currently in development or maybe your CLI is not up to date!\n%s",CYAN,WHITE);
};

void App::generateNewtonFile()
{
	std::stringstream ss;
	ss << m_projectName << "/setting.nn";

	std::ofstream file(ss.str(), std::ios::out);
	if (file.is_open()) {
		time_t now {time(NULL)};
		const char* dateTime {ctime(&now)};
		file << m_projectName << "\n";
		file << "Project created on " << dateTime << "\n";
		std::cout << YELLOW << "Project Creation date :" << dateTime << WHITE << "\n";
		file << "Note: Please don't remove or edit this file!\n";
		file.close();
	} else {
		std::cerr << RED << "Something went wrong!\n" << WHITE << "\n";
	}
}

void App::readNewtonFile(std::string& output)
{
	std::stringstream ss;
	ss << m_projectName << "/setting.nn";

	std::ifstream file(ss.str());
	if (file.is_open()) {
		std::getline(file, output);
		std::string dateTime{};
		std::getline(file, dateTime);
		printf("%s[%s: %s]%s\n\n", YELLOW, output.c_str() ,dateTime.c_str(), WHITE);
		file.close();
	} else {
		printf("%snewton file setting.nn doesn't exist!\n%s",RED,WHITE);
	}
}

bool App::createProject()
{
	namespace fs = std::filesystem;
	auto status {false};
	std::string errorMsg {"Failed to create "};

	// Check project already exist
	if (fs::exists(m_projectName)) {
		std::cerr << RED << m_projectName 
			<< " already exist unable to create project" << WHITE << "\n";
		return false;
	}

	// Create project folder
	status = fs::create_directories(m_projectName);
	if (status != true) {
		errorMsg += m_projectName;
		goto ERROR;
	}

	// Create build folder
	status = fs::create_directories(m_projectName + "/build");
	if (status != true) {
		errorMsg += m_projectName + "/build";
		goto ERROR;
	}

	// Create src folder
	fs::create_directories(m_projectName + "/src");
	if (status != true) {
		errorMsg += m_projectName + "/src";
		goto ERROR;
	}

	// Create res folder
	fs::create_directories(m_projectName + "/res");
	if (status != true) {
		errorMsg += m_projectName + "/res";
		goto ERROR;
	}

ERROR:
	if (status != true) {
		std::cerr << RED << errorMsg << WHITE << "\n";
	}

	return status;
};

std::string cppTemplate()
{
	std::string brief{R"(/**
 * @brief Auto generated C++ file by newton CLI
 *        )"};
 
    brief += NEWTON_COPYRIGHT;
	brief += "\n */";

	std::string main {R"(

#include<iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello, test\n";
    std::cout << "Happy coding journey :)\n";

    return 0;
};

	)"};

	return brief + main;
}

std::string App::cmakeTemplate()
{
	std::string script {""};
	script += "# Auto Genrated CMake file by newton CLI\n";
	script += "# ";
	script += NEWTON_COPYRIGHT;
	script += "\n";
	script += "cmake_minimum_required(VERSION 3.0.0)\n";
	script += "set(CMAKE_CXX_STANDARD 17)\n";
	script += "\n";
	script += "project(" + m_projectName + " VERSION 1.0.0)\n";
	script += "\n";
	script += "# Add your additional source file here!\n";
	script += "set(SOURCE src/main.cc)\n";
	script += "\n";
	script += "add_executable(${PROJECT_NAME} ${SOURCE})\n";
	script += "\n";
	script += "install(TARGETS ${PROJECT_NAME} DESTINATION bin)\n";

	return script;
}

void App::generateCppTemplateFile()
{
	std::ofstream file;
	std::stringstream ss;
	ss << m_projectName << "/src/main.cc";
	
	file.open(ss.str(), std::ios::out);
	if (file.is_open()) {
		file << cppTemplate();
		file.close();
	}
}

void App::generateCmakeFile()
{
	std::ofstream file;
	std::stringstream ss;
	ss << m_projectName << "/CMakeLists.txt";

	file.open(ss.str(), std::ios::out);
	if (file.is_open()) {
		file << cmakeTemplate();
		file.close();
	}
}

void App::generateGitIgnoreFile()
{
	std::ofstream file;
	std::stringstream ss;
	ss << m_projectName << "/.gitignore";

	file.open(ss.str(), std::ios::out);
	if (file.is_open()) {
		file << "build";
		file.close();
	}
}
