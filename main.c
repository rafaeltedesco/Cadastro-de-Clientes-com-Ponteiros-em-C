#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define BLOCK_CLIENTE 10

typedef struct {
  char nome[30];
  int ano_nasc;
  float gastos;
} Cliente;

void showMenu(int * popt);
void incluirCliente(Cliente *pcliente, int * clientes_cadastrados);
void listarClientes(Cliente *pcliente, int clientes_cadastrados);
void removerCliente(Cliente *pcliente, int *clientes_cadastrados);
void zerarMontantes(Cliente *pcliente, int clientes_cadastrados);

int main() {
  Cliente *pcliente;
  pcliente = (Cliente *)malloc(sizeof(Cliente) * BLOCK_CLIENTE);
  int clientes_cadastrados = 0;
  int opt;

  do {

    showMenu(&opt);

    switch(opt) {

      case 1:
        incluirCliente(pcliente, &clientes_cadastrados);
        break;
      case 2:
        listarClientes(pcliente, clientes_cadastrados);
        break;
      case 3:
        removerCliente(pcliente, &clientes_cadastrados);
        break;
      case 4:
        zerarMontantes(pcliente, clientes_cadastrados);
        break;
    }
  } while(opt != 7);

  free(pcliente);
  pcliente = NULL;
  return 0;
}

void zerarMontantes(Cliente *pcliente, int clientes_cadastrados) {
  
  if (!clientes_cadastrados) {
    printf("Não há clientes cadastrados para realizar a limpeza dos montantes!\n");
    sleep(2);
  }
  else {
    Cliente *first_el = pcliente;
    Cliente *last_el = (pcliente + clientes_cadastrados - 1);
    
    printf("Limpando todos os montantes!\n");
    
    while (pcliente <= last_el) {
      pcliente->gastos = 0;
      pcliente++;
    }

    printf("Limpeza realizada com sucesso!\n");
  }
  sleep(2);
  system("clear");


}



void removerCliente(Cliente *pcliente, int *clientes_cadastrados) {

  if (!*clientes_cadastrados) {
    printf("Ainda não há clientes cadastrados para excluir!\n");
    sleep(2);
  }
  else {

    char nome[30];
    bool found = false;
    int pos = 0;

    printf("Digite o nome do cliente a ser removido: ");
    scanf("%s", nome);
    
    Cliente *first_el = pcliente;
    Cliente *last_el = (pcliente + *clientes_cadastrados - 1);

    while (pcliente <= last_el) {
      if (!strcmp(pcliente->nome, nome)) {
        printf("Removendo o cliente %s na posição %i\n", pcliente->nome, pos + 1);
        found = true;
        break;
      }

      pos++;
      pcliente++;
    }

    if (!found) {
      printf("Cliente %s não encontrado nos registros!\n", nome);
    }
    else {
      if (pos == *clientes_cadastrados-1) {
        printf("Limpando!\n");
        strcpy(pcliente->nome, "");
        pcliente->ano_nasc = 0;
        pcliente->gastos = 0;
      }
      else {
        for (int i = pos; i < *clientes_cadastrados - 1; i++) {
          pcliente[i] = pcliente[i + 1];
        }
      }
      printf("Registro excluído!\n");
      *clientes_cadastrados = *clientes_cadastrados - 1;
    }

    pcliente = first_el;

    sleep(2);
    system("clear");
    }
}


void incluirCliente(Cliente *pcliente, int * clientes_cadastrados) {
  
  printf("Digite o nome do %iº cliente: ", *clientes_cadastrados + 1);
  scanf("%s", pcliente[*clientes_cadastrados].nome);
  printf("Digite o ano de nascimento do cliente %s: ", pcliente[*clientes_cadastrados].nome);
  scanf("%i", &pcliente[*clientes_cadastrados].ano_nasc);
  printf("Digite os gastos do cliente desse mês: ");
  scanf("%f", &pcliente[*clientes_cadastrados].gastos);
  
  *clientes_cadastrados = *clientes_cadastrados + 1;

  system("clear");

}

void listarClientes(Cliente *pcliente, int clientes_cadastrados) {

  if (!clientes_cadastrados) {
    printf("Ainda não há clientes cadastrados para serem exibidos\n");
    sleep(2);
  }
  else {
    int i = 0;
    Cliente *last_el = (pcliente + clientes_cadastrados - 1);
    Cliente *first_el = pcliente;

    while (pcliente <= last_el) {
      printf("Exibindo dados do %iº cliente\n", i + 1);
      printf("============================================\n");
      printf("Nome: %s\n", pcliente->nome);
      printf("Ano Nascimento: %d\n", pcliente->ano_nasc);
      printf("Gastos: %.2f\n", pcliente->gastos);
      printf("\n\n");
      pcliente++;
    }
    pcliente = first_el;

    sleep(3);
  }

  system("clear");

}

void showMenu(int * popt) {

  printf("Gerenciador de Clientes - Loja FMU\n");
  printf("=============================================\n");
  printf("|                                           |\n");
  printf("|     1 - Incluir Cliente                   |\n");
  printf("|     2 - Listar Clientes                   |\n");
  printf("|     3 - Remover Cliente                   |\n");
  printf("|     4 - Zerar todos montantes             |\n");
  printf("|     5 - Listar Melhor comprador           |\n");
  printf("|     6 - Exibir Montante por Cliente       |\n");
  printf("|     7 - Sair                              |\n");
  printf("|                                           |\n");
  printf("============================================\n");

  printf("Digite a opção desejada: ");
  scanf("%d", popt);
  system("clear");

}