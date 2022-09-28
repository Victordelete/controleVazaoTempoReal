/*Trabalho 1: Sistemas de Tempo Real


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

//Definições de constantes globais utilizadas no programa
int temp_ciclo = 1020 ; //tempo de cada ciclo
clock_t temp_ini, temp_fim;
float inicio_geral; //guardar o inicio geral do programa

//Função que análisa o tempo necessário para o sincronismo
void anaSleep();
//Função que realiza um sleep de tempo recebido
void funcSleep(float temp_Sleep);

//inicio do programa
int main(int argc, char *argv[]){

    /*
    //Abertura de arquivo
    if(argc != 3) {
        cout<<"Poucos argumentos.\n";
        return -1;
    }

    //Atribuição das chamadas da função
    char interrupcao_tipo = argv[1][0];
    float interrupcao_tempo = strtof(argv[2], nullptr) ;

    //caso o argumento recebido seja diferente do tipo T ou P não é um teste válido
    if(interrupcao_tipo != 'T' && interrupcao_tipo != 'P'){
        cout<<"Tipo de teste '"<<interrupcao_tipo<<"' nao suportado.\n\n";
        return -1;
    }
    */

    float interrupcao_tempo = 10.0 ;

    //auxiliar para geração dos testes aleatório
    unsigned seed = time(NULL);
    srand(seed);

    //Inicialização dos objetos que herdario os valores das funções
    tanqueObjeto tanque1;
    tanqueObjeto tanque2;
    tanqueObjeto tanque3;

    controlProper contStatus;

    inicio_geral = float(clock());

    //loop infinito para o controle das funções periodicas
    while(true){
        ///PRIMEIRO CICLO
        //pego o tempo inicial do ciclo
        temp_ini = clock()-inicio_geral;
        tempo_passado( inicio_geral);
            //Controle vazao
            contStatus = atuControleVazao(contStatus, tanque1, tanque2, tanque3);
            tanque1 = atuAltura(contStatus, tanque1, 1);
            tanque2 = atuAltura(contStatus, tanque2, 2);
            tanque3 = atuAltura(contStatus, tanque3, 3);
            //cout<<contStatus.consumo1<<" "<<contStatus.consumo2<<" "<<tanque1.preenAtual<< " " <<tanque2.preenAtual<<" "<<tanque3.preenAtual<<"\n";
            //atualizo as funcoes do TANQUE 1
            tanque1.sensorPressao = atuSensorPressao(tanque1.sensorPressao);
                if(analizaInterrupcoes( interrupcao_tempo,  inicio_geral))
                        break;
            tanque1.sensorVazao = atuSensorVazao(tanque1.sensorVazao);
                if(analizaInterrupcoes( interrupcao_tempo,  inicio_geral))
                        break;

            //atualizo as funcoes do TANQUE 2
            tanque2.sensorPressao = atuSensorPressao(tanque2.sensorPressao);
                if(analizaInterrupcoes( interrupcao_tempo,  inicio_geral))
                        break;
            tanque2.sensorVazao = atuSensorVazao(tanque2.sensorVazao);
                if(analizaInterrupcoes( interrupcao_tempo,  inicio_geral))
                        break;

            //atualizo as funcoes do TANQUE 3
            tanque3.sensorPressao = atuSensorPressao(tanque3.sensorPressao);
                if(analizaInterrupcoes( interrupcao_tempo,  inicio_geral))
                        break;
            tanque3.sensorVazao = atuSensorVazao(tanque3.sensorVazao);
                if(analizaInterrupcoes( interrupcao_tempo,  inicio_geral))
                        break;


        //pego o tempo final do ciclo
        temp_fim = clock()-inicio_geral;
        anaSleep();//vejo qu�o longe do fim do ciclo para inicio do pr�ximo

        ///SEGUNDO CICLO
        //pego o tempo inicial do ciclo
        temp_ini = clock()-inicio_geral;
        tempo_passado(inicio_geral);
            //Controle vazao
            contStatus = atuControleVazao(contStatus, tanque1, tanque2, tanque3);
            tanque1 = atuAltura(contStatus, tanque1, 1);
            tanque2 = atuAltura(contStatus, tanque2, 2);
            tanque3 = atuAltura(contStatus, tanque3, 3);

            //atualizo as funcoes do TANQUE 1
            tanque1.sensorTemperatura = atuSensorTemperatura(tanque1.sensorTemperatura);
                if(analizaInterrupcoes( interrupcao_tempo, inicio_geral))
                        break;
            tanque1.sensorAltura = atuSensorAltura(tanque1.sensorAltura);
                if(analizaInterrupcoes( interrupcao_tempo, inicio_geral))
                        break;

            //atualizo as funcoes do TANQUE 2
            tanque2.sensorTemperatura = atuSensorTemperatura(tanque2.sensorTemperatura);
                if(analizaInterrupcoes( interrupcao_tempo, inicio_geral))
                        break;
            tanque2.sensorAltura = atuSensorAltura(tanque2.sensorAltura);
                if(analizaInterrupcoes( interrupcao_tempo, inicio_geral))
                        break;

            //atualizo as funcoes do TANQUE 3
            tanque3.sensorTemperatura = atuSensorTemperatura(tanque3.sensorTemperatura);
                if(analizaInterrupcoes( interrupcao_tempo, inicio_geral))
                        break;
            tanque3.sensorAltura = atuSensorAltura(tanque3.sensorAltura);
                if(analizaInterrupcoes( interrupcao_tempo, inicio_geral))
                        break;

        temp_fim = clock()-inicio_geral;
        anaSleep(); //vejo qu�o longe do fim do ciclo para inicio do pr�ximo
    }

    return 0;
}

//Funcao que analisa o tempo necess�rio para o sincronismo
void anaSleep(){
    //vejo o tempo necess�rio para atingir o per�odo do ciclo
    int temp_dif = temp_ciclo - (int(temp_fim) - int(temp_ini)); //ciclo de clock n�o convertido para segundos
    //pauso o sistema para atingir este tempo
    //testo para caso o ciclo tenha sido ultrapassado
    if(temp_dif>0){
        funcSleep(temp_dif);
    }
    return;
}
