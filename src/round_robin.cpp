#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include "processo.h"

void escalonadorRoundRobin(
    std::vector<Processo>& processos,
    int quantum,
    int tTroca
) {
    std::queue<Processo*> fila;
    int tempo_atual = 0;

    // inicializaando a fila de prontos
    for (auto& p : processos) {
        fila.push(&p);
    }

    while (!fila.empty()) {
        Processo* atual = fila.front();
        fila.pop();
        
        // executando o processo pelo tempo min
        int tempo_exec = std::min(quantum, atual->tempo_restante);

        std::cout << "Tempo " << tempo_atual
                  << ": Processo " << atual->pid
                  << " executa por " << tempo_exec << " ms\n";

        tempo_atual += tempo_exec;
        atual->tempo_restante -= tempo_exec;

        if (atual->tempo_restante > 0) {
            fila.push(atual); // volta para o fim
        }

        // ttroca de contexto se ainda houver processos
        if (!fila.empty()) {
            tempo_atual += tTroca;
        }
    }
}