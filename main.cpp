//for runnig this code write g++ main.cpp -o main
// and then write ./main to run the programm sucessfully 



#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <direct.h> // For _getcwd and _chdir

using namespace std;

// Global vector to store command history
vector<string> commandHistory;

// Helper to get current working directory as a string
string getCurrentDir() {
    char buffer[FILENAME_MAX];
    if (_getcwd(buffer, sizeof(buffer)) != nullptr) {
        return string(buffer);
    }
    return "";
}

// --- Command Functions ---

void showHelp() {
    cout << "Available commands: help, dir, pwd, cd, mkdir, rmdir, create, del, history, clear, exit" << endl;
}

void handlePwd() {
    cout << getCurrentDir() << endl;
}

void handleCd(const vector<string>& args) {
    if (args.empty()) {
        cout << "cd: expected argument" << endl;
    } else {
        if (_chdir(args[0].c_str()) != 0) {
            cout << "cd: No such file or directory" << endl;
        }
    }
}

void handleDir() {
    WIN32_FIND_DATA findFileData;
    // Search for all files/folders in the current directory
    HANDLE hFind = FindFirstFile("*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "dir: failed to open directory" << endl;
        return;
    } 
    
    do {
        string name = findFileData.cFileName;
        // Skip current and parent directory markers
        if (name == "." || name == "..") continue;

        // Check if attribute is a directory or file
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            cout << "[DIR]  " << name << endl;
        } else {
            cout << "[FILE] " << name << endl;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);
    
    FindClose(hFind);
}

void handleMkdir(const vector<string>& args) {
    if (args.empty()) {
        cout << "mkdir: missing operand" << endl;
    } else {
        if (_mkdir(args[0].c_str()) == 0) {
            cout << "Directory created successfully." << endl;
        } else {
            cout << "mkdir: failed to create directory" << endl;
        }
    }
}

void handleRmdir(const vector<string>& args) {
    if (args.empty()) {
        cout << "rmdir: missing operand" << endl;
    } else {
        if (_rmdir(args[0].c_str()) == 0) {
            cout << "Directory removed successfully." << endl;
        } else {
            cout << "rmdir: failed to remove (directory must be empty)" << endl;
        }
    }
}

void handleCreate(const vector<string>& args) {
    if (args.empty()) {
        cout << "create: missing file name" << endl;
    } else {
        ofstream outfile(args[0]);
        if (outfile) {
            cout << "File created successfully." << endl;
        } else {
            cout << "create: failed to create file" << endl;
        }
    }
}

void handleDel(const vector<string>& args) {
    if (args.empty()) {
        cout << "del: missing file name" << endl;
    } else {
        if (remove(args[0].c_str()) == 0) {
            cout << "File deleted successfully." << endl;
        } else {
            cout << "del: file not found or cannot be deleted" << endl;
        }
    }
}

void handleHistory() {
    cout << "--- Command History ---" << endl;
    for (size_t i = 0; i < commandHistory.size(); ++i) {
        cout << i + 1 << "  " << commandHistory[i] << endl;
    }
}

void handleClear() {
    system("cls");
}

// --- Main Loop ---

int main() {
    cout << "Welcome to my Virtual Shell!" << endl;
    string input;

    while (true) {
        string fullPath = getCurrentDir();
        // Extract just the folder name for a clean prompt
        size_t lastSlash = fullPath.find_last_of("\\");
        string currentFolder = (lastSlash == string::npos) ? fullPath : fullPath.substr(lastSlash + 1);
        if (currentFolder.empty()) currentFolder = fullPath;

        cout << "VirtualShell:" << currentFolder << "> ";
        getline(cin, input);

        if (input.empty()) continue;

        commandHistory.push_back(input);

        stringstream ss(input);
        string cmd;
        vector<string> args;
        
        ss >> cmd;
        string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }

        if (cmd == "exit") {
            break;
        } 
        else if (cmd == "help") {
            showHelp();
        } 
        else if (cmd == "pwd") {
            handlePwd();
        } 
        else if (cmd == "cd") {
            handleCd(args);
        } 
        else if (cmd == "dir") {
            handleDir();
        } 
        else if (cmd == "mkdir") {
            handleMkdir(args);
        } 
        else if (cmd == "rmdir") {
            handleRmdir(args);
        } 
        else if (cmd == "create") {
            handleCreate(args);
        } 
        else if (cmd == "del") {
            handleDel(args);
        }
        else if (cmd == "history") {
            handleHistory();
        }
        else if (cmd == "clear") {
            handleClear();
        }
        else {
            cout << "Command not found: " << cmd << endl;
        }
    }
    return 0;
}