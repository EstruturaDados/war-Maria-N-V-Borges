#include <stdio.h>
#include <string.h>

// Definition of the struct (Definition da estrutura)
typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

int main()
{
    // Array of 5 territories (Vetor estático de 5 elementos)
    Territorio mapa[5];
    
    printf("--- Bem-vindo(a) ao MateCheck WAR: Cadastro de Territorios ---\n\n");
    
    // Loop for data entry (Cadastro dos dados)
    for (int i = 0; i < 5; i++) {
        printf("Digite os dados do território %d:\n", i + 1);
        
        printf("Nome: ");
        scanf(" %[^\n]s", mapa[i].nome); // Lê a string com espaços
        
        printf("Cor do Exército: ");
        scanf(" %[^\n]s", mapa[i].cor);
        
        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("---------------------\n");
        }
        
        // Displaying the map status (Exibição do estado do mapa)
        printf("\n### ESTADO ATUAL DO MAPA ###\n");
        for (int i = 0; i < 5; i++) {
            printf("Território: %-15s | cor: %-10s | Tropas: %d\n",
                    mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        
        
    return 0;
}
