#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ELEITORES 100

typedef struct {
    char cpf[12]; // Considerando CPF no formato "12345678909"
    bool jaVotou;
    int voto;
} Eleitor;

Eleitor eleitores[MAX_ELEITORES];
int numEleitores = 0;

// Função para validar CPF
bool validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) return false;

    int soma = 0, digito1, digito2;
    for (int i = 0; i < 9; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return false;
        soma += (cpf[i] - '0') * (10 - i);
    }

    digito1 = (soma * 10) % 11;
    if (digito1 == 10 || digito1 == 11) digito1 = 0;

    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }

    digito2 = (soma * 10) % 11;
    if (digito2 == 10 || digito2 == 11) digito2 = 0;

    return (digito1 == cpf[9] - '0' && digito2 == cpf[10] - '0');
}

// Função para registrar voto
bool registrarVoto(const char *cpf, int voto) {
    for (int i = 0; i < numEleitores; i++) {
        if (strcmp(eleitores[i].cpf, cpf) == 0) {
            if (eleitores[i].jaVotou) {
                printf("Eleitor já votou!\n");
                return false;
            } else {
                eleitores[i].voto = voto;
                eleitores[i].jaVotou = true;
                printf("Voto registrado com sucesso!\n");
                return true;
            }
        }
    }

    // Caso o eleitor não esteja registrado, adicione-o
    strcpy(eleitores[numEleitores].cpf, cpf);
    eleitores[numEleitores].voto = voto;
    eleitores[numEleitores].jaVotou = true;
    numEleitores++;
    printf("Eleitor registrado e voto contabilizado com sucesso!\n");
    return true;
}

int main() {
    char cpf[12];
    int voto;

    printf("Digite o CPF do eleitor (11 dígitos): ");
    scanf("%s", cpf);

    if (!validarCPF(cpf)) {
        printf("CPF inválido!\n");
        return 1;
    }

    printf("Digite o voto (número): ");
    scanf("%d", &voto);

    registrarVoto(cpf, voto);

    return 0;
}
