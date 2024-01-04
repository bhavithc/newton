#pragma once

#include <string>

class App
{

public:
      App(const std::string& projectName);
      void create();
      void compile();
      void run();
      void build();
      void setup();
private:
      void generateNewtonFile();
      void readNewtonFile(std::string &);
      bool createProject();
      void generateCppTemplateFile();
      std::string cmakeTemplate();
      void generateCmakeFile();
      void generateGitIgnoreFile();

      std::string m_projectName {""};
};