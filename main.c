#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ARR_SIZE(a) (sizeof(a)/ sizeof(*a))


// Pode representar Receptor ou Emissor
typedef struct Actor {
    int id;
    char name[15];
} Actor;

// Mensagens enviadas por um Emissor
typedef struct Message {
    int id_emissor;
    char content[50];
    struct Message* next;
} Message;

// Lista de mensagem aguardando o Receptor
typedef struct Queue {
    int id_receptor;
    struct Message* messages;
    struct Queue* next;
} Queue;


// TODO: fazer as implementacoes dos seguintes metodos:
void insertActor();
void removeActor();
void listActors();


/* TODO:
 *  Aqui a ideia seria retornar uma nova lista
 *  com cada elemento apontando para uma queue
 *  pertencente ao id do receptor da lista.
 *
 */
Queue* getQueueByReceptors(int id_receptor[], Queue* queues) {

}

void enqueue(Message *newMessage, Queue queue) {
    Message* aux = malloc(sizeof(Message));
    Message** messages = (Message **) queue.messages;
    if(*messages == NULL) {
        *messages = newMessage;
    } else {
        aux = *messages;
        while(aux->next)
            aux = aux->next;
        aux->next = newMessage;
    }
}
/*TODO:
 *  Validar se o metodo esta funcional.
 */
void sendMessage(Queue** queue, Actor emissor, char content[]) {
    Message* message = malloc(sizeof(Message));
    Queue* aux = malloc(sizeof(Queue));
    if(message) {
        message->id_emissor = emissor.id;
        strcpy(message->content, content);

        aux = *queue;
        while(aux) {
            enqueue(message, **queue);
            aux = aux->next;
        }
    } else {
        printf("Nao foi possivel alocar memoria da mensagem.");
    }
}




void removeMessage();

void listMessagesByReceptor();
//------------------------------------------------------
int getArraySize(int arr[]) {
    int len = sizeof(arr)/sizeof(int);
    return len;
}

int main() {
    Actor* emissores = NULL;
    Actor* receptores = NULL;
    Queue* message_queues = NULL;


    return 0;
}