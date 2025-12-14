#ifndef PROCESSO_H
#define PROCESSO_H
#include <iostream>
#include <vector>

struct Processo {
    int pid;
    int tempo_chegada;
    int prioridade;
    int tempo_restante;
};

std::vector<Processo> gerarProcessos(int nProc) {

char trashChar;

std::vector<Processo> processos;

for (int i=0; i < nProc; i++) {
    Processo* temp = new Processo;

    std::cin >> temp->pid;
    std::cin >> trashChar;
    std::cin >> temp->tempo_chegada;
    std::cin >> trashChar;
    std::cin >> temp->prioridade;
    std::cin >> trashChar;
    std::cin >> temp->tempo_restante;

    processos.push_back(*temp);
    delete temp;
}

return processos;
}
#endif