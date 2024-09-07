#include <stdio.h>

typedef struct {
    // informações sobre a espécie
    int id_especie;
    char nome[41];
    char nome_cientifico[41];
    char status;
    int impacto_humano;

    // informações sobre a localização
    float eixo_x;
    float eixo_y;



} Especie_marinha;


void registrar (const char  *arquivo) {
    FILE *file = fopen(arquivo, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    int numero_especies;
    scanf("%d", &numero_especies);
    for (int i = 0; i < numero_especies; i++) {
       
        Especie_marinha species;
        scanf("%d", &species.id_especie);
        scanf("%s", species.nome);
        scanf("%s", species.nome_cientifico);
        scanf(" %c", &species.status);
        scanf("%d", &species.impacto_humano);
        scanf("%f", &species.eixo_x);
        scanf("%f", &species.eixo_y);

        fwrite(&species, sizeof(Especie_marinha), 1, file);
    }
    fclose(file);
    printf("concluido\n");
}

void listar( const char *arquivo){
    FILE *file = fopen(arquivo, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    Especie_marinha species;

    while ( fread (&species, sizeof(Especie_marinha), 1, file) == 1) {
        printf("ID: %d\n", species.id_especie);
        printf("Nome: %s\n", species.nome);
        printf("Nome cientifico: %s\n", species.nome_cientifico);
        printf("Status: %c\n", species.status);
        printf("Impacto humano: %d\n", species.impacto_humano);
        printf("Eixo x: %.2f\n", species.eixo_x);
        printf("Eixo y: %.2f\n", species.eixo_y);
        printf("\n");
    }

}