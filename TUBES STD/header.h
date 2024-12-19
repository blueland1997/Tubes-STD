#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

struct elmList {
    string info;
    elmList* next;
    elmList* prev;
};

typedef elmList* address;

struct List {
    address first;
    address last;
};

struct Info {
    string type;
    int position;
    string data;
    string oldData;
};

struct StackNode {
    Info info;
    StackNode* next;
};

struct Stack {
    StackNode* topNode;
};

void initStack(Stack &stack);
bool isEmpty(Stack &stack);
void push(Stack &stack, Info info);
void pop(Stack &stack);
Info top(Stack &stack);
void clearStack(Stack &stack);

address createelmList(string data);
void createList(List &L);
void InsertTeks(List &L, int posisi, string data, Stack &undoStack);
void DeleteTeks(List &L, int posisi, Stack &undoStack);
void Undo(List &L, Stack &undoStack, Stack &redoStack);
void Redo(List &L, Stack &redoStack, Stack &undoStack);
bool containsSubstring(string &str, string &key);
void FindTeks(List &L, string &key);
void ReplaceTeks(List &L, string &findStr, string &replaceStr, Stack &undoStack);
void DokumentasiFiturDasar(List &L);

#endif // HEADER_H_INCLUDED
