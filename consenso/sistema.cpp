#include <sistema.hpp>

Sistema::Sistema(){} //construtor padrão

Sistema::Sistema(int num_processos){
    Processo p[num_processos];
    for(int i = 0; i < num_processos; i++){
        p[i] = Processo();
        processos.push_back(p[i]);
    }
}
int Sistema::define_status(int processo, int novo_status){
    processos[processo-1].status = novo_status;
}
void Sistema::consenso(){
    for (int i = 0; i < processos.size(); i++)
    {
        if(processos[i].consenso == 0){
            suspeitos.push_back(processos[i]);
        }else{
            corretos.push_back(processos[i]);
        } 
    }
}

void Sistema::oraculo(){
    for (int i = 0; i < suspeitos.size(); i++)
    {   
        if(suspeitos[i].status == -1){
            falhos.push_back(suspeitos[i]);
        }
    }
}