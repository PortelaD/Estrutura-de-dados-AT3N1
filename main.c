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
