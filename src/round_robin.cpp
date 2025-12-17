#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "processo.h"

void escalonadorRoundRobin(
    std::vector<Processo> processos,
    int quantum,
    int tTroca
) {
    std::queue<Processo*> fila;
    int tempo_atual = 0;
    int qtd_troca = 0;
    int tempo_total_trocas = 0;

    std::ofstream saidaRound;
    saidaRound.open("Saida_Round.txt");

    // inicializaando a fila de prontos
    for (auto& p : processos) {
        fila.push(&p);
    }

    while (!fila.empty()) {
        Processo* atual = fila.front();
        fila.pop();
        
        // executando o processo pelo tempo min
        int tempo_exec = std::min(quantum, atual->tempo_restante);
        
        saidaRound << "Processo: " << atual->pid << " executa em " << tempo_atual << " ms" << std::endl;

        tempo_atual += tempo_exec;
        atual->tempo_restante -= tempo_exec;

        if (atual->tempo_restante > 0) {
            fila.push(atual); // volta para o fim
        }

        if (atual->tempo_restante == 0) {
            atual->tempo_retorno = tempo_atual - atual->tempo_chegada;
        }

        // ttroca de contexto se ainda houver processos
        if (!fila.empty()) {
            saidaRound << "Escalonador executa em " << tempo_atual << " ms" << std::endl;
            qtd_troca += 1;
            tempo_total_trocas += tTroca;
            tempo_atual += tTroca;
        }
    }

    saidaRound << "\n" << std::endl;
    saidaRound << "Relatório Final" << std::endl;
    saidaRound << "Tempo total: " << tempo_atual << std::endl;
    saidaRound << "Overhead: " << std::fixed << std::setprecision(2) << ((float)tempo_total_trocas/(float)tempo_atual)*100 << " %" << std::endl;
    saidaRound << "Número de Trocas de Contexto: " << qtd_troca << std::endl;
    for (int j=0; j < processos.size(); j++) {
        saidaRound << "Tempo de retorno do Processo " << processos[j].pid << " = " << processos[j].tempo_retorno << " ms" << std::endl;
    }

    return;
}