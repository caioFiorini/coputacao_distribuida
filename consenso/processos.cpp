#include "processo.hpp"

Processo::Processo()
{
    srand(time(0));
    this->status = -1;
    //Irá gerar valores entre 0 e 1;
    this->consenso = static_cast<int> (rand()/RAND_MAX);
    this->timeStamp = 0;
}

Processo::Processo(int status, int consenso, int timeStamp)
{
    this->status = -1;
    this->consenso = -1;
    this->timeStamp = 0;
}