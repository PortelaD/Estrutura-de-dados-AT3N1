#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hospedes.h"

Hospede hospedes[MAX_HOSPEDES];
int total_hospedes = 0;

void carregar_hospedes_do_arquivo() {
    FILE *arquivo;
    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    while (fscanf(arquivo, "%s %d", hospedes[total_hospedes].nome, &hospedes[total_hospedes].quarto) != EOF) {
        total_hospedes++;
    }

    fclose(arquivo);
}

void salvar_hospedes_no_arquivo() {
    FILE *arquivo;
    arquivo = fopen(ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    for (int i = 0; i < total_hospedes; i++) {
        fprintf(arquivo, "Nome hospede: %s\nNumero quarto: %d\n", hospedes[i].nome, hospedes[i].quarto);
    }

    fclose(arquivo);
}

void criar_arquivo_hospedes() {
    FILE *arquivo;
    arquivo = fopen(ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    fclose(arquivo);
}

void inserir_hospede() {
    char nome[MAX_NOME];
    int quarto;

    printf("Digite o nome do hospede: ");
    scanf("%s", nome);

    printf("Digite o numero do quarto: ");
    scanf("%d", &quarto);

    for (int i = 0; i < total_hospedes; i++) {
        if (hospedes[i].quarto == quarto) {
            printf("Este quarto ja esta ocupado.\n");
            return;
        }
    }

    strcpy(hospedes[total_hospedes].nome, nome);
    hospedes[total_hospedes].quarto = quarto;
    total_hospedes++;

    printf("Hospede inserido com sucesso.\n");

    salvar_hospedes_no_arquivo();
}

void listar_hospedes_por_nome() {
    for (int i = 0; i < total_hospedes - 1; i++) {
        for (int j = i + 1; j < total_hospedes; j++) {
            if (strcmp(hospedes[i].nome, hospedes[j].nome) > 0) {
                Hospede temp = hospedes[i];
                hospedes[i] = hospedes[j];
                hospedes[j] = temp;
            }
        }
    }

    printf("Hospedes em ordem alfabetica por nome:\n");
    for (int i = 0; i < total_hospedes; i++) {
        printf("Nome: %s, Quarto: %d\n", hospedes[i].nome, hospedes[i].quarto);
    }
}

void buscar_hospede() {
    char nome[MAX_NOME];
    int encontrado = 0;

    printf("Digite o nome do hospede a ser buscado: ");
    scanf("%s", nome);

    for (int i = 0; i < total_hospedes; i++) {
        if (strcmp(hospedes[i].nome, nome) == 0) {
            printf("Hospede encontrado no quarto %d.\n", hospedes[i].quarto);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Hospede nao encontrado.\n");
    }
}

void editar_hospede() {
    char nome[MAX_NOME];
    int opcao, quarto;

    printf("Digite o nome do hospede que deseja editar: ");
    scanf("%s", nome);

    for (int i = 0; i < total_hospedes; i++) {
        if (strcmp(hospedes[i].nome, nome) == 0) {
            printf("Hospede encontrado.\n");
            printf("O que deseja editar?\n");
            printf("1. Nome\n");
            printf("2. Numero do quarto\n");
            printf("3. Ambos\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch(opcao) {
                case 1:
                    printf("Digite o novo nome do hospede: ");
                    scanf("%s", hospedes[i].nome);
                    break;
                case 2:
                    printf("Digite o novo numero do quarto: ");
                    scanf("%d", &hospedes[i].quarto);
                    break;
                case 3:
                    printf("Digite o novo nome do hospede: ");
                    scanf("%s", hospedes[i].nome);

                    printf("Digite o novo numero do quarto: ");
                    scanf("%d", &hospedes[i].quarto);
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }

            printf("Hospede editado com sucesso.\n");

            salvar_hospedes_no_arquivo();
            return;
        }
    }

    printf("Hospede nao encontrado.\n");
}
