#include "header.h"

void initStack(Stack &stack) {
    stack.topNode = nullptr;
}

bool isEmpty(Stack &stack) {
    return stack.topNode == nullptr;
}

void push(Stack &stack, Info info) {
    StackNode* newNode = new StackNode{info, stack.topNode};
    stack.topNode = newNode;
}

void pop(Stack &stack) {
    if (isEmpty(stack)){
        return;
    }
    StackNode* temp = stack.topNode;
    stack.topNode = stack.topNode->next;
    temp->next = nullptr;
}

Info top(Stack &stack) {
    if (!isEmpty(stack)) {
        return stack.topNode->info;
    }
}

void clearStack(Stack &stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

address createelmList(string data) {
    address P = new elmList;
    P->info = data;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
}

void InsertTeks(List &L, int posisi, string data, Stack &undoStack) {
    address P = createelmList(data);

    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
        cout << "Text successfully inserted at line 1!\n";
    } else {
        if (posisi == 1) {
            P->next = L.first;
            L.first->prev = P;
            L.first = P;
            cout << "Text successfully inserted at line 1!\n";
        } else {
            address temp = L.first;
            int current = 1;

            while (temp && current < posisi - 1) {
                temp = temp->next;
                current++;
            }

            if (!temp) {
                cout << "Invalid position! Adding to the end of the document.\n";
                if (L.last) {
                    L.last->next = P;
                    P->prev = L.last;
                    L.last = P;
                } else {
                    L.first = L.last = P;
                }
                cout << "Text successfully inserted at line " << current << "!\n";
            } else {
                P->next = temp->next;
                P->prev = temp;
                if (temp->next) {
                    temp->next->prev = P;
                } else {
                    L.last = P;
                }
                temp->next = P;
                cout << "Text successfully inserted at line " << (current + 1) << "!\n";
            }
        }
    }

    push(undoStack, { "insert", posisi, data });
}

void DeleteTeks(List &L, int posisi, Stack &undoStack) {
    if (L.first == nullptr) {
        cout << "Document is empty. Cannot delete.\n";
        return;
    }

    address temp = L.first;
    int current = 1;

    while (temp && current < posisi) {
        temp = temp->next;
        current++;
    }

    if (!temp) {
        cout << "Invalid position! No text to delete at line " << posisi << ".\n";
        return;
    }

    string deletedData = temp->info;

    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        L.first = temp->next;
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        L.last = temp->prev;
    }

    temp->next = nullptr;
    temp->prev = nullptr;
    cout << "Text successfully deleted from line " << posisi << "!\n";
    push(undoStack, { "delete", posisi, deletedData });
}

void Undo(List &L, Stack &undoStack, Stack &redoStack) {
    if (isEmpty(undoStack)) {
        cout << "Nothing to undo.\n";
        return;
    }

    Info lastInfo = top(undoStack);
    pop(undoStack);

    if (lastInfo.type == "insert") {
        DeleteTeks(L, lastInfo.position, redoStack);
    } else if (lastInfo.type == "delete") {
        InsertTeks(L, lastInfo.position, lastInfo.data, undoStack);
    } else if (lastInfo.type == "replace") {
        string originalText = lastInfo.oldData;
        string findStr = lastInfo.data;
        ReplaceTeks(L, findStr, originalText, redoStack);
    }

    push(redoStack, lastInfo);
}

void Redo(List &L, Stack &redoStack, Stack &undoStack) {
    if (isEmpty(redoStack)) {
        cout << "Nothing to redo.\n";
        return;
    }

    Info lastInfo = top(redoStack);
    pop(redoStack);

    if (lastInfo.type == "insert") {
        InsertTeks(L, lastInfo.position, lastInfo.data, undoStack);
    } else if (lastInfo.type == "delete") {
        DeleteTeks(L, lastInfo.position, undoStack);
    } else if (lastInfo.type == "replace") {
        string newText = lastInfo.data;
        string findStr = lastInfo.oldData;
        ReplaceTeks(L, findStr, newText, undoStack);
    }
}

bool containsSubstring(string &str, string &key) {
    int strLen = str.length();
    int keyLen = key.length();

    for (int i = 0; i <= strLen - keyLen; i++) {
        int j;
        for (j = 0; j < keyLen; j++) {
            if (str[i + j] != key[j]) {
                break;
            }
        }
        if (j == keyLen) {
            return true;
        }
    }
    return false;
}

void FindTeks(List &L, string &key) {
    address temp = L.first;
    bool found = false;
    int line = 1;

    while (temp) {
        if (containsSubstring(temp->info, key)) {
            cout << "Found at line " << line << ": " << temp->info << endl;
            found = true;
        }
        temp = temp->next;
        line++;
    }

    if (!found) {
        cout << "No text found containing: " << key << endl;
    }
}

void ReplaceTeks(List &L, string &findStr, string &replaceStr, Stack &undoStack) {
    address temp = L.first;
    bool replaced = false;

    while (temp) {
        string originalLine = temp->info;
        string newLine;
        int findStrLength = findStr.length();
        int originalLineLength = originalLine.length();
        int i = 0;

        //a k u s u k a p i s a n g = 13
        //suka -> benci
        //i = 12
        while (i < originalLineLength) {
            bool match = true;

            //findStrLength = 4
            //originalLineLength - findStrLength = 9
            if (i <= originalLineLength - findStrLength) {
                for (int j = 0; j < findStrLength; ++j) {
                    //j = 0
                    //originalLine[i + j] = g
                    //findStr[j] = s
                    if (originalLine[i + j] != findStr[j]) {
                        match = false;
                        break;
                    }
                }
            } else {
                match = false;
            }

            //newline = akubencipisang
            if (match) {
                for (char c : replaceStr) {
                    newLine += c;
                }
                replaced = true;
                i += findStrLength;
            } else {
                newLine += originalLine[i];
                i++;
            }
        }

        if (replaced) {
            temp->info = newLine;
        }

        temp = temp->next;
    }

    if (replaced) {
        cout << "All occurrences of '" << findStr << "' have been replaced with '" << replaceStr << "'.\n";
        push(undoStack, {"replace", 0, replaceStr, findStr});
    } else {
        cout << "No occurrences of '" << findStr << "' found to replace.\n";
    }
}

void DokumentasiFiturDasar(List &L) {
    if (!L.first) {
        cout << "Document is empty.\n";
        return;
    }
    address temp = L.first;
    int posisi = 1;
    while (temp) {
        cout << posisi++ << ": " << temp->info << endl;
        temp = temp->next;
    }
}
