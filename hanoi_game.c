/*
 * TORRES DE HANOI - Jogo Interativo em C
 * Implementacao com Estrutura de Dados: PILHA (Stack)
 *
 * Objetivo: Mover todos os discos da Torre A para Torre C
 * Regra: Nunca colocar um disco maior sobre um disco menor
 *
 * Compile com: gcc -o hanoi hanoi_game.c
 * Execute com: ./hanoi
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISCOS 10
#define MAX_PILHA 100

typedef struct {
  int discos[MAX_PILHA];
  int topo;
} Pilha;

typedef struct {
  Pilha torres[3];
  int num_discos;
  int movimentos;
} Jogo;

/* Inicializa uma pilha vazia */
void pilha_inicializar(Pilha *p) { p->topo = -1; }

/* Verifica se a pilha esta vazia */
int pilha_vazia(Pilha *p) { return p->topo == -1; }

/* Verifica se a pilha esta cheia */
int pilha_cheia(Pilha *p) { return p->topo == MAX_PILHA - 1; }

/* Empilha um disco */
int pilha_empilhar(Pilha *p, int disco) {
  if (pilha_cheia(p)) {
    printf("Erro: Pilha cheia!\n");
    return 0;
  }
  p->discos[++(p->topo)] = disco;
  return 1;
}

/* Desempilha um disco */
int pilha_desempilhar(Pilha *p) {
  if (pilha_vazia(p)) {
    printf("Erro: Pilha vazia!\n");
    return -1;
  }
  return p->discos[(p->topo)--];
}

/* Retorna o topo da pilha sem remover */
int pilha_topo(Pilha *p) {
  if (pilha_vazia(p)) {
    return -1;
  }
  return p->discos[p->topo];
}

/* Retorna o tamanho da pilha */
int pilha_tamanho(Pilha *p) { return p->topo + 1; }

/* Inicializa o jogo */
void jogo_inicializar(Jogo *j, int num_discos) {
  if (num_discos < 1 || num_discos > MAX_DISCOS) {
    num_discos = 3;
  }

  j->num_discos = num_discos;
  j->movimentos = 0;

  for (int i = 0; i < 3; i++) {
    pilha_inicializar(&j->torres[i]);
  }

  /* Carrega todos os discos na Torre A (do maior para o menor) */
  for (int i = num_discos; i >= 1; i--) {
    pilha_empilhar(&j->torres[0], i);
  }
}

/* Desenha o estado atual do jogo */
void jogo_exibir(Jogo *j) {
  printf("\n");
  printf("+------------------------------------------------+\n");
  printf("|            TORRES DE HANOI - Jogo em C         |\n");
  printf("+------------------------------------------------+\n\n");

  /* Encontra a altura maxima */
  int altura_max = 0;
  for (int i = 0; i < 3; i++) {
    if (pilha_tamanho(&j->torres[i]) > altura_max) {
      altura_max = pilha_tamanho(&j->torres[i]);
    }
  }

  /* Desenha de cima para baixo */
  for (int linha = altura_max - 1; linha >= 0; linha--) {
    for (int col = 0; col < 3; col++) {
      printf("  ");
      if (linha < pilha_tamanho(&j->torres[col])) {
        int disco = j->torres[col].discos[linha];
        int largura = disco * 2 - 1;
        int padding = (9 - largura) / 2;

        for (int i = 0; i < padding; i++)
          printf(" ");
        for (int i = 0; i < largura; i++)
          printf("#");
        for (int i = 0; i < padding; i++)
          printf(" ");
      } else {
        printf("    |    ");
      }
      printf("  ");
    }
    printf("\n");
  }

  /* Base das torres */
  printf("  ");
  for (int i = 0; i < 3; i++) {
    printf("---------  ");
  }
  printf("\n");

  printf("  ");
  for (int i = 0; i < 3; i++) {
    printf("   %c      ", 'A' + i);
  }
  printf("\n");

  printf("\n+ Status ----------------------------------------+\n");
  printf("| Discos: %d | Movimentos: %d                        |\n",
         j->num_discos, j->movimentos);
  printf("| Torre A: %d disco(s) | Torre B: %d disco(s) | Torre C: %d disco(s) "
         "|\n",
         pilha_tamanho(&j->torres[0]), pilha_tamanho(&j->torres[1]),
         pilha_tamanho(&j->torres[2]));
  printf("+------------------------------------------------+\n");
}

/* Realiza um movimento de uma torre para outra */
int jogo_mover(Jogo *j, char origem, char destino) {
  int idx_origem = origem - 'A';
  int idx_destino = destino - 'A';

  /* Valida indices */
  if (idx_origem < 0 || idx_origem > 2 || idx_destino < 0 || idx_destino > 2) {
    printf("[ERRO] Torres invalidas! Use: A, B ou C\n");
    return 0;
  }

  if (idx_origem == idx_destino) {
    printf("[ERRO] Origem e destino devem ser diferentes!\n");
    return 0;
  }

  /* Verifica se a torre origem esta vazia */
  if (pilha_vazia(&j->torres[idx_origem])) {
    printf("[ERRO] A torre %c esta vazia!\n", origem);
    return 0;
  }

  /* Obtem o disco do topo da origem */
  int disco = pilha_topo(&j->torres[idx_origem]);

  /* Verifica a regra: disco maior sobre menor */
  int topo_destino = pilha_topo(&j->torres[idx_destino]);
  if (topo_destino != -1 && topo_destino < disco) {
    printf("[ERRO] Movimento ilegal! Disco maior sobre menor!\n");
    printf("   Voce tentou mover disco %d sobre disco %d\n", disco,
           topo_destino);
    return 0;
  }

  /* Realiza o movimento */
  pilha_desempilhar(&j->torres[idx_origem]);
  pilha_empilhar(&j->torres[idx_destino], disco);
  j->movimentos++;

  printf("[OK] Moveu disco %d de %c para %c\n", disco, origem, destino);
  return 1;
}

