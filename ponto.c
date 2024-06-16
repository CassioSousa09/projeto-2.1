#include <stdio.h>
#include <string.h>
#include "ponto.h"



ERROS criar(Tarefa tarefas[], int *pos) {
    if (*pos >= TOTAL)
        return MAX_TAREFA;

    do {
        printf("Entre com a prioridade (1-10): ");
        scanf("%d", &tarefas[*pos].prioridade);
        clearBuffer();
    } while (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10);

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, CATEGORIA, stdin);
    if (tarefas[*pos].categoria[strlen(tarefas[*pos].categoria) - 1] == '\n') {
        tarefas[*pos].categoria[strlen(tarefas[*pos].categoria) - 1] = '\0';
    }

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, DESCRICAO, stdin);
    if (tarefas[*pos].descricao[strlen(tarefas[*pos].descricao) - 1] == '\n') {
        tarefas[*pos].descricao[strlen(tarefas[*pos].descricao) - 1] = '\0';
    }

    *pos = *pos + 1;

    return OK;
}





ERROS deletar(Tarefa tarefas[], int *pos){
  // teste se existem tarefas
  if(*pos == 0)
      return SEM_TAREFAS;

  // verifica se a tarefa escolhida existe
  int pos_deletar;
  printf("Entre com a posicao da tarefa a ser deletada: ");
  scanf("%d", &pos_deletar);
  pos_deletar--; // garantir posicao certa no array
  if(pos_deletar >= *pos || pos_deletar < 0)
      return NAO_ENCONTRADO;

  for(int i = pos_deletar; i < *pos; i++){
      tarefas[i].prioridade = tarefas[i+1].prioridade;
      strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
      strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
  }

  *pos = *pos - 1;

  return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
    if (*pos == 0)
        return SEM_TAREFAS;

    char categoria[CATEGORIA];
    int encontrou = 0;

    printf("Digite a categoria que deseja listar ou  clique enter para listar todas: ");
    fgets(categoria, CATEGORIA, stdin);
    if (categoria[strlen(categoria) - 1] == '\n') {
        categoria[strlen(categoria) - 1] = '\0';
    }

    for (int i = 0; i < *pos; i++) {
        if (strlen(categoria) == 0 || strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("Pos: %d\t", i + 1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada para a categoria '%s'.\n", categoria);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
  FILE *f = fopen("info.bin", "wb");
  if(f == NULL)
      return ABRIR;

  int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
  if(qtd == 0)
      return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if(qtd == 0)
      return ESCREVER;

  if(fclose(f))
      return FECHAR;

  return OK;
}




ERROS carregar(Tarefa tarefas[], int *pos){
  FILE *f = fopen("info.bin", "rb");
  if(f == NULL)
      return ABRIR;

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if(qtd == 0)
      return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if(qtd == 0)
      return LER;

  if(fclose(f))
      return FECHAR;

  return OK;

}





ERROS gravar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("arquivo.txt", "w");
    if (f == NULL)
        return ABRIR;

    for (int i = 0; i < *pos; i++) {
        fprintf(f, "Prioridade: %d\n", tarefas[i].prioridade);
        fprintf(f, "Categoria: %s\n", tarefas[i].categoria);
        fprintf(f, "Descrição: %s\n", tarefas[i].descricao);
        fprintf(f, "-------------------------\n");
    }

    if (fclose(f) != 0) { 
        return FECHAR; 
    }

    return OK;
}

ERROS exportar(Tarefa tarefas[], int *pos) {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo que esta em bin para exportar para  txt): ");
    fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
    if (nomeArquivo[strlen(nomeArquivo) - 1] == '\n') {
        nomeArquivo[strlen(nomeArquivo) - 1] = '\0';
    }

    FILE *f = fopen(nomeArquivo, "w");
    if (f == NULL)
        return ABRIR;

    for (int i = 0; i < *pos; i++) {
        fprintf(f, "Prioridade: %d, Categoria: %s, Descrição: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
    }

    if (fclose(f) != 0) {
        return FECHAR;
    }

    return OK;
}



void clearBuffer(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}