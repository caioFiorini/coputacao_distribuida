#include <sistema.hpp>

Sistema::Sistema(){} //construtor padrão

Sistema::Sistema(int num_processos){
    Processo p[num_processos];
    for(int i = 0; i < num_processos; i++){
        p[i] = Processo();
        p[i].id = i;
        processos.push_back(p[i]);
    }
}

void Sistema::valida_consenso(){
    for (const auto& processo : processos) {
    if (processo.consenso == 1) {
        suspeitos.push_back(processo);
    } else {
        corretos.push_back(processo);
    }
}
}

void Sistema::oraculo(){
    for (const auto& suspeito : suspeitos) {
        if(suspeito.status == 1){
            falhos.push_back(suspeito);
        }
    }
}

void Sistema::print_processos(){
    for (const auto& processo : processos) {
        cout << "Processo: " << processo.id << endl;
        cout << "Status: " << processo.status << endl;
        cout << "Consenso: " << processo.consenso << endl; 
    }
}
void Sistema::print_suspeitos(){
    int i = 0;
    cout << "Lista de suspeitos" << endl;
    for (const auto& suspeito : suspeitos) {
        cout << "Processo: " << suspeito.id << endl;
        i++;
    }
}
void Sistema::print_falhos(){
    int i = 0;
    cout << "Processos falhos" << endl;
    for (const auto& falho : falhos) {
        cout << "Processo: " << falho.id << endl;
        i++;
    }
}