/* Verifica se o jogo foi vencido */
int jogo_venceu(Jogo *j) {
  return pilha_tamanho(&j->torres[2]) == j->num_discos &&
         pilha_vazia(&j->torres[0]) && pilha_vazia(&j->torres[1]);
}

/* Calcula o numero minimo de movimentos necessarios */
int movimentos_minimos(int n) { return (1 << n) - 1; /* 2^n - 1 */ }

/* Exibe as instrucoes */
void exibir_instrucoes(int num_discos) {
  printf("\n+------------------------------------------------+\n");
  printf("|                  INSTRUCOES                    |\n");
  printf("+------------------------------------------------+\n\n");
  printf("Objetivo: Mover todos os %d disco(s) da Torre A para Torre C\n\n",
         num_discos);
  printf("Regras:\n");
  printf("  1. Apenas um disco pode ser movido por vez\n");
  printf("  2. Nunca coloque um disco maior sobre um disco menor\n");
  printf("  3. Use qualquer torre intermediaria necessaria\n\n");
  printf("Como jogar:\n");
  printf("  * Digite o comando: <ORIGEM> <DESTINO>\n");
  printf("  * Exemplo: A C (move um disco de A para C)\n");
  printf("  * Use letras maiusculas: A, B ou C\n");
  printf("  * Digite 'h' para estas instrucoes\n");
  printf("  * Digite 's' para sair\n\n");
  printf("Numero minimo de movimentos: %d\n\n", movimentos_minimos(num_discos));
}

/* Menu de selecao de dificuldade */
int menu_dificuldade() {
  int num_discos;

  printf("\n+------------------------------------------------+\n");
  printf("|      TORRES DE HANOI - SELECAO DE NIVEL      |\n");
  printf("+------------------------------------------------+\n\n");
  printf("Escolha o numero de discos:\n\n");
  printf("  1) Facil    (3 discos) - 7 movimentos minimos\n");
  printf("  2) Medio    (4 discos) - 15 movimentos minimos\n");
  printf("  3) Dificil  (5 discos) - 31 movimentos minimos\n");
  printf("  4) Extremo  (6 discos) - 63 movimentos minimos\n");
  printf("  5) Customizado (1-10 discos)\n\n");
  printf("Digite sua escolha (1-5): ");

  int escolha;
  scanf("%d", &escolha);
  getchar(); /* Consome o newline */

  switch (escolha) {
  case 1:
    return 3;
  case 2:
    return 4;
  case 3:
    return 5;
  case 4:
    return 6;
  case 5:
    printf("\nQuantos discos? (1-10): ");
    scanf("%d", &num_discos);
    getchar();
    return (num_discos < 1 || num_discos > 10) ? 3 : num_discos;
  default:
    printf("\nOpcao invalida! Usando nivel facil (3 discos).\n");
    return 3;
  }
}

/* Funcao principal do jogo */
int main() {
  Jogo jogo;
  char origem, destino;
  char comando[10];

  printf("\n");
  printf("************************************************\n");
  printf("*                                              *\n");
  printf("*          BEM-VINDO AO TORRES DE HANOI        *\n");
  printf("*                 Jogo em C com                *\n");
  printf("*            Estrutura de Dados: PILHA         *\n");
  printf("*                                              *\n");
  printf("************************************************\n");

  int num_discos = menu_dificuldade();
  jogo_inicializar(&jogo, num_discos);
  exibir_instrucoes(num_discos);

  printf("\nPressione ENTER para comecar...");
  getchar();

  while (1) {
    jogo_exibir(&jogo);

    if (jogo_venceu(&jogo)) {
      printf("\n");
      printf("+------------------------------------------------+\n");
      printf("|            ! PARABENS! VOCE VENCEU! !          |\n");
      printf("+------------------------------------------------+\n\n");
      printf("Voce completou o jogo em %d movimentos!\n", jogo.movimentos);
      printf("O numero minimo possivel era: %d movimentos\n",
             movimentos_minimos(num_discos));

      if (jogo.movimentos == movimentos_minimos(num_discos)) {
        printf("* PERFEITO! Voce alcancou o numero minimo!\n");
      } else {
        printf("Diferenca: %d movimentos a mais\n",
               jogo.movimentos - movimentos_minimos(num_discos));
      }
      break;
    }

    printf(
        "\nDigite seu movimento (ex: A C) ou 'h' para ajuda, 's' para sair: ");

    if (fgets(comando, sizeof(comando), stdin) == NULL) {
      break;
    }

    /* Remove newline */
    comando[strcspn(comando, "\n")] = '\0';

    /* Processa comando */
    if (strlen(comando) == 0) {
      continue;
    }

    if (comando[0] == 's' || comando[0] == 'S') {
      printf("\nObrigado por jogar! Ate logo!\n\n");
      break;
    }

    if (comando[0] == 'h' || comando[0] == 'H') {
      exibir_instrucoes(jogo.num_discos);
      printf("\nPressione ENTER para continuar...");
      getchar();
      continue;
    }

    /* Processa movimento */
    if (strlen(comando) >= 3) {
      origem = toupper(comando[0]);
      destino = toupper(comando[2]);

      jogo_mover(&jogo, origem, destino);
    } else {
      printf("[ERRO] Formato invalido! Use: A C\n");
    }
  }

  return 0;
}
