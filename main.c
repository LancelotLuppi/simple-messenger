#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    char[15] name;
    struct Node* next;
} Node;

typedef struct MessageQ {
    char[50] message;
    struct MessageQ* next;
} MessageQ;

int main() {
    return 0;
}