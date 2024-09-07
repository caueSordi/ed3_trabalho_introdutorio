#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int especieID;
    char nome[41];
    char nome_cientifico[61];
    int populacao;
    char status[9];
    float localizacao[2]; // coordenadas em x e y cada com 4 bytes
    int impacto_humano;
} Registro;



void readline(char* string, int tamanho) {
    fgets(string, tamanho, stdin);  // Lê uma linha com limite de tamanho
    size_t len = strlen(string); // tamanho da string lida
    if (len > 0 && string[len - 1] == '\n') { 
        string[len - 1] = '\0';  // Remove o caractere de nova linha
    }
}

void binarioNaTela(const char* nomeArquivoBinario) {
    unsigned long i, cs;
    unsigned char* mb;
    size_t fl;
    FILE* fs;

    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA: não foi possível abrir o arquivo para leitura.\n");
        return;
    }

    fseek(fs, 0, SEEK_END);     // Vai para o final do arquivo
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);  // Volta para o início do arquivo

    mb = (unsigned char*)malloc(fl);
    fread(mb, 1, fl, fs);  // Lê o arquivo binário na memória

    cs = 0;
    for (i = 0; i < fl; i++) {
        cs += (unsigned long)mb[i];  // Soma todos os bytes do arquivo
    }

    printf("%lf\n", (cs / (double)100));  // Exibe a soma dos bytes dividida por 100
    free(mb);  // Libera a memória
    fclose(fs);  // Fecha o arquivo
}

void registrarEspecies(const char *nomearquivo, int num) {
    Registro *animais = malloc(num * sizeof(*animais));
    if (animais == NULL) {   //se nao deu problema algum (por enquanto)
        printf("Erro ao alocar memória\n");
        return;
    }

    FILE *file = fopen(nomearquivo, "ab"); // abre o arquivo em ab = append binario
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n"); //se nao deu problema algum (por enquanto)
        free(animais);
        return;
    }

    for (int i = 0; i < num; i++) {
        char coordx[20], coordy[20], populacao[20], impacto[20], Id[20]; //variaveis auxiliares para leitura    

        // Ler dados para cada registro
        printf("Digite o ID da espécie: ");
        readline(Id, sizeof(Id));
        animais[i].especieID = atoi(Id);

        printf("Digite o nome comum da espécie: ");
        readline(animais[i].nome, sizeof(animais[i].nome));

        printf("Digite o nome científico da espécie: ");
        readline(animais[i].nome_cientifico, sizeof(animais[i].nome_cientifico));

        printf("Digite a população: ");
        readline(populacao, sizeof(populacao));
        animais[i].populacao = atoi(populacao);

        printf("Digite o status: ");
        readline(animais[i].status, sizeof(animais[i].status));

        printf("Digite a coordenada X: ");
        readline(coordx, sizeof(coordx));
        animais[i].localizacao[0] = atof(coordx);

        printf("Digite a coordenada Y: ");
        readline(coordy, sizeof(coordy));
        animais[i].localizacao[1] = atof(coordy);

        printf("Digite o impacto humano: ");
        readline(impacto, sizeof(impacto));
        animais[i].impacto_humano = atoi(impacto);

        // Grava o registro no arquivo binário
        fwrite(&animais[i], sizeof(Registro), 1, file);
    }

    fclose(file);
    free(animais);  // Libera a memória alocada, e tambem libera os animaiszinhos 
    printf("Espécies registradas com sucesso!\n");
}

void exibirEspecies(const char *nomearquivo) {
    FILE *file = fopen(nomearquivo, "rb");
    if (file == NULL) {
        printf("Falha no processamento do arquivo\n");
        return;
    }

    Registro especie;
    size_t tamanho_registro = sizeof(Registro);
    while (fread(&especie, tamanho_registro, 1, file)) { //enquanto tiver conteudo para ler
        printf("ID: %d\n", especie.especieID);
        printf("Nome: %s\n", strcmp(especie.nome, "") == 0 ? "NULO" : especie.nome);
        printf("Nome Científico: %s\n", strcmp(especie.nome_cientifico, "") == 0 ? "NULO" : especie.nome_cientifico);
        printf("População: %d\n", especie.populacao == 0 ? 0 : especie.populacao);
        printf("Status: %s\n", strcmp(especie.status, "") == 0 ? "NULO" : especie.status);
        printf("Localização: (%.2f, %.2f)\n", especie.localizacao[0], especie.localizacao[1]); //eixo x e y juntos 
        printf("Impacto Humano: %d\n\n", especie.impacto_humano);
    }

    fclose(file);
}

