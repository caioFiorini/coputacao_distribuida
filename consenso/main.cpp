#include <sistema.hpp>

int main(){

    Sistema sis = Sistema(5);
    sis.print_processos();
    // No nosso exemplo os processos recebem o consenso de forma aleatória
    // 0 -> consenso que prevalece
    // 1 -> consenso suspeito
    sis.valida_consenso();
    // chamamos o oraculo para verificar quais processos são realmente falhos,
    // que também no nosso caso é aleatório
    // 0 -> correto
    // 1 -> falho
    sis.oraculo();
    // agora mostramos a nossa lista de suspeitos e a nossa lista de falhos
    sis.print_suspeitos();
    sis.print_falhos();     

    return 0;
}