#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <experimental/filesystem>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h> 
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
namespace fs = std::experimental::filesystem;


string startTerminal();
int takeInput(string);
void parser(string);
void interpretador(string, int);


void help();
void cd(string, int);
void pwd();
void ls(string, int);