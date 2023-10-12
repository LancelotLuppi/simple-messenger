#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

// Tempo de espera de 1 segundo para o usuário ler a mensagem da interface
int SLEEP_TIME = 1;

#define ARR_SIZE(a) (sizeof(a) / sizeof(*a))

// Pode representar Receptor ou Emissor
typedef struct Actor {
  int id;
  char name[15];
} Actor;

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

// TODO: fazer as implementacoes dos seguintes metodos:
void insertActor(Actor **list, Actor *actor) {
    Actor *aux = *list;

    while(aux->)
}
void removeActor();
void listActors();

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
void sendMessage(Queue **queue, Actor emissor, int id_receptor, char content[]) {
  Message *message = malloc(sizeof(Message));
  Queue *aux = malloc(sizeof(Queue));
  if (message && aux) {
    message->id_emissor = emissor.id;
    strcpy(message->content, content);

    aux = *queue;
    while (aux->next) {
        if(aux->id_receptor == id_receptor) {
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

// TODO ao inputar mais do que 10 chars está repetindo o while
// Valida e trata o input do usuario
void trataInput(int *selectedOption) {
  char input[10];
  int num;

  if (fgets(input, sizeof(input), stdin) != NULL) {
    char *endptr;

    num = strtol(input, &endptr, 10);

    // Caso ocorra algum erro no input, atribui a opção default
    if (*endptr != '\0' && *endptr != '\n') {
      *selectedOption = -1;
    }
    // Caso o input seja uma integer válida, atribui ela como opção selecionada
    else {
      *selectedOption = num;
    }
  } else {
    *selectedOption = -1;
  }
}

void showInterface() {
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
    // printf("  10) Outras operações (a seu critério), como: exibir receptores
    // "
    //        "com fila vazia, exibir receptores com mais mensagens na fila, "
    //        "exibir total de mensagens enviadas por um emissor, exibir total
    //        de " "mensagens recebidas por um receptor \n");

    trataInput(&userInput);

    // TODO ADICIONAR METODOS PARA CADA INPUT DO USUARIO
    switch (userInput) {
    case 0:
      printf("\n\n\n\nEncerrando... \n\n\n\n");
      sleep(SLEEP_TIME);
      break;
    case 1:
      printf("\n\n\n\nIncluir emissor na lista de emissores \n\n\n\n");
      sleep(SLEEP_TIME);
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
  Actor *emissores = NULL;
  Actor *receptores = NULL;
  Queue *message_queues = NULL;

  showInterface();

  return 0;
}
