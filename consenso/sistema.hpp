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
        int define_status(int processo, int novo_status);
        void consenso();
        void oraculo();
};


#endif //SISTEMA_HPP