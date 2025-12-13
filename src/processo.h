#ifndef PROCESSO_H
#define PROCESSO_H
#include <iostream>
#include <vector>


struct Processo {
    int pid;
    int tempo_restante;
    int prioridade;
};

using namespace std;

std::vector<std::vector<int>> gerarProcessos(int nProc) {

std::vector<std::vector<int>> processos;

int ID;
int tempChegada;
int prioridade;
int tempoCPU;

char trashChar;

for (int i = 0; i < nProc; i++) {
    cin >> ID;
    cin >> trashChar;
    cin >> tempChegada;
    cin >> trashChar;
    cin >> prioridade;
    cin >> trashChar;
    cin >> tempoCPU;

    processos.push_back({ID, tempChegada, prioridade, tempoCPU});
}

//o vector guarda os processos -> [1,2,3,4...,nProc] em ordem de entrada
//dentro de cada processo há um vector que guarda ID, tempChegada...sequencialmente

return processos;
}
#endif