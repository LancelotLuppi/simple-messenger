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
  int interactions;
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
  struct Message *messages;
  struct Queue *next;
} Queue;

void emptyQueueError() { fprintf(stderr, "A fila já está vazia.\n"); }

void noRegisterError() {
  fprintf(stderr, "\nNenhum registro foi encontrado.\n");
}

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
    return noRegisterError();
  }
};

void insertActor(Actors **head, int operation) {
  char name[15];
  Actors *newActor = (Actors *)malloc(sizeof(Actors));
  Actors *aux;
  newActor->next = NULL;
  newActor->interactions = 0;

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
    while (aux->next)
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

int getActorInteractions(Actors *head, int actorId) {
  Actors *aux = head;
  if (aux->id != actorId) {
    if (aux->next) {
      while (aux->next && aux->id != actorId)
        aux = aux->next;
    } else {
      noRegisterError();
    }
  }
  return aux->interactions;
}

void enqueue(Message *newMessage, Message **messages) {
  Message *aux;
  newMessage->next = NULL;
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

void dequeueMessage(Message **message) {
  if (!message) {
    return emptyQueueError();
  }
  Message *aux = *message;

  if (!aux->next) {
    *message = NULL;
  } else {
    *message = aux->next;
  }
  free(aux);
}

void dequeue(Queue *queue, int receiver_id) {
  Queue *auxQueue = queue;

  if (auxQueue == NULL) {
    return emptyQueueError();
  }

  if (auxQueue->id_receptor == receiver_id) {
    dequeueMessage(&auxQueue->messages);
  } else {
    while (auxQueue->id_receptor != receiver_id && auxQueue->next) {
      auxQueue = auxQueue->next;
    }
    if (!auxQueue->messages) {
      return emptyQueueError();
    }
    dequeueMessage(&auxQueue->messages);
  }

  Message **messages = (Message **)queue->messages;
}

char *inputMessage() {
  char *message = (char *)malloc(sizeof(char) * 50);

  printf("\nDigite a mensagem a ser enviada:\n");
  scanf("%49s", message);
  printf("\n");
  return message;
}

Actors *selectActor(Actors *head) {
  int actorId = 0;
  Actors *aux = head;

  if (!aux) {
    noRegisterError();
  } else {
    listActors(head);
    if (scanf("%d", &actorId)) {
      while (aux->next && aux->id != actorId) {
        aux = aux->next;
      }
    }
  }

  return aux;
}

void sendMessage(Queue **queue, Actors *emissor, int id_receptor,
                 char *content) {
  Message *message = malloc(sizeof(Message));
  Queue *aux, *newNode = malloc(sizeof(Queue));

  if (message && newNode) {
    message->id_emissor = emissor->id;
    strcpy(message->content, content);
    message->next = NULL;
    newNode->id_receptor = id_receptor;
    newNode->next = NULL;
    newNode->messages = NULL;
    if (*queue == NULL) {
      *queue = newNode;
      aux = *queue;
      Message **headerMensagens = &(aux->messages);
      enqueue(message, headerMensagens);
    } else {
      aux = *queue;
      int find = 0;
      if (aux->id_receptor == id_receptor) {
        find = 1;
        Message **headerMensagens = &(aux->messages);
        enqueue(message, headerMensagens);
      }
      while (aux->next && aux->next->id_receptor != id_receptor) {
        aux = aux->next;
      }
      if (find == 0) {
        aux->next = newNode;
        Message **headerMensagens = &(aux->next->messages);
        enqueue(message, headerMensagens);
      }
    }
  } else
    memoryAllocationError();
}

void listMessagesByReceptor(Queue *queue, int id_receptor) {
  if (queue) {
    while (queue) {
      if (queue->id_receptor == id_receptor) {
        Message *list = queue->messages;
        while (list) {
          printf("Mensagem: ");
          printf("%s\n", list->content);
          list = list->next;
        }
      }
      queue = queue->next;
    }
  } else
    printf("Nenhuma mensagem registrada\n");
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
    printf("  7) Enviar mensagem: emissor adiciona a mensagem para a fila de "
           "um (ou mais) receptor\n");
    printf("  8) Retirar mensagem: um receptor desenfileira uma "
           "mensagem (apresentar mensagem de erro se a fila está vazia) \n ");
    printf("  9) Consultar fila de mensagens: exibe a fila de mensagens de um "
           "receptor \n");
    printf("  10) Consultar total de mensagens enviadas por um emissor \n");
    printf("  11) Consultar total de mensagens recebidas por um receptor \n");
    printf("  0) Fechar o programa.\n");
    // TODO AVALIAR FUNCOES POSSIVEIS
    //  printf("  10) Outras operações (a seu critério), como: exibir receptores
    //  "
    //         "com fila vazia, exibir receptores com mais mensagens na fila, "
    //         ", exibir total
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
    case 7: {
      printf("\n\n\n\nEnviar mensagem\n\n\n\n");

      printf("\nDigite o id do emissor desejado:\n");
      Actors *sender = selectActor(*sender_head);
      printf("\nDigite o id do receptor desejado:\n");
      Actors *receiver = selectActor(*receiver_head);
      if (sender && receiver) {
        sender->interactions++;
        receiver->interactions++;
        sendMessage(messages, sender, receiver->id, inputMessage());
      }
      break;
    }
    case 8: {
      printf("\n\n\n\nConcluir/remover mensagem\n\n\n\n");

      printf("\nDigite o id do receptor desejado:\n");
      int receiver_id = selectActor(*receiver_head)->id;
      dequeue(*messages, receiver_id);
      break;
    }
    case 9:
      printf("\n\n\n\nConsultar mensagens\n\n\n\n");
      printf("\nDigite o id do receptor desejado:\n");
      listMessagesByReceptor(*messages, selectActor(*receiver_head)->id);
      break;

    case 10: {
      printf("\n\n\n\nConsultar envios de um emissor\n\n\n\n");
      printf("\nDigite o id do emissor desejado:\n");
      Actors *actor = selectActor(*sender_head);
      if (actor) {
        int emissions = getActorInteractions(*sender_head, actor->id);
        if (emissions == 0) {
          printf("\nEsse emissor nunca enviou uma mensagem!\n");
        } else if (emissions == 1) {
          printf("\nEsse emissor já enviou %d mensagem!\n", emissions);
        } else {
          printf("\nEsse receptor já enviou %d mensagens!\n", emissions);
        }
      }
      break;
    }

    case 11: {
      printf("\n\n\n\nConsultar número de mensagens recebidas de um "
             "receptor\n\n\n\n");
      printf("\nDigite o id do receptor desejado:\n");
      Actors *actor = selectActor(*receiver_head);
      if (actor) {
        int receptions = getActorInteractions(*receiver_head, actor->id);
        if (receptions == 0) {
          printf("\nEsse receptor nunca recebeu uma mensagem!\n");
        } else if (receptions == 1) {
          printf("\nEsse receptor já recebeu %d mensagem!\n", receptions);
        } else {
          printf("\nEsse receptor já recebeu %d mensagens!\n", receptions);
        }
      }
      break;
    }

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
