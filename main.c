#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

// Tempo de espera de 1 segundo para o usuário ler a mensagem da interface
int SLEEP_TIME = 1;

#define ARR_SIZE(a) (sizeof(a) / sizeof(*a))

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
  struct Message *messages;
  struct Queue *next;
} Queue;

void operationError() {
  printf("\nERROR: Não foi possível realizar a operação.\n");
  return;
}
// TODO: fazer as implementacoes dos seguintes metodos:
void insertActor(Actors *head) {
  printf("\nDigite o Id (Inteiro positivo):\n");
  int id;
  char name[15];

  // If there is less than or more than one successful scan it should error
  if (scanf("%d", &id) != 1) {
    return operationError();
  };
  printf("\nDigite o nome:\n");
  if (scanf("%14s", name) != 1) {
    return operationError();
  };
  Actors *newActor = malloc(sizeof(Actors));
  newActor->id = id;
  strcpy(newActor->name, name);
  newActor->next = NULL;

  Actors *aux = head;

  while (aux->next) {
    if (aux->id == newActor->id) {
      printf("\nERROR: Esse ator já existe!\n");
      return;
    }
    aux = aux->next;
  }

  aux->next = newActor;
}

void removeActor(Actors *head) {
  int id;
  printf("\nDigite o Id (Inteiro positivo):\n");
  // If there is less than or more than one successful scan it should error
  if (scanf("%d", &id) != 1) {
    return operationError();
  };

  Actors *aux = head;

  if (aux->id == id) {
    head = aux->next;
  } else {
    Actors *prev;
    while (aux->id != id && aux->next) {
      prev = aux;
      aux = aux->next;
    }
    prev->next = aux->next;
  }
  if (aux) {
    printf("\nRemovendo...\n");
    free(aux);
  } else {
    printf("\nID não encontrado.n");
  }
};

void listActors(Actors *head) {
  Actors *aux = head;
  if (aux) {
    do {
      printf("\nID: %d\n", aux->id);
      printf("Nome: %s\n", aux->name);
      aux = aux->next;
    } while (aux->next);
  } else {
    printf("\nNenhum registro foi encontrado.\n");
  }
};

void enqueue(Message *newMessage, Queue *queue) {
  Message *aux;
  Message **messages = (Message **)queue->messages;
  if (*messages == NULL) {
    *messages = newMessage;
  } else {
    aux = *messages;
    while (aux->next)
      aux = aux->next;
    aux->next = newMessage;
  }
}
/*TODO:
 *  Validar se o metodo esta funcional.
 */
void sendMessage(Queue **queue, Actors emissor, int id_receptor,
                 char content[]) {
  Message *message = malloc(sizeof(Message));
  Queue *aux = malloc(sizeof(Queue));
  if (message && aux) {
    message->id_emissor = emissor.id;
    strcpy(message->content, content);

    aux = *queue;
    while (aux->next) {
      if (aux->id_receptor == id_receptor) {
        enqueue(message, aux);
      }
      aux = aux->next;
    }
  } else {
    printf("Nao foi possivel alocar memoria da mensagem.");
  }
}

void removeMessage();

void listMessagesByReceptor();

//------------------------------------------------------
// CLI  functions
//------------------------------------------------------
void showInterface(Actors *sender_head, Actors *receiver_head,
                   Queue *messages) {
  int userInput = -1;

  // TODO REVISAR OPERACOES POSSIVEIS
  while (userInput != 0) {
    printf("----------------- / ~ / -----------------\n");
    printf("----------- SIMPLE MESSENGER -----------\n");
    printf("----------------- / ~ / -----------------\n");
    printf("\n-------------- OPERAÇÕES --------------\n");
    printf("  1) Incluir emissor na lista de emissores \n");
    printf("  2) Remover emissor da lista de emissores \n");
    printf("  3) Consultar emissores: escrever na tela os emissores "
           "cadastrados\n");
    printf("  4) Incluir receptor na lista de receptores \n");
    printf("  5) Remover receptor da lista de receptores: quando o receptor é "
           "removido, sua fila de mensagens também é removida \n");
    printf("  6) Consultar receptores: escrever na tela os receptores "
           "cadastrados \n");
    printf("  7) Enviar mensagem: um receptor cadastrado escreve a mensagem, e "
           "define quais são os receptores (pelo menos um receptor). A "
           "mensagem é enfileirada na fila de cada receptor. \n");
    printf("  8) Retirar mensagem: um receptor cadastrado desenfileira uma "
           "mensagem (apresentar mensagem de erro se a fila está vazia) \n ");
    printf("  9) Consultar fila de mensagens: exibe a fila de mensagens de um "
           "receptor \n");
    printf("  0) Fechar o programa.\n");
    // printf("  10) Outras operações (a seu critério), como: exibir receptores
    // "
    //        "com fila vazia, exibir receptores com mais mensagens na fila, "
    //        "exibir total de mensagens enviadas por um emissor, exibir total
    //        de " "mensagens recebidas por um receptor \n");

    scanf("%d", &userInput);

    // TODO ADICIONAR METODOS PARA CADA INPUT DO USUARIO
    switch (userInput) {
    case 0:
      printf("\n\n\n\nEncerrando... \n\n\n\n");
      sleep(SLEEP_TIME);
      break;
    case 1:
      printf("\n\n\n\nIncluir emissor na lista de emissores \n\n\n\n");
      sleep(SLEEP_TIME);
      insertActor(sender_head);
      break;
    case 2:
      printf("\n\n\n\nRemover emissor da lista de emissores \n\n\n\n");
      sleep(SLEEP_TIME);
      removeActor(sender_head);
      break;
    case 3:
      printf("\n\n\n\nListar emissores \n\n\n\n");
      sleep(SLEEP_TIME);
      listActors(sender_head);
      break;
    case 4:
      printf("\n\n\n\nIncluir receptor na lista de receptores\n\n\n\n");
      sleep(SLEEP_TIME);
      insertActor(receiver_head);
      break;
    case 5:
      printf("\n\n\n\nRemover receptor da lista de receptores\n\n\n\n");
      sleep(SLEEP_TIME);
      removeActor(receiver_head);
      break;
    case 6:
      printf("\n\n\n\nListar receptores\n\n\n\n");
      sleep(SLEEP_TIME);
      listActors(receiver_head);
      break;

    default:
      printf("\n\n\n\nNão foi possível compreender o comando! \n\n\n\n");
      sleep(SLEEP_TIME);
      break;
    }
  };
}
//------------------------------------------------------

int main() {
  Actors *emissores = NULL;
  Actors *receptores = NULL;
  Queue *message_queues = NULL;

  showInterface(emissores, receptores, message_queues);

  return 0;
}
