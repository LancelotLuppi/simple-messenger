#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

const int INDEX_SENDER = 0;
const int INDEX_RECEIVER = 1;
int SEQUENTIAL_ID[2];

// Pode representar Receptor ou Emissor
typedef struct Actors {
    int id;
    char name[15];
    struct Actors *next;
} Actors;

// Mensagens enviadas por um Emissor
typedef struct Message {
    int id_emissor;
    char content[50];
    struct Message *next;
} Message;

// Lista de mensagem aguardando o Receptor
typedef struct Queue {
    int id_receptor;
    struct Message **messages;
    struct Queue *next;
} Queue;

void operationError() {
    fprintf(stderr, "Não foi possível realizar a operação.\n");
}

void memoryAllocationError() {
    fprintf(stderr, "Não foi possível alocar memória com sucesso.\n");
}

void listActors(Actors *head) {
    Actors *aux = head;
    if (aux) {
        while (aux != NULL) {
            printf("\nID: %d\n", aux->id);
            printf("Nome: %s\n", aux->name);
            printf("----------- // -----------\n");
            aux = aux->next;
        }
        printf("\n");
    } else {
        printf("\nNenhum registro foi encontrado.\n");
    }
};

void insertActor(Actors **head, int operation) {

    char name[15];
    Actors *newActor = (Actors *) malloc(sizeof(Actors));
    Actors *aux;
    newActor->next = NULL;

    printf("\nDigite o nome:\n");
    if (scanf("%14s", name) != 1) {
        return operationError();
    };
    newActor->id = SEQUENTIAL_ID[operation];
    strcpy(newActor->name, name);

    if (*head == NULL) {
        *head = newActor;
    } else {
        aux = *head;
        while(aux->next)
            aux = aux->next;
        aux->next = newActor;
    }
    SEQUENTIAL_ID[operation]++;
    printf("\nInserido!\n\n");
}

void removeActor(Actors **head) {
    listActors(*head);
    int id;
    printf("\nDigite o Id (Inteiro positivo):\n");
    // If there is less than or more than one successful scan it should error
    if (scanf("%d", &id) != 1) {
        return operationError();
    };

    Actors *aux = *head;

    if (aux->id == id) {
        *head = aux->next;
    } else {
        Actors *prev;
        while (aux->id != id && aux->next) {
            prev = aux;
            aux = aux->next;
        }
        prev->next = aux->next;
    }
    printf("\nRemovido!\n");
    free(aux);
};

void enqueue(Message *newMessage, Queue *queue) {
    Message *aux;
    Message **messages = queue->messages;
    if (*messages == NULL) {
        printf("fila de mensagem null\n");
        *messages = newMessage;
    } else {
        aux = *messages;
        printf("fila de mensagem nao null\n");
        while (aux->next) {
            aux = aux->next;
        }

        aux->next = newMessage;
    }
}

void dequeue(Queue *queue) {
    Message **messages = (Message **) queue->messages;
    Message *aux = *messages;

    if (*messages == NULL) {
        printf("\nA fila já está vazia!\n");
    } else {
        *messages = aux->next;
        free(aux);
    }
}

char *inputMessage() {
    char *message = (char *) malloc(sizeof(char) * 50);

    printf("\nDigite a mensagem a ser enviada:\n");
    scanf("%49s", message);
    printf("\n");
    return message;
}

Actors *selectActor(Actors *head, int operation) {
    int actorId = 0;
    Actors *aux = head;

    listActors(head);
    scanf("%d", &actorId);
    while (aux->next && aux->id != actorId) {
        printf("laco iterado\n");
        aux = aux->next;
    }
    return aux;
}

void sendMessage(Queue **queue, Actors *emissor, int id_receptor,
                 char *content) {
    Message *message = malloc(sizeof(Message));
    Queue *aux, *newNode = malloc(sizeof(Queue));

//    if(message) {
//        message->id_emissor = emissor->id;
//        strcpy(message->content, content);
//        message->next = NULL;
//        if(*queue == NULL) {
//            if(newNode != NULL) {
//                newNode->id_receptor = id_receptor;
//                newNode->messages = NULL;
//                newNode->next = NULL;
//                *queue = newNode;
//                enqueue(message, queue);
//            }
//        } else {
//            aux = *queue;
//            while (aux) {
//                if(aux->id_receptor == id_receptor)
//                    enqueue(message, aux);
//                aux = aux->next;
//            }
//        }
//    }

    if(message && newNode) {
        message->id_emissor = emissor->id;
        strcpy(message->content, content);
        message->next = NULL;
        newNode->messages = message;
        newNode->id_receptor = id_receptor;
        newNode->next = NULL;
        if(*queue == NULL) {
            *queue = newNode;
        } else {
            aux = *queue;
            while (aux) {
                if(aux->id_receptor == id_receptor)
                    enqueue(message, aux);
                aux = aux->next;
            }
            aux = *queue;
            while(aux->next)
                aux = aux->next;
            aux->next = newNode;
        }
    } else
        memoryAllocationError();
//    if (message != NULL && aux != NULL) {
//        message->id_emissor = emissor->id;
//        strcpy(message->content, content);
//        aux = *queue;
//        // erro
//        while (aux->next) {
//            if (aux->id_receptor == id_receptor) {
//                enqueue(message, aux);
//            }
//            aux = aux->next;
//        }
//    } else {
//        memoryAllocationError();
//    }
}

