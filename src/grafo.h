#ifndef GRAFO_H
#define GRAFO_H
#include <list>

class Grafo
{
public:
    Grafo(int qtd_CD, int qtd_PV, int incremento_temperatura); // Construtor.
    void adicionaAresta(int v, int w);                         // Adiciona uma aresta no grafo.
    void insereLigacoesImediatasCDs();                         // Lê as C linhas contendo as ligações imediatas de cada CD.
    void insereLigacoesImediatasPVs();                         // Lê as P linhas contendo as ligações imediatas de cada PV.
    int calculaViagens(int incremento_temperatura);            // Calcula o nº de viagens que um caminhão pode fazer em função do incremento da temperatura.
    void inicializaVisitados();                                // Inicializa o vetor "visitados".
    void navegaPeloGrafo();                                    // Navega pelo grafo.
    void DFSmodificada(int v, int distancia);                  // Busca em profundidade modificada conforme os interesses do tp.
    void imprimeResultado();                                   // Imprime a saída do tp.
private:
    int *visitados;      // Ponteiro para um array de PV's visitados.
    std::list<int> *adj; // Ponteiro para um array contendo as listas de adjacências.
    int num_vertices;
    int qtd_CD;
    int qtd_PV;
    int incremento_temperatura;
    int num_viagens_caminhao;
    int PVrepetido;
};

#endif //GRAFO_H