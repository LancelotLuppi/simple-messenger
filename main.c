#include <stdio.h>
#include <stdlib.h>


// Pode representar Receptor ou Emissor
typedef struct Actor {
    int id;
    char[15] name;
} Actor;

// Mensagens enviadas por um Emissor
typedef struct Message {
    int id_emissor;
    char[50] content;
} Message;

// Lista de mensagem aguardando o Receptor
typedef struct Queue {
    int id_receptor;
    struct Message* messages;
}

int main() {
    return 0;
}