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
void liberar_quarto() {
    int quarto;
    int encontrado = 0;

    printf("Digite o numero do quarto a ser liberado: ");
    scanf("%d", &quarto);

    for (int i = 0; i < total_hospedes; i++) {
        if (hospedes[i].quarto == quarto) {
            encontrado = 1;
            for (int j = i; j < total_hospedes - 1; j++) {
                strcpy(hospedes[j].nome, hospedes[j + 1].nome);
                hospedes[j].quarto = hospedes[j + 1].quarto;
            }
            total_hospedes--;
            break;
        }
    }

    if (encontrado) {
        printf("Quarto %d liberado com sucesso.\n", quarto);
        salvar_hospedes_no_arquivo();
    } else {
        printf("Quarto nao encontrado.\n");
    }
}

void mostrar_quartos_vazios() {
    int quartos[MAX_HOSPEDES];
    int num_quartos = 0;

    for (int i = 0; i < MAX_HOSPEDES; i++) {
        quartos[i] = i + 1;
    }

    for (int i = 0; i < total_hospedes; i++) {
        for (int j = 0; j < MAX_HOSPEDES; j++) {
            if (quartos[j] == hospedes[i].quarto) {
                quartos[j] = 0;
                break;
            }
        }
    }

    printf("Quartos vazios: ");
    for (int i = 0; i < MAX_HOSPEDES; i++) {
        if (quartos[i] != 0) {
            printf("%d ", quartos[i]);
            num_quartos++;
        }
    }

    if (num_quartos == 0) {
        printf("Todos os quartos estao ocupados.\n");
    } else {
        printf("\n");
    }
}

void exibir_menu() {
    printf("\n==== Menu ====\n");
    printf("1. Inserir hospedes em um quarto vazio\n");
    printf("2. Listar hospedes por ordem alfabetica\n");
    printf("3. Buscar hospede\n");
    printf("4. Editar hospede\n");
    printf("5. Liberar um quarto\n");
    printf("6. Mostrar os numeros dos quartos vazios\n");
    printf("7. Sair\n");
    printf("Escolha uma opcao: ");
}
