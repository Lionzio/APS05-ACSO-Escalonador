#include <iostream>
#include <vector>

#include "processo.h"
#include "round_robin.cpp"

using namespace std;

int nProc;
int quantum;
int tTroca;

char trashChar;

int main() {
    //entrada dos dados iniciais
    std::cin >> nProc;
    std::cin >> trashChar;
    std::cin >> quantum;
    std::cin >> trashChar;
    std::cin >> tTroca;

    //geração de processos
    std::vector<Processo> processos;
    processos = gerarProcessos(nProc);

    //roun robin
    escalonadorRoundRobin(processos, quantum, tTroca);

    return 0;

}