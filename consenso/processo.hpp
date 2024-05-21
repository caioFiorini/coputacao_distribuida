#ifndef PROCESSO_HPP
#define PROCESSO_HPP
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

class Processo
{
public:
    Processo();
    Processo(int status, int consenso, int timeStamp);
    int id;
    int status; // 0 C, 1 F, -1 NI
    int consenso; //rand(0,1)
    int timeStamp; //se precisar, verificação de erros no futuro
};

#endif //PROCESSO_HPP