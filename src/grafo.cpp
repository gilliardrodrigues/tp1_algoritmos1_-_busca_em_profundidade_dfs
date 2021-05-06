#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "grafo.h"

using namespace std;

Grafo::Grafo(int qtd_CD, int qtd_PV, int incremento_temperatura) // Construtor.
{
    this->qtd_CD = qtd_CD;
    this->qtd_PV = qtd_PV;
    num_vertices = qtd_CD + qtd_PV; // Calcula o nº de vértices do grafo.
    num_viagens_caminhao = calculaViagens(incremento_temperatura);
    PVrepetido = 0;
    adj = new list<int>[num_vertices]; // Constrói o array de listas.
    visitados = new int[qtd_PV];       // Constrói o array de PV's visitados.
}

void Grafo::adicionaAresta(int v, int w) // Adiciona uma aresta no grafo.
{
    adj[v].push_back(w); // Adiciona w à lista de vértices adjacentes a v.
}

void Grafo::insereLigacoesImediatasCDs() // Lê as C linhas contendo as ligações imediatas de cada CD.
{
    int ligacao_imediata_CD;
    string linha;
    for (int i = 0; i < qtd_CD; i++)
    {
        getline(cin, linha);                                              // Lê da entrada e armazena em 'linha'.
        istringstream stream(linha);                                      // Cria um objeto da classe istringstream e passa como parâmetro a linha.
        while (stream >> ligacao_imediata_CD && ligacao_imediata_CD != 0) // Enquanto houver extração de 'stream' para 'ligacao_imediata_CD' e nenhuma for 0.
            adicionaAresta(i, ligacao_imediata_CD);                       // Adiciona a ligação imediata do i-ésimo CD em sua lista de adjacência.
    }
}

void Grafo::insereLigacoesImediatasPVs() // Lê as P linhas contendo as ligações imediatas de cada PV.
{
    int ligacao_imediata_PV;
    string linha;
    for (int i = qtd_CD; i < num_vertices; i++)
    {
        getline(cin, linha);                                              // Lê da entrada e armazena em 'linha'.
        istringstream stream(linha);                                      // Cria um objeto da classe istringstream e passa como parâmetro a linha.
        while (stream >> ligacao_imediata_PV && ligacao_imediata_PV != 0) // Enquanto houver extração de 'stream' para 'ligacao_imediata_CD' e nenhuma for 0.
            adicionaAresta(i, ligacao_imediata_PV);                       // Adiciona a ligação imediata do PV em sua lista de adjacência.
    }
}

int Grafo::calculaViagens(int incremento_temperatura) // Calcula o nº de viagens que um caminhão pode fazer em função do incremento da temperatura.
{
    if (incremento_temperatura == 0) // Caso não haja incremento na temperatura, o algoritmo vai percorrer todos os PVs.
        return qtd_PV;
    return (30 / incremento_temperatura); // Fórmula apresentadada na especificação do tp.
}

void Grafo::inicializaVisitados() // Inicializa o vetor "visitados".
{
    for (int i = 0; i < qtd_PV; i++)
        visitados[i] = 0; // Inicialmente nenhum PV foi visitado.
}

void Grafo::navegaPeloGrafo() // Chama a DFS modificada para os PV's vizinhos de cada CD.
{
    for (int i = 0; i < qtd_CD; i++)                             // Itera nas posições de adj que contém os CD's.
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) // Itera nas listas de adjacências de cada posição do array.
            DFSmodificada(*it, 1);                               // Chama a DFS modificada, passando como parâmetro o vértice em questão e um valor inicial pro contador de distância.
}

void Grafo::DFSmodificada(int v, int distancia) // Busca em profundidade modificada conforme os interesses do tp.
{   // Legenda:
    // "visitados[v - 1] = 0" significa que v ainda não foi visitado.
    // "visitados[v - 1] = 1" significa que v foi visitado.
    // "visitados[v - 1] = 2" significa que v e todos os seus vizinhos já foram visitados.
    // o cálculo "qtd_CD + v - 1" é feito para garantir que o método trabalhe com o PV certo (considerando que CD's e PV's estão no mesmo array de listas).

    if (visitados[v - 1] == 1) // Se o posto de vacinação v já foi visitado, atribui o valor 1 para a variável PVrepetido.
        PVrepetido = 1;

    if (visitados[v - 1] == 2) // Se v já não é mais possível percorrer esse caminho, retorna.
        return;
    if (distancia > num_viagens_caminhao) // Se já não é possível viajar mais com o caminhão devido ao limite, retorna.
        return;
    visitados[v - 1] = 1;                                                              // Marca v como visitado.
    for (auto it = adj[qtd_CD + v - 1].begin(); it != adj[qtd_CD + v - 1].end(); it++) // Chama recursivamente a DFS para os PV's
    {
        DFSmodificada(*it, distancia + 1);
    }
    visitados[v - 1] = 2; // Encerra o caminho
}

void Grafo::imprimeResultado() // Imprime a saída do tp.
{
    int contador_visitados = 0;
    for (int i = 0; i < qtd_PV; i++) // Contabiliza os PV's visitados.
    {
        if (visitados[i])
        {
            contador_visitados++;
        }
    }

    cout << contador_visitados << endl; // Imprime o nº de PV's visitados.

    if (!contador_visitados) // Se nenhum PV foi visitado, imprime "*".
    {
        cout << "*" << endl;
    }
    else
    {
        for (int i = 0; i < qtd_PV; i++) // Imprime os PV's visitados.
        {
            if (visitados[i] > 0)
            {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }

    cout << PVrepetido << endl; // Imprime 1 caso haja um ciclo ou 0 caso contrário.
}