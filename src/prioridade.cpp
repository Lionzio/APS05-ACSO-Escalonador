#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include "processo.h"

// definição de infinito (para ajudar na busca)
#define INF 9999999

// função auxiliar pra dizer se o processo já terminou
bool estaConcluido(const Processo& p) {
    return p.tempo_restante <= 0;
}

/*
Implementação do Escalonador de Prioridade (Preemptivo)
Critérios:
1. Maior valor de prioridade
2. Desempate: Menor tempo_chegada (FCFS)
3. Preempção: Verifica a cada unidade de tempo se há alguém mais prioritário.
*/
void escalonadorPrioridade(std::vector<Processo> processos, int tTroca) {

    std::ofstream saidaPrioridade;
    saidaPrioridade.open("Saida_Prioridade.txt");

    int tempo_atual = 0;
    int processos_finalizados = 0;
    int n = processos.size();

    int trocas_contexto = 0;
    int tempo_total_trocas = 0;
    double soma_tempo_retorno = 0;

    // ponteiro para o último processo que executou 
    int pid_ultimo_executado = -1;  // -1 singifica que a CPU tava ociosa ou é o início

    while (processos_finalizados < n) {
        int indice_escolhido = -1;
        int maior_prioridade = -1; 
        int menor_chegada = INF;

        // selecionar o próximo processo da fila de prontos
        for (int i = 0; i < n; ++i) {
            // o processo deve ter chegado && não ter terminado
            if (processos[i].tempo_chegada <= tempo_atual && !estaConcluido(processos[i])) {
                // seleção por maior prioridade
                if (processos[i].prioridade > maior_prioridade) {
                    maior_prioridade = processos[i].prioridade;
                    menor_chegada = processos[i].tempo_chegada;
                    indice_escolhido = i;
                } 
                // desempate por menor tempo de chegada
                else if (processos[i].prioridade == maior_prioridade) {
                    if (processos[i].tempo_chegada < menor_chegada) {
                        menor_chegada = processos[i].tempo_chegada;
                        indice_escolhido = i;
                    }
                }
            }
        }

        // processar a escolha
        if (indice_escolhido != -1) {
            // verifica se teve troca de contexto -> havia alguém executando antes (pid != -1) e o escolhido é diferente do anterior
            if (pid_ultimo_executado != -1 && pid_ultimo_executado != processos[indice_escolhido].pid) {
                trocas_contexto++;
                tempo_total_trocas += tTroca;
                
                // avança o tempo por conta da troca (overhead), nenhum processo executa "trabalho útil"
                saidaPrioridade << "Escalonador executa em " << tempo_atual << " ms" << std::endl;
                tempo_atual += tTroca; 
            }

            // executa o processo por 1 unidade de tempo 
            Processo& p = processos[indice_escolhido];
            saidaPrioridade << "Processo: " << indice_escolhido << " executa em " << tempo_atual << " ms" << std::endl;
            p.tempo_restante--;
            tempo_atual++;
            pid_ultimo_executado = p.pid;

            // verifica se o processo terminou nesta unidade de tempo
            if (p.tempo_restante == 0) {
                processos_finalizados++;
                // tempo de retorno = tempo final - tempo chegada
                int turnaround = tempo_atual - p.tempo_chegada;
                p.tempo_retorno = turnaround;
                soma_tempo_retorno += turnaround;
            }

        } else {
            // CPU ociosa (Nenhum processo chegou ainda)
            tempo_atual++;
            saidaPrioridade << "CPU ociosa em " << tempo_atual << " ms" << std::endl;
            pid_ultimo_executado = -1; // Reseta para não contar troca de contexto ao voltar
        }
    }

    saidaPrioridade << "\n" << std::endl;
    saidaPrioridade << "Relatório Final" << std::endl;
    saidaPrioridade << "Tempo Total: " << tempo_atual - 1 << " ms" << std::endl;
    saidaPrioridade << "Overhead: " << std::fixed << std::setprecision(2) << ((float)tempo_total_trocas/(float)tempo_atual)*100 << " %" << std::endl;
    saidaPrioridade << "Número de Trocas de Contexto: " << trocas_contexto << std::endl;
    for (int j=0; j < processos.size(); j++) {
        saidaPrioridade << "Tempo de retorno do Processo " << processos[j].pid << " = " << processos[j].tempo_retorno << " ms" << std::endl;
    }

    return;
}
