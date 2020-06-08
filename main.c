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

void parser(char buffer[]){
    char newbuffer[SMAX];
    int i=0;
    //while(i < buffer.length()){
    //    if(isspace(buffer[i]))
     //       cout << buffer[i];
       // i++;
    //}
    

    return;
}

void interpretador(char entrada[]){
    int numComandos = 4;
    char *comandos[numComandos];
    comandos[0]=(char*)"cd";
    comandos[1]=(char*)"ls";
    comandos[2]=(char*)"pwd";
    comandos[3]=(char*)"help";

    for(int i = 0; i < numComandos; i++){
        printf("%s\n", comandos[i]);
    }
    return ;
}


//comandos
void ls();
void pwd();
void cd();



int main()
{
    char entrada[SMAX]; //entradaTratada = {};

    startTerminal();

    do{
        printf("> "); //Colocar o "dir + user + >" aqui
        fgets(entrada,SMAX,stdin);
        
        int cch = strlen(entrada);
        if (cch > 1 && entrada[cch-1] == '\n'){
            entrada[cch-1] = '\0';
        }
        
        if(entrada != "exit"){
            parser(entrada);
        }

    }while(strcmp(entrada, "exit") != 0);

}