void buscarEspecie(const char *nomearquivo, int rrn) {
    FILE *file = fopen(nomearquivo, "rb");
    if (file == NULL) { //se nao deu problema algum (por enquanto)
        printf("Falha no processamento do arquivo\n");
        return;
    }

    Registro especie;
    fseek(file, rrn * sizeof(Registro), SEEK_SET); //vai para o RRN desejado
    size_t tamanho_registro = sizeof(Registro); //tamanho do registro   
    if (fread(&especie, tamanho_registro, 1, file) != 1) {  //caso o arquivo nao tenha o que ler
        printf("Espécie não encontrada\n");
    } else { // caso bem sucedido deve printar as informações seguintes
        printf("ID: %d\n", especie.especieID);
        printf("Nome: %s\n", strcmp(especie.nome, "") == 0 ? "NULO" : especie.nome);
        printf("Nome Científico: %s\n", strcmp(especie.nome_cientifico, "") == 0 ? "NULO" : especie.nome_cientifico);
        printf("População: %d\n", especie.populacao == 0 ? 0 : especie.populacao);
        printf("Status: %s\n", strcmp(especie.status, "") == 0 ? "NULO" : especie.status);
        printf("Localização: (%.2f, %.2f)\n", especie.localizacao[0], especie.localizacao[1]);
        printf("Impacto Humano: %d\n", especie.impacto_humano);
    }

    fclose(file);
}

void atualizarInformacoes(const char *nomearquivo, int id, int numInfo) {
    FILE *file = fopen(nomearquivo, "r+b"); 
    if (file == NULL) {  //se nao deu problema algum (por enquanto)
        printf("Falha no processamento do arquivo\n");
        return;
    }

    Registro especie;  // nossa sctruct 
    int encontrado = 0; //flag para saber se encontrou ou nao
    size_t tamanho_registro = sizeof(Registro);   

    while (fread(&especie, tamanho_registro, 1, file)) { //enquanto tiver conteudo para ler
        if (especie.especieID == id) { 
            encontrado = 1;
            fseek(file, -tamanho_registro, SEEK_CUR); //volta para o inicio do registro

            for (int i = 0; i < numInfo; i++) { //enqauanto tiver informação para atualizar
                char tipo[20];
                char dado[20];
                
                // Ler o tipo e o dado a ser atualizado
                readline(tipo, sizeof(tipo)); 
                
               //se o tipo for igual a status, ele vai atualizar o status  
                readline(dado, sizeof(dado));

                if (strcmp(tipo, "STATUS") == 0) {
                    strncpy(especie.status, dado, sizeof(especie.status) - 1);
                    especie.status[sizeof(especie.status) - 1] = '\0';  // Garantir terminação
                } else if (strcmp(tipo, "HUMAN IMPACT") == 0) {
                    especie.impacto_humano = atoi(dado);
                } else if (strcmp(tipo, "POPULATION") == 0) {
                    especie.populacao = atoi(dado);
                } else {
                    printf("Tipo de informação inválido\n");
                    continue;
                }

                fwrite(&especie, sizeof(Registro), 1, file);
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Espécie não encontrada\n");
    }

    fclose(file);
}

int main() {
    const char *nomeArquivo = "especies.bin";

    // Testa a função de registrar espécies
    int num;
    printf("Digite o número de espécies a serem registradas: ");
    scanf("%d", &num);
    getchar();  // Limpa o buffer do teclado após scanf
    registrarEspecies(nomeArquivo, num);

    // Testa a função para exibir o conteúdo do arquivo binário
    exibirEspecies(nomeArquivo);

    // Testa a função para buscar uma espécie pelo RRN
    int rrn;
    printf("Digite o RRN da espécie a ser buscada: ");
    scanf("%d", &rrn);
}