#include "processo.hpp"

Processo::Processo()
{
    srand(time(0));
    // 0 -> correto
    // 1 -> falho
    this->id = -1;
    this->status = static_cast<int> ((rand()/static_cast<double>(RAND_MAX)) * 2);
    //Irá gerar valores entre 0 e 1;
    this->consenso = static_cast<int> ((rand()/static_cast<double>(RAND_MAX)) * 2);
    this->timeStamp = 0;
}
