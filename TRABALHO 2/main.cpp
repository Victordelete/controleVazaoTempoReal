/*Trabalho 1: Sistemas de Tempo Real
    Aplica��o desenvolvida para o trabalho 2 de Sistemas de Tempo Real.

    Programa implementa o controle um processo de vaz�o para um tanque fechado,
    levando em considera��o o controlador de vaz�o, leitura de sensor de press�o,
    sensor de algura do l�quido, sensor de composi��o da mistura, e sensor de vaz�o.
    Assim como um processo n�o periodico de acionamento de seguran�a do processo.

    Alunos:
        Victor Hugo Marques Vieira - 150047649.
        Daniel

    Desenvolvimento em C/C++ utilizando as bibliotecas nativas
    habilitando funções de compilação para C++ 2011 ISO C Language.
*/

#include "functions.cpp"

#include <ctime>
#include <iostream>
using namespace std;

int main(){
    //Inicio os tanques
    tanqueObjeto tanque1;
    tanqueObjeto tanque2;
    tanqueObjeto tanque3;
    tanque1.atual = 100; tanque1.anter = 100;
    tanque2.atual = 0; tanque2.anter = 0;
    tanque3.atual = 100; tanque3.anter = 100;

    float consumo1 = 1.0;
    float consumo2 = 1.0;

    float vazao1 = 1.0;
    float vazao2 = 1.0;

    float delTempo = 1.0;
    float ganho = 1.2;

    float media = 100.0;

    unsigned seed = time(NULL);
    srand(seed);
    float random;
    int i = 0;
    
    while(i<=50){
        random = 0.01*float(rand()%100);
        consumo1 = random;

        random = 0.01*float(rand()%100);
        consumo2 = random; 

        media = (tanque1.atual + tanque2.atual + tanque3.atual) / 3;
        vazao1 = ganho*(tanque1.atual-media);
        vazao2 = ganho*(tanque3.atual-media);

        tanque1.anter = tanque1.atual;
        tanque2.anter = tanque2.atual;
        tanque3.anter = tanque3.atual;

        tanque1.atual = tanque1.anter - consumo1*delTempo - vazao1*delTempo;
        tanque2.atual = tanque2.anter + vazao1*delTempo + vazao2*delTempo;
        tanque3.atual = tanque3.anter - consumo2*delTempo - vazao2*delTempo;

        cout<<"Iteracao: "<<i<<"\n";

        cout<<"Consumo 1: "<<consumo1<<"\n";
        cout<<"Consumo 2: "<<consumo2<<"\n";

        cout<<"Vazao 1: "<<vazao1<<"\n";
        cout<<"Vazao 2: "<<vazao2<<"\n";

        cout<<"Tanque 1: "<<tanque1.atual<<"\n";
        cout<<"Tanque 2: "<<tanque2.atual<<"\n";
        cout<<"Tanque 3: "<<tanque3.atual<<"\n\n";
        i++;
    }


}
