#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h> 

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