void listMessagesByReceptor(Queue *queue, int id_receptor) {
//    Queue *queueAux = queue;
//    if(queue) {
//        while(queue) {
//            if(queue->id_receptor == id_receptor) {
//                printf("fila encontrada");
//                while (queue->messages) {
//                    printf("mensagem encontrada");
//                    printf("\nMensagem: ");
//                    M
//                    printf("%s\n", queue->(*messages)->content);
//                    queue->messages = queue->messages->next;
//                }
//            }
//            queue = queue->next;
//        }
//    } else
//        printf("Nenhuma mensagem registrada\n");
//    if (queueAux) {
//        do {
//            if (queueAux->id_receptor == id_receptor) {
//                Message **messages = (Message **) queueAux->messages;
//                Message *aux = *messages;
//
//                if (messages) {
//                    do {
//                        printf("\nMensagem:\n");
//                        printf("%s\n", aux->content);
//                        aux = aux->next;
//
//                    } while (aux->next);
//                }
//            }
//        } while (queueAux->next);
//    } else {
//        printf("\nNenhuma mensagem registrada para esse receptor\n");
//    }
};

//------------------------------------------------------
// CLI functions
//------------------------------------------------------
void showInterface(Actors **sender_head, Actors **receiver_head,
                   Queue **messages) {
    int userInput = -1;

    // TODO REVISAR OPERACOES POSSIVEIS
    while (userInput != 0) {
        printf("----------------- / * / -----------------\n");
        printf("----------- SIMPLE MESSENGER -----------\n");
        printf("----------------- / * / -----------------\n");
        printf("\n-------------- OPERACOES --------------\n");
        printf("  1) Incluir emissor na lista de emissores \n");
        printf("  2) Remover emissor da lista de emissores \n");
        printf("  3) Consultar emissores\n");
        printf("  4) Incluir receptor \n");
        printf("  5) Remover receptor (AS MENSAGENS TAMBEM SERAO REMOVIDAS)\n");
        printf("  6) Consultar receptores\n");
        printf("  7) Enviar mensagem: emissor adiciona a mensagem para a fila de um (ou mais) receptor\n");
        printf("  8) Retirar mensagem: um receptor desenfileira uma "
               "mensagem (apresentar mensagem de erro se a fila está vazia) \n ");
        printf("  9) Consultar fila de mensagens: exibe a fila de mensagens de um "
               "receptor \n");
        printf("  0) Fechar o programa.\n");
        // TODO AVALIAR FUNCOES POSSIVEIS
        //  printf("  10) Outras operações (a seu critério), como: exibir receptores
        //  "
        //         "com fila vazia, exibir receptores com mais mensagens na fila, "
        //         "exibir total de mensagens enviadas por um emissor, exibir total
        //         de " "mensagens recebidas por um receptor \n");

        scanf("%d", &userInput);

        switch (userInput) {
            case 0:
                printf("\n\n\n\nEncerrando... \n\n\n\n");
                break;
            case 1:
                printf("\n\n\n\nIncluir emissor na lista de emissores \n\n\n\n");
                insertActor(sender_head, INDEX_SENDER);
                break;
            case 2:
                printf("\n\n\n\nRemover emissor da lista de emissores \n\n\n\n");
                removeActor(sender_head);
                break;
            case 3:
                printf("\n\n\n\nListar emissores \n\n\n\n");
                listActors(*sender_head);
                break;
            case 4:
                printf("\n\n\n\nIncluir receptor na lista de receptores\n\n\n\n");
                insertActor(receiver_head, INDEX_RECEIVER);
                break;
            case 5:
                printf("\n\n\n\nRemover receptor da lista de receptores\n\n\n\n");
                removeActor(receiver_head);
                break;
            case 6:
                printf("\n\n\n\nListar receptores\n\n\n\n");
                listActors(*receiver_head);
                break;
            case 7:
                printf("\n\n\n\nEnviar mensagem\n\n\n\n");

                printf("\nDigite o id do emissor desejado:\n");
                Actors *sender = selectActor(*sender_head, INDEX_SENDER);
                printf("\nDigite o id do receptor desejado:\n");
                int receiver_id = selectActor(*receiver_head, INDEX_RECEIVER)->id;
                sendMessage(messages, sender, receiver_id, inputMessage());
                break;
            case 8:
                printf("\n\n\n\nConcluir/remover mensagem\n\n\n\n");
                dequeue(*messages);
                break;
            case 9:
                printf("\n\n\n\nConsultar mensagens\n\n\n\n");
                printf("\nDigite o id do receptor desejado:\n");
                listMessagesByReceptor(*messages, selectActor(*receiver_head, INDEX_RECEIVER)->id);
                break;

            default:
                printf("\n\n\n\nNão foi possível compreender o comando! \n\n\n\n");
                break;
        }
    };
}
//------------------------------------------------------

int main() {
    SEQUENTIAL_ID[INDEX_SENDER] = 0;
    SEQUENTIAL_ID[INDEX_RECEIVER] = 0;
    Actors *emissores = NULL;
    Actors *receptores = NULL;
    Queue *message_queues = NULL;

    showInterface(&emissores, &receptores, &message_queues);

    return 0;
}
