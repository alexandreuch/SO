#include "proto-terminal.h"
#include <unistd.h>
#include <sys/wait.h> 

#define NMAX 1000 // maximo  de comandos
#define SMAX 100  // maximo de argumentos

void help()
{ 
    puts("\n╔════════════════════════════ Comandos do Terminal ════════════════════════════╗"
        "\n║                                                                              ║" 
        "\n║> cd -> Abre o diretório desejado.                                            ║" 
        "\n║> ls -> Mostra o diretório atual.                                             ║"
        "\n║> pwd -> Mostra o caminho completo para o diretório atual.                    ║"
        "\n║> ./ -> Usado para abrir diretório e pode ser modificado com: >, <, | e &.    ║"
        "\n║> exit -> Fecha o terminal.                                                   ║"
        "\n║                                                                              ║" 
        "\n╚══════════════════════════════════════════════════════════════════════════════╝\n");

    return; 
}

void cd(string buffer[], int index){
    string pathAux;
    fs::path diretorio;

    if(index <=1){
        cout << "Diretório não especificado corretamente.\n";
        return;
    }
    if(index=2 && buffer[1]==".."){
        diretorio=fs::current_path().parent_path();
        fs::current_path(diretorio);
        return;
    }
    else if(index>2){
        for(int i = 1; i<=index; i++){
            pathAux += buffer[i];
        }
    } 
    else{
        pathAux = buffer[1];
    }

    diretorio = pathAux;
    fs::current_path(diretorio);

    return;
}
    
void ls(){
    string path = fs::current_path();
    int tamanhoPath = (path.length()+1);
    cout << endl;

    for(const auto & entry : fs::directory_iterator(path)){
        string ls = (entry.path());
        cout << ls.substr(tamanhoPath) << endl;
    }
    cout << endl;
    return;
}

void pwd(){
    fs::path diretorio = fs::current_path();
    string dir = ((string)diretorio);
    cout << dir;

    return;
}

int verificaPipe(string buffer[],int index){ // Verifica se em alguma parte da string o | e encontrado
    for(int i = 0; i < index; i++){ 
        if(buffer[i] == "|"){
            return 1;
        }    
    }
    return 0;
}

int verificaExec(string elemento){
    string path = fs::current_path();
    int tamanhoPath = (path.length()+1);
    int tamanhoElemento = elemento.length();
    int retorno = 0; // Indica se o elemento e um ./exec ou exec

    if(elemento[0] == '.' && elemento[1] == '/'){ // Faz os os ./exec virarem exec.
        elemento = elemento.substr(2,tamanhoElemento);
        retorno++;
    }

    for(const auto & entry : fs::directory_iterator(path)){ // Verifica se o exec esta presente no diretorio atual
        string ls = (entry.path());
        string aux = ls.substr(tamanhoPath);
        if(elemento == aux){
            retorno++;
            return retorno;
        }
    }
   return 0;
}

void executa();

void interpretador(string buffer[], int index){
    string pathAux = ("");

    fs::path diretorio;
    
    int flag = verificaPipe(buffer,index);
    int flagExec = (verificaExec(buffer[0]));

    if(flag == 0){    
        if(buffer[0] == "help"){
            help();
        }
        else if(buffer[0] == "cd"){
            cd(buffer, index);
        }
        else if(buffer[0] == "ls"){
            ls();
        }
        else if(buffer[0] == "pwd"){
            pwd();
            cout << "\n";
        }
        else if(buffer[0] == "\0");
        
        else if(flagExec >= 1 && index == 1){
            if (flagExec == 1){
                buffer[0] = "./" + buffer[0];

            }

            //executa();

        }
        else{
            string aux ("");
            for(int i = 0; i < index; i++){
                if(i == (index-1)){
                    aux += buffer[i];
                }
                else{
                    aux += buffer[i] + " ";
                }
            }
        
        cout << "O comando '" << aux << "' nao e conhecido.\n";
        }
    }    
    else{

    }
    
    return;
}

void parser(string entrada){
    string buffer[NMAX];
    int ini = 0, fim = 0, index = 0;

    for(int i=0; i<entrada.length();i++){
        if(isspace(entrada[i]) && isspace(entrada[i-1]) && i>0){
            ini++;
            fim --;
        }
        else{
            if(isspace(entrada[i])){
                buffer[index] = entrada.substr(ini,fim);
                ini = i + 1;
                fim = -1;
                index++;
            } 
        }    
        fim ++;
    }
    buffer[index] = entrada.substr(ini,fim);
    index++;
    
    /*
    for(int i = 0;i <= index;i++){
        cout << buffer[i] << "\n";
    }
    cout <<"index "<< index << "\n";
    */
    
    interpretador(buffer, index);
    
    return;
}

string startTerminal()
{
    puts(
    "\n╔══════════════════════════════════════════════════════════════╗"
    "\n║                        PROTO-TERMINAL©                       ║"
    "\n╚══════════════════════════════════════════════════════════════╝\n\n"
    ); 
    
    string username =  getenv("USER"); 
    
    return username; 
}

int main(){

    string entrada (""), username = ("");
    //path 
    // /= append 

    username = startTerminal()+"@";
    
    do{
        cout << username;
        pwd();
        cout << " ─► ";
        
        getline(cin,entrada);
        if(entrada != "exit"){
            parser(entrada);
        }

    }while(entrada != "exit");

}
