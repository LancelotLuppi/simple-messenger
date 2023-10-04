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


// TODO: fazer as implementacoes dos seguintes metodos:
void insertActor();
void removeActor();
void listActors();

void sendMessage();
void removeMessage();

void listMessagesByReceptor();
//------------------------------------------------------

int main() {
    Actor* emissores = NULL;
    Actor* receptores = NULL;
    Queue* message_queue = NULL;


    return 0;
}