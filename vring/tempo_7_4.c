/* Disciplina Sistemas Distribu�dos
   Prof. Elias P. Duarte Jr.
   O primeiro programa de simula��o: tempo.c
   Cada processo simplesmente conta o tempo
   Esta atualiza��o: 29/11/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "smpl.h"

/* cada processo conta seu tempo */

/*---- aqui definimos os eventos ----*/
#define test 1
#define fault 2
#define recovery 3

/*---- declaramos agora o TipoProcesso ----*/
typedef struct
{
    int id; /* identificador de facility SMPL */

    /* vari�veis locais do processo s�o declaradas aqui */
    int testado_por;
    float tempo;
    int status;
    int *state;
} TipoProcesso;

TipoProcesso *processo;

int main(int argc, char *argv[])
{
    static int N, /* number of nodes is parameter */
        token,    /* node identifier, natural number */
        token_analise,
        event,
        r,
        i,
        N_reverso,
        j,
        tempo;

    static char fa_name[5];

    if (argc != 2)
    {
        puts("Uso correto: tempo <num-processos>");
        exit(1);
    }

    N = atoi(argv[1]);
    N_reverso = N;
    smpl(0, "Um Exemplo de Simula��o");
    reset();
    stream(1);

    /*----- inicializacao -----*/

    processo = (TipoProcesso *)malloc(sizeof(TipoProcesso) * N);

    for (i = 0; i < N; i++)
    {
        memset(fa_name, '\0', 5);
        sprintf(fa_name, "%d", i);
        processo[i].id = facility(fa_name, 1);
        processo[i].testado_por = -1;
        processo[i].tempo = 0.0;
        processo[i].status = -1;
        processo[i].state = (int *)malloc(sizeof(int) * N);
        for (int k = 0; k < N; k++)
        {
            processo[i].state[k] = processo->status;
        }
        // printf("processo[%d] = %d\n",processo[i].id);
    } /* end for */

    /*------ Incializa status dos processos --------*/
    // como estamos simulando vou deixar que o status dos processos seja escolhido por quem quer testar;

    
    for (i = 0; i < N; i++)
    {

        // status = 0 (correto)
        // status != 0 (falho)
        processo[i].status = 0;
        // printf("%d\n",processo[i].status);
    } /* end for */

    /*----- vamos escalonar os eventos iniciais -----*/

    for (i = 0; i < N; i++)
    {
        tempo = i * 2;
        schedule(test, 30.0 + tempo, i);
    }
    // schedule(fault, 31.0, 1);
    // schedule(recovery, 61.0, 1);

    /*----- agora vem o loop principal do simulador -----*/
    j = 1;
    while (time() < (30.0 + tempo))
    {
        cause(&event, &token);
        // printf("%d",token);
        token_analise = token - 1;
        switch (event)
        {
        case test:
            // printf("processo %d\n", token);
            if (processo[token].status != 0)
                break; // processo falho não testa!
            else if (token == 0)
            {
                while (N > j)
                {
                    if (processo[N_reverso - 1].status == 0)
                    {
                        processo[token].testado_por = processo[N_reverso - 1].id;
                        // printf("status do processo[N_reerso -1] %d\n", processo[N_reverso - 1].status);
                        processo[token].state[token] = processo[token].status;
                        for (int k = 0; k < N; k++)
                        {
                            // printf("Passei aqui\n");
                            // printf("0 Estado do processo[N_reverso - 1].[%d] = %d \n", k, processo[N_reverso-1].state[k]);
                            // printf("Estado do processo[token].[%d] = %d\n", k, processo[token].state[k]);
                            if (((processo[N_reverso-1].state[k] == -1) && (processo[token].state[k] == 0)) || 
                            ((processo[token].state[k] == -1) && (processo[N_reverso-1].state[k] == 0)))
                            {
                                processo[N_reverso-1].state[k] = processo[token].state[k];
                                // printf("01 Estado do processo[N_reverso - 1].[%d] = %d &&  Estado do processo[token].[%d] = %d\n", k, processo[N_reverso-1].state[k], k, processo[token].state[k]);
                            }
                            
                        }
                        
                        
                        printf("processo %d, testado por processo %d no tempo %5.1f\n", token, N_reverso - 1, time());
                        j = N;
                    }
                    else
                    {
                        N_reverso--;
                    }
                    j++;
                }
                j = 1;
            }
            
            else
            {
                while (j < N)
                {
                    // printf("entrei aqui");
                    if (processo[token_analise].status == 0)
                    {
                        // um processo testa o outro;
                        processo[token].testado_por = processo[token_analise].id;
                        
                        // atualiza o estado do processo;
                        processo[token].state[token] = processo[token].status;

                        for (int k = 0; k < N; k++)
                        {
                            // printf("Passei aqui2\n");
                            // printf("1 Estado do processo[token_analise].[%d] = %d\n", k, processo[token_analise].state[k]);
                            // printf("1 Estado do processo[token].[%d] = %d\n", k, processo[token].state[k]);
                            if (((processo[token_analise].state[k] == -1) && (processo[token].state[k] == 0)) || 
                            ((processo[token].state[k] == -1) && (processo[token_analise].state[k] == 0)))
                            {
                                processo[token_analise].state[k] = processo[token].state[k];
                                // printf("2 Estado do processo[N_reverso - 1].[%d] = %d &&  Estado do processo[token].[%d] = %d\n", k, processo[token_analise].state[k], k, processo[token].state[k]);
                            }
                            
                        }
                        
                        printf("processo %d, testado por processo %d no tempo %5.1f\n", token, token_analise, time());
                        j = N;
                    }
                    else
                    {
                        token_analise++;
                    }
                    j++;
                }
                j = 1;
            }

            schedule(test, 30.0, token);
            break;
        case fault:
            r = request(processo[token].id, token, 0);
            printf("o processo %d falhou no tempo %5.1f\n", token, time());
            break;
        case recovery:
            release(processo[token].id, token);
            schedule(test, 1.0, token);
            printf("o processo %d recuperou no tempo %5.1f\n", token, time());
            break;
        } /* end switch */

        printf("Vetor: State[ ");
        for (int k = 0; k < N; k++)
        {
            printf("%d ", processo[token].state[k]);
        }
        printf("]");
        printf("\n");

    } /* end while */

    free(processo->state);
    free(processo);

} /* end tempo.c */
