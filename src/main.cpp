#include <iostream>
#include <string>
#include <sstream>
#include "grafo.h"

using namespace std;

int main()
{
    int qtd_CD, qtd_PV, incremento_temperatura;

    string linha;
    getline(cin, linha);         // Lê a primeira linha da entrada e armazena em 'linha'.
    istringstream stream(linha); // Cria um objeto da classe istringstream e passa como parâmetro a linha.

    // Atribui os valores das entradas às variáveis:
    (stream >> qtd_CD);
    (stream >> qtd_PV);
    (stream >> incremento_temperatura);

    Grafo g(qtd_CD, qtd_PV, incremento_temperatura); // Instancia um objeto do tipo "Grafo".

    g.insereLigacoesImediatasCDs(); // Lê as ligações imediatas dos CDs.
    g.insereLigacoesImediatasPVs(); // Lê as ligações imediatas dos PVs.
    g.inicializaVisitados();
    g.navegaPeloGrafo();
    g.imprimeResultado(); // Imprime a saída do tp.

    return 0;
}