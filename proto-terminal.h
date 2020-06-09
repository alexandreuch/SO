#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
string startTerminal();
void help();

void cd(string, int);
void interpretador(string, int);
void pwd();