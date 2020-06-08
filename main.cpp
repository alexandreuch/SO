#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

#define NMAX 1000 // maximo  de comandos
#define SMAX 100  // maximo de argumentos


#include <ostream>
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

class Terminal
{
private:
    char* username;
    char* PATH;
public:
     Terminal(/* args */);
     void draw_interface();
     void clear_interface();
};

Terminal::Terminal(/* args */)
{
    username = getenv("USER");
    PATH = getenv("PWD");
};

void Terminal::draw_interface(){
    Color::Modifier user(Color::FG_RED);
    Color::Modifier path(Color::FG_RED);
    Color::Modifier arrow(Color::FG_GREEN);
    Color::Modifier text(Color::FG_DEFAULT);

    std::cout << user << username << text <<" is using ProtoTeminal in " << path << PATH << "\n";
    std::cout << arrow << "➜ ";
}

void Terminal::clear_interface(){
    printf("\033[H\033[J");
}


void parser(std::string entrada){
    std::string buffer[NMAX];
    int ini = 0, index = 0, cont = 0;

    for(int i=0; i<entrada.length();i++){
        if(isspace(entrada[i]) && isspace(entrada[i-1]) && i>0){
            ini++;
            cont --;
        }
        else{
            if(isspace(entrada[i])){
                buffer[index] = entrada.substr(ini,cont);
                ini = i + 1;
                cont = -1;
                index++;
            } 
        }    
        cont ++;
    }
    buffer[index] = entrada.substr(ini,cont);

    for(int i = 0;i <= index;i++){
        std::cout << buffer[i] << "\n";
    }
 
    return;

}

int main(){
    
    std::string entrada ("");
    // startTerminal();
    Terminal terminal = Terminal();
    terminal.clear_interface();
    do{
        terminal.draw_interface();
        getline(std::cin,entrada);
        if(entrada != "exit"){
            parser(entrada);
        }

    }while(entrada != "exit");

}