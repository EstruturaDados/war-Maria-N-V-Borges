#include <stdio.h>
#include <stdlib.h> // dynamic memory and rand()
#include <string.h>
#include <time.h> // for srand(time(NULL))

// Definition of the struct (Definition da estrutura)
typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

// Function to simulate a battle (Modularização)
void batalhar(Territorio *atacante, Territorio *defensor) {
    printf("\n Batalha: %s (%s) vs %s (%s)\n", atacante->nome, atacante ->cor, defensor->nome, defensor->cor);

    // Generating random dice values (1 to 6)
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("Dado Atacante: %d | Dado Defesa: %d\n", dadoAtaque, dadoDefesa);

    // Logic: Attack wins or ties (Empates favorecem o atacante neste desafio)
    if (dadoAtaque >= dadoDefesa) {
        printf("Sucesso! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
           printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s!\n", defensor->nome, atacante->cor);
           strcpy(defensor->cor, atacante->cor);
           defensor->tropas = 1; // Start with 1 troop
        }

    } else {
        printf("🛡️ Defesa implacavel! O atacante falhou.\n");
    }
}


int main()
{
    srand(time(NULL)); // Seed for randomness

    int numTerritorios = 5;
    // Dynamic allocation with calloc (Alocação dinâmica)
    Territorio *mapa = (Territorio *) calloc(numTerritorios, sizeof(Territorio));

    if (mapa == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    printf("--- Cadastro Inicial (Nivel Aventureiro) ---\n");
    for (int i = 0; i < numTerritorios; i++)
    {
        printf("Territorio %d - Nome: ", i + 1);
        scanf(" %[^\n]s", mapa[i].nome);
        printf("Cor: ");
        scanf(" %[^\n]s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
    
    int op;
    do
    {
        printf("\n1. Atacar | 2. Ver Mapa | 0. Sair: ");
        scanf("%d", &op);

        if (op == 1) 
        {
            int at, df;
            printf("Index do Atacante (1-5): "); scanf("%d", &at);
            printf("Index do Defensor (1-5): "); scanf("%d", &df);

            if (at != df && at >= 1 && at <= 5 && df >= 1 && df <= 5)
            {
                batalhar(&mapa[at-1], &mapa[df-1]);
            } else {
                printf("Indices invalidos!\n");
            }  
        } else if (op == 2) {
            for (int i = 0; i < numTerritorios; i++)
            {
                printf("[%d] %-15s | Cor: %-10s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
            } 
        }
    } while (op != 0);

    // Freeing the memory (Importante!)
    free(mapa);
    printf("Memoria liberada. Ate a proxima!\n");
      

    return 0;
}
