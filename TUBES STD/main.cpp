#include <iostream>
#include "header.h"
#include <sstream>

using namespace std;

int main() {
    List editor;
    Stack undoStack, redoStack;
    initStack(undoStack);
    initStack(redoStack);
    createList(editor);
    string command;

    cout << "Welcome to the Text Editor!\n";
    cout << "Type 'help' for a list of commands.\n";

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, command);
        stringstream ss(command);
        string action;
        ss >> action;

        int actionCode = 0;

        if (action == "insert") {
            actionCode = 1;
        } else if (action == "delete") {
            actionCode = 2;
        } else if (action == "undo") {
            actionCode = 3;
        } else if (action == "redo") {
            actionCode = 4;
        } else if (action == "find") {
            actionCode = 5;
        } else if (action == "replace") {
            actionCode = 6;
        } else if (action == "show") {
            actionCode = 7;
        } else if (action == "help") {
            actionCode = 8;
        } else if (action == "exit") {
            actionCode = 9;
        }

        switch (actionCode) {
            case 1: { // insert
                int line;
                string text;
                if (!(ss >> line) || line < 1) {
                    cout << "Invalid line number. Please enter a valid command (line number must be 1 or greater).\n";
                    continue;
                }
                getline(ss, text);
                if (!text.empty() && text[0] == ' ') {
                    text.erase(0, 1);
                }
                InsertTeks(editor, line, text, undoStack);
                DokumentasiFiturDasar(editor);
                break;
            }
            case 2: { // delete
                int line;
                if (!(ss >> line) || line < 1) {
                    cout << "Invalid line number. Please enter a valid command (line number must be 1 or greater).\n";
                    continue;
                }
                DeleteTeks(editor, line, undoStack);
                DokumentasiFiturDasar(editor);
                break;
            }
            case 3: // undo
                Undo(editor, undoStack, redoStack);
                DokumentasiFiturDasar(editor);
                break;
            case 4: // redo
                Redo(editor, redoStack, undoStack);
                DokumentasiFiturDasar(editor);
                break;
            case 5: { // find
                string key;
                getline(ss, key);
                if (!key.empty() && key[0] == ' ') {
                    key.erase(0, 1);
                }
                FindTeks(editor, key);
                break;
            }
            case 6: { // replace
                string findStr, replaceStr;
                cout << "Enter the string to find: ";
                getline(cin, findStr);
                cout << "Enter the string to replace with: ";
                getline(cin, replaceStr);
                ReplaceTeks(editor, findStr, replaceStr, undoStack);
                DokumentasiFiturDasar(editor);
                break;
            }
            case 7: // show
                DokumentasiFiturDasar(editor);
                break;
            case 8: // help
                cout << "Available commands:\n";
                cout << "insert [line] [string] : to input a new line\n";
                cout << "delete [line] : to delete a line\n";
                cout << "undo : to undo the last action\n";
                cout << "redo : to redo the last undone action\n";
                cout << "find [string] : to find lines containing the specified string\n";
                cout << "replace : to replace all occurrences of a string\n";
                cout << "show : to display the current document content\n";
                cout << "exit : to exit the program\n";
                break;
            case 9: // exit
                cout << "Exiting the program.\n";
                clearStack(undoStack);
                clearStack(redoStack);
                return 0;
            default:
                cout << "Unknown command. Type 'help' for a list of commands.\n";
                break;
        }
    }

    return 0;
}
