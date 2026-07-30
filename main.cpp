#include <iostream>
#include <string>
using namespace std;

int main() {
    string commands[9]={"help", "dir", "pwd", "cd", "mkdir", "rmdir", "create", "del", "exit"};
    cout<<"welcome to my shell"<<endl;
    string a;
    while(true){
        cout<<"VirtualShell> ";
        getline(cin, a);
        if(a=="exit"){
            break;
        }
        if(a=="help"){
            cout<<"available commands are: "<<endl;
            for(int i=0; i<9; i++){
                cout<<commands[i]<<endl;
            }
            continue;

        }
        bool found=false;
        for(int i=0; i<9; i++){
            if(a==commands[i]){
                found=true;
                break;
            }
        }
        if(found==false){
            cout<<"command not found"<<endl;
            continue;
        }
        cout<<"you entered: "<<a<<endl;
    }
    return 0;
}

