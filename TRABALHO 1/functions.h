#ifndef functions
#define functions

//classe utilizada na leitura de um sensor
class grandeza{
    public:
        float valor; //utilizado para guardar o valor de leitura
        int tempoLeit; //utilizado para manejo do tempo de leitura
        bool estado; //utilizado para determinar se o estado da leitura é preocupante
};

//função utilizada para realização do controle PI da vazão de controle
grandeza atuControleVazao(grandeza valor);

//função utilizada para leitura auxiliar de pressão do sistema
grandeza atuSensorPressao(grandeza valor);

//função utilizada para leitura auxiliar de vazao do sistema
grandeza atuSensorVazao(grandeza valor);

//função utilizada para leitura auxiliar de temperatura do sistema
grandeza atuSensorTemperatura(grandeza valor);

//função utilizada para leitura auxiliar de altura do sistema
grandeza atuSensorAltura(grandeza valor);

//função que análisa os estados das interrupções do sistema
bool analizaInterrupcoes(char interrupcao_tipo, float interrupcao_tempo, float inicio_geral);

//função que realiza um sleep de tempo recebido
void funcSleep(int temp_Sleep);

//função que gera a randomização dos processos de leitura
int randomGen(int lim_inf, int lim_sup);

//função imprime o tempo passado
void tempo_passado(float inicio_geral);

#endif // functions
