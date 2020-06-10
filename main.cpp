#include "proto-terminal.h"
#include <unistd.h>
#include <cstring>
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
    fs::directory_entry flag;

    if(index <= 1){
        cout << "Diretório não especificado corretamente.\n";
        return;
    }
    if(index == 2 && buffer[1] == ".."){
        diretorio=fs::current_path().parent_path();
        fs::current_path(diretorio);
        return;
    }
    else if(index > 2){
        for(int i = 1; i<=index; i++){
            pathAux += buffer[i];
        }
    } 
    else{
        pathAux = buffer[1];
    }

    flag.assign(pathAux);
    if(!flag.exists()){
        cout << "Diretório não especificado corretamente.\n";
        return;
    }

    diretorio = pathAux;
    fs::current_path(diretorio);

    return;
}
    
void ls(string buffer[], int index){
    string path;
    int tamanhoPath;
    fs::directory_entry diretorio;

    if(index == 1 ){
        path = fs::current_path();
        tamanhoPath = (path.length()+1);
    }
    else{
        if(index >= 2){
            for(int i = 1; i<=index; i++){
                path += buffer[i];
                if(i < index-1){ 
                    path += " ";
                }
            }
            path = (fs::path)path;
            tamanhoPath = path.length();


        }
    }

    diretorio.assign(path);

    if(!diretorio.exists()){
        cout << "Diretório não especificado corretamente.\n";
        return;
    }
        
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

void executa(char** vetor) { 
    
    pid_t pid = fork();  

    if (pid < 0) { 
        cout << "Falha no Fork\n"; 
        return; 
    } else if (!pid) {
        int flag = execvp(vetor[0], vetor);

        if (flag < 0) { 
            cout << "O comando não existe\n"; 
        }
        
        exit(0); 
    
    } else {
        wait(NULL);  
        return; 
    } 
}

void execArgsPiped(char** parsed, char** parsedpipe){ 
    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        cout << "\nPipe could not be initialized"; 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        cout << "\nCould not fork"; 
        return; 
    } 
  
    if (p1 == 0) {
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(parsed[0], parsed) < 0) { 
            cout << "\nCould not execute command 1.."; 
            exit(0); 
        }

    } else {
        p2 = fork();   
        
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 

        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                cout << "\nCould not execute command 2.."; 
                exit(0); 
            } 
        
        } else {
            wait(NULL); 
            wait(NULL); 
        } 
    } 
} 

void interpretador(string buffer[], int index){
    string pathAux = ("");

    fs::path diretorio;
    int flagExec = (verificaExec(buffer[0]));
    int flag = verificaPipe(buffer,index);

    if (flagExec == 1){
        buffer[0] = "./" + buffer[0];
    }

    if(flag == 0){    
        if(buffer[0] == "help"){
            help();
        }
        else if(buffer[0] == "cd"){
            cd(buffer, index);
        }
        else if(buffer[0] == "ls"){
            ls(buffer,index);
        }
        else if(buffer[0] == "pwd"){
            pwd();
            cout << "\n";
        }
        else if(buffer[0] == "\0");
        
        else if(buffer[0][0] == '.' && buffer[0][1] == '/'){
            //Transformar em funcao e usar-la no pipe.
            char *char_array[index+1];
            int i = 0;
            for(i = 0; i <= index; i++){
                char_array[i] = (char *)malloc(40*sizeof(char));
                strcpy(char_array[i], buffer[i].c_str());
            }
            char_array[i] = (char *)malloc(40*sizeof(char));
            char_array[i] = NULL;
            executa(char_array);

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

int takeInput(string username){
    string entrada("");
    cout << username;
    pwd();
    cout << " ─► ";
    
    getline(cin,entrada);
    if(entrada == "exit"){
        return 0;
    }
    else{
        parser(entrada);
    }
    
    return 1;
}

int main(){
    
    string entrada(""), username("");
    int status;

    username = startTerminal();
    
    do{
        status = takeInput(username);
    }while(status);

}