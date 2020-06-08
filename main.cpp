#include "proto-terminal.h"

#define NMAX 1000 // maximo  de comandos
#define SMAX 100  // maximo de argumentos


void startTerminal()
{
    puts(
    "\n****************************"
    "\n*****  Proto-Terminal  *****"
    "\n****************************"
    "\n"
    ); 
    char* username = getenv("USER"); 
    
    return; 
}

void help()
{ 
    puts("\n*******Comandos do Terminal*******"
        "\n>cd -> Abre o diretório desejado"
        "\n>ls -> Mostra o diretório atual"
        "\n>pwd -> Mostra o caminho completo para o diretório atual"
        "\n>./ -> Usado para abrir diretório e pode ser modificado com: >, <, | e & "
        "\n>exit -> Fecha o terminal"); 
  
    return; 
}

void parser(string entrada){
    string buffer[NMAX];
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
        cout << buffer[i] << "\n";
    }
 
    return;

}

int main(){
    
    string entrada ("");
    startTerminal();
    do{
        getline(cin,entrada);
        if(entrada != "exit"){
            parser(entrada);
        }

    }while(entrada != "exit");

}