#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <filesystem>



using namespace std;
namespace fs = std::filesystem;


string startTerminal();
int takeInput(string);
void parser(string);
void interpretador(string, int);


void help();
void cd(string, int);
void pwd();
void ls(string, int);