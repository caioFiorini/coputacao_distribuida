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
  int testado_por;
  float tempo;
  int status;
  /* vari�veis locais do processo s�o declaradas aqui */
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
      j;

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
    // printf("fa_name = %s, processo[%d].id = %d\n", fa_name, i, processo[i].id);
  } /* end for */

  /*------ Incializa status dos processos --------*/
  // como estamos simulando vou deixar que o status dos processos seja escolhido por quem quer testar;

  for (i = 0; i < N; i++)
  {
    
    // status = 0 (correto)
    // status != 0 (falho)
    if(i == 1)
      processo[i].status = 1;
    else  
      processo[i].status = 0;

  } /* end for */


  /*----- vamos escalonar os eventos iniciais -----*/

  for (i = 0; i < N; i++)
  {
    schedule(test, 30.0+(i*2), i);
  }
  // schedule(fault, 31.0, 1);
  // schedule(recovery, 61.0, 1);

  /*----- agora vem o loop principal do simulador -----*/
  j = 1;
  while (time() < 40.0)
  {
    cause(&event, &token);
    // printf("%d",token);
    token_analise = token;
    switch (event)
    {
    case test:
      printf("processo %d, status: %d\n", token, processo[token].status);
      if (processo[token].status != 0)
        break; // processo falho não testa!
      else 
        while ((token_analise < N-1) && (processo[token_analise+j].status != 0)){
          token_analise = token_analise+j;
          j++;
        }
        printf("1 while %d\n", token_analise);
        j = 1; // reset da variável j;
        if(token == token_analise){
          token_analise = token_analise -1;
          while ((token_analise > 0) && (processo[token_analise -j].status == 0)){
            token_analise = token_analise-j;
            j++;
          }
          j = 1; // reset da variável j;
        }
        if(token == 0){
          while ((N_reverso > 0) && (processo[N_reverso -j].status == 0)){
            N_reverso = N_reverso-j;
            j++;
          }
          j = 1;
          processo[token].testado_por = processo[N_reverso].id;
          processo[token].tempo = time();
          printf("processo %d testado por %d, no tempo %5.1f\n", token, N_reverso, processo[token].tempo);
        }else{
          processo[token_analise].testado_por = processo[token].id;
          processo[token_analise].tempo = time();
          printf("processo %d testado por %d, no tempo %5.1f\n", token_analise, token, processo[token_analise].tempo);
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
  }   /* end while */
} /* end tempo.c */
