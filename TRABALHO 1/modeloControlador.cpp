/*Trabalho 1: Sistemas de Tempo Real
    Aplica��o desenvolvida para o trabalho de Sistemas de Tempo Real.

    Programa implementa o controle um processo de vaz�o para um tanque fechado,
    levando em considera��o o controlador de vaz�o, leitura de sensor de press�o,
    sensor de algura do l�quido, sensor de composi��o da mistura, e sensor de vaz�o.
    Assim como um processo n�o periodico de acionamento de seguran�a do processo.

    Aluno: Victor Hugo Marques Vieira.
    Matr�cula: 150047649.

    Desenvolvimento em C/C++ utilizando as bibliotecas nativas do CodeBlocks vers�o 17.12
    habilitando fun��es de compila��o para C++ 2011 ISO C Language.
*/

//Inclus�es necess�rias para o programa
#include "functions.cpp" //m�dulo das fun��es desenvolvidas

    //bibliotecas de tempo para o sistema
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
    using namespace std;

//defini��es de constantes globais utilizadas no programa
int temp_ciclo = 650 ; //tempo de cada ciclo
clock_t temp_ini, temp_fim;
float inicio_geral; //guardar o inicio geral do programa

//Fun��o que an�lisa o tempo necess�rio para o sincronismo
void anaSleep();
//fun��o que realiza um sleep de tempo recebido
void funcSleep(float temp_Sleep);

//inicio do programa
int main(int argc, char *argv[]){

    if(argc != 3) {
        cout<<"Poucos argumentos.\n";
        return -1;
    }

    //atribui��o das chamadas da fun��o
    char interrupcao_tipo = argv[1][0];
    float interrupcao_tempo = strtof(argv[2], nullptr) ;

    //caso o argumento recebido seja diferente do tipo T ou P n�o � um teste v�lido
    if(interrupcao_tipo != 'T' && interrupcao_tipo != 'P'){
        cout<<"Tipo de teste '"<<interrupcao_tipo<<"' nao suportado.\n\n";
        return -1;
    }

    //auxiliar para gera��o dos testes aleat�rios
    unsigned seed = time(NULL);
    srand(seed);

    //Inicializa��o dos objetos que herdar�o os valores das fun��es
    grandeza controleVazao;
    grandeza sensorPressao;
    grandeza sensorVazao;
    grandeza sensorTemperatura;
    grandeza sensorAltura;

    inicio_geral = float(clock());
    cout<<"inicio geral"<<inicio_geral<<"\n\n";
    //loop infinito para o controle das fun��es periodicas
    while(true){
        ///PRIMEIRO CICLO
        //pego o tempo inicial do ciclo
        temp_ini = clock()-inicio_geral;
        tempo_passado( inicio_geral);
            //atualizo as fun��es deste ciclo
            controleVazao = atuControleVazao(controleVazao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo,  inicio_geral))
                        break;
            sensorPressao = atuSensorPressao(sensorPressao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo,  inicio_geral))
                        break;
            sensorVazao = atuSensorVazao(sensorVazao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo,  inicio_geral))
                        break;
        //pego o tempo final do ciclo
        temp_fim = clock()-inicio_geral;
        anaSleep();//vejo qu�o longe do fim do ciclo para inicio do pr�ximo

        ///SEGUNDO CICLO
        //pego o tempo inicial do ciclo
        temp_ini = clock()-inicio_geral;
        tempo_passado(inicio_geral);
            controleVazao = atuControleVazao(controleVazao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo, inicio_geral))
                        break;
            sensorTemperatura = atuSensorTemperatura(sensorTemperatura);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo, inicio_geral))
                        break;
            sensorAltura = atuSensorAltura(sensorAltura);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo, inicio_geral))
                        break;
        temp_fim = clock()-inicio_geral;
        anaSleep(); //vejo qu�o longe do fim do ciclo para inicio do pr�ximo
    }

    return 0;
}

//Fun��o que an�lisa o tempo necess�rio para o sincronismo
void anaSleep(){
    //vejo o tempo necess�rio para atingir o per�odo do ciclo
    int temp_dif = temp_ciclo - (int(temp_fim) - int(temp_ini)); //ciclo de clock n�o convertido para segundos
    //pauso o sistema para atingir este tempo
    cout<<"Fim de ciclo: ";
    //testo para caso o ciclo tenha sido ultrapassado
    if(temp_dif>0){
        funcSleep(temp_dif);
    }
    cout<<"\n";
    return;
}
