#include <stdio.h>
#include "ponto.h"

int main() {
    funcao fs[] = {criar, deletar, listar, salvar, carregar, gravar, exportar};
    Tarefa tarefas[TOTAL];
    int pos = 0; // Inicializando pos

    int opcao;
    do {
        printf("Bem vindo! \n");
        printf("------------------\n");
        printf("0 - Sair\n");
        printf("1 - Criar conta\n");
        printf("2 - Apagar cliente \n");
        printf("3 - Listar cliente\n");
        printf("4 - Salvar em bin\n");
        printf("5 - Carregar em bin\n");
        printf("6 - Salvar em txt\n");
        printf("7 - Exportar para arquivo de texto\n");
        printf("------------------\n");
        printf("Escolha uma Opção: ");
        scanf("%d", &opcao);
        clearBuffer();

        if (opcao > 0 && opcao <= 7) {
            ERROS erro = fs[opcao - 1](tarefas, &pos);
            if (erro != OK) {
                printf("Erro encontrado: ");
                switch (erro) {
                    case MAX_TAREFA:
                        printf("Número máximo de tarefas atingido.\n");
                        break;
                    case SEM_TAREFAS:
                        printf("Não há tarefas para serem processadas.\n");
                        break;
                    case NAO_ENCONTRADO:
                        printf("Tarefa não encontrada.\n");
                        break;
                    case ABRIR:
                        printf("Erro ao abrir o arquivo.\n");
                        break;
                    case FECHAR:
                        printf("Erro ao fechar o arquivo.\n");
                        break;
                    case ESCREVER:
                        printf("Erro ao escrever no arquivo.\n");
                        break;
                    case LER:
                        printf("Erro ao ler do arquivo.\n");
                        break;
                    default:
                        printf("Erro desconhecido.\n");
                        break;
                }
            }
            printf("------------------\n");
        } else if (opcao == 0) {
            printf("Até mais =( \n");
        } else {
            printf("**Opção Inválida**\n");
            printf("------------------\n");
        }
    } while (opcao != 0);

    return 0;
}