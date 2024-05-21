#ifndef SISTEMA_HPP
#define SISTAMA_HPP
#include "processo.hpp"
#include <queue>
#include <vector>
class Sistema{
    public:
        vector<Processo> processos;
        vector<Processo> suspeitos;
        vector<Processo> corretos;
        vector<Processo> falhos;
        Sistema();
        Sistema(int num_processos);
        void valida_consenso();
        void oraculo();
        void print_processos();
        void print_suspeitos();
        void print_falhos();
};


#endif //SISTEMA_HPP