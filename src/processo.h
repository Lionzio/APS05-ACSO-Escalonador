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

using namespace std;

std::vector<Processo> gerarProcessos(int nProc) {

char trashChar;

std::vector<Processo> processos;

for (int i; i < nProc; i++) {
    Processo* temp = new Processo();

    cin >> temp->pid;
    cin >> trashChar;
    cin >> temp->tempo_chegada;
    cin >> trashChar;
    cin >> temp->prioridade;
    cin >> trashChar;
    cin >> temp->tempo_restante;

    processos.push_back(*temp);
    delete temp;
}

return processos;
}
#endif