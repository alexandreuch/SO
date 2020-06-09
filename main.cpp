#include "proto-terminal.h"

#define NMAX 1000 // maximo  de comandos
#define SMAX 100  // maximo de argumentos

void help()
{ 
    puts("\n************************** Comandos do Terminal **************************\n"
        "\n> cd -> Abre o diretório desejado."
        "\n> ls -> Mostra o diretório atual."
        "\n> pwd -> Mostra o caminho completo para o diretório atual."
        "\n> ./ -> Usado para abrir diretório e pode ser modificado com: >, <, | e &."
        "\n> exit -> Fecha o terminal.\n"
        "\n***************************************************************************"); 

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

    for(const auto & entry : fs::directory_iterator(path)){
        string ls = (entry.path());
        cout << ls.substr(tamanhoPath) << "\t";
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

void interpretador(string buffer[], int index){
    string pathAux = ("");

    fs::path diretorio;

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
    "\n****************************"
    "\n*****  Proto-Terminal  *****"
    "\n****************************"
    "\n"
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
        cout << " > ";
        
        getline(cin,entrada);
        if(entrada != "exit"){
            parser(entrada);
        }

    }while(entrada != "exit");

    // (destructor) path
}