#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int especieID;
    char nome[41];
    char nome_cientifico[61];  
    int populacao;
    char status[9];
    float localizacao_x;        
    float localizacao_y;
    int impacto_humano;
} Registro;


void readline(char* string, int tamanho) {
    fgets(string, tamanho, stdin);  // Lê uma linha com limite de tamanho
    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';  // Remove o caractere de nova linha
    }
}


void registrarEspecie(const char *arquivo) {
    FILE *file = fopen(arquivo, "ab");  // "ab" abre o arquivo para escrita em modo binário no final (append)
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    Registro especie;  
    
   
    printf("Digite o ID da espécie: ");
    scanf("%d", &especie.especieID);
    getchar();  // Limpa o buffer do teclado após scanf

    readline(especie.nome, 41); 
   
    readline(especie.nome_cientifico, 61);

    scanf("%d", &especie.populacao);

    getchar();  // Limpa o buffer do teclado após scanf
    readline(especie.status, 9);

    scanf("%f", &especie.localizacao_x);

    scanf("%f", &especie.localizacao_y);

    scanf("%d", &especie.impacto_humano);

    // Grava o registro no arquivo binário
    fwrite(&especie, sizeof(Registro), 1, file);

    fclose(file);
    printf("Espécie registrada com sucesso!\n");
}

void binarioNaTela(char* nomeArquivoBinario) {
    unsigned long i, cs;
    unsigned char* mb;
    size_t fl;
    FILE* fs;

    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA: não foi possível abrir o arquivo que me passou para leitura.\n");
        return;
    }

    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);  // volta para início do arquivo

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

int main() {
    const char *nomeArquivo = "especies.bin";

    // Testa a função de registrar uma espécie
    registrarEspecie(nomeArquivo);

    // Testa a função para exibir o conteúdo do arquivo binário
    binarioNaTela(nomeArquivo);

    return 0;
}
