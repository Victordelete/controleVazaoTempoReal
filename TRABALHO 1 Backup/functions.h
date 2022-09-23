#ifndef functions
#define functions

//classe utilizada na leitura de um sensor
class grandeza{
    public:
        float valor; //utilizado para guardar o valor de leitura
        int tempoLeit; //utilizado para manejo do tempo de leitura
        bool estado; //utilizado para determinar se o estado da leitura � preocupante
};

//fun��o utilizada para realiza��o do controle PI da vaz�o de controle
grandeza atuControleVazao(grandeza valor);

//fun��o utilizada para leitura auxiliar de press�o do sistema
grandeza atuSensorPressao(grandeza valor);

//fun��o utilizada para leitura auxiliar de vazao do sistema
grandeza atuSensorVazao(grandeza valor);

//fun��o utilizada para leitura auxiliar de temperatura do sistema
grandeza atuSensorTemperatura(grandeza valor);

//fun��o utilizada para leitura auxiliar de altura do sistema
grandeza atuSensorAltura(grandeza valor);

//fun��o que an�lisa os estados das interrup��es do sistema
bool analizaInterrupcoes(char interrupcao_tipo, float interrupcao_tempo, float inicio_geral);

//fun��o que realiza um sleep de tempo recebido
void funcSleep(int temp_Sleep);

//fun��o que gera a randomiza��o dos processos de leitura
int randomGen(int lim_inf, int lim_sup);

//fun��o imprime o tempo passado
void tempo_passado(float inicio_geral);

#endif // functions
