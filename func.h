#ifndef FUNC_H
#define FUNC_H

typedef struct {
    int especieID;
    char nome[41];
    char nome_cientifico[61];
    int populacao;
    char status[9];
    float localizacao[2];  // Coordenadas em x e y
    int impacto_humano;
} Registro;

// Função para ler uma linha do stdin e remover o '\n' no final
void readline(char* string, int tamanho);

// Função para registrar espécies em um arquivo binário
void registrarEspecies(const char *nomearquivo, int num);

// Função para exibir todas as espécies registradas em um arquivo binário
void exibirEspecies(const char *nomearquivo);

// Função para buscar uma espécie pelo RRN (registro relativo no arquivo)
void buscarEspecie(const char *nomearquivo, int rrn);

// Função para atualizar informações de uma espécie específica
void atualizarInformacoes(const char *nomearquivo, int id, int numInfo);

// Função para mostrar o conteúdo binário na tela
void binarioNaTela(const char* nomeArquivoBinario);

#endif
