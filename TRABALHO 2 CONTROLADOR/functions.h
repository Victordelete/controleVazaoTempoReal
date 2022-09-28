#ifndef functions
#define functions

//classe utilizada na leitura de um sensor
class grandeza{
    public:
        float valor; //utilizado para guardar o valor de leitura
        int tempoLeit; //utilizado para manejo do tempo de leitura
        bool estado; //utilizado para determinar se o estado da leitura � preocupante
};

//classe utilizada na caracterização dos tanques
class tanqueObjeto{
    public:
        //grandezas associadas a cada tanque
        grandeza sensorPressao;
        grandeza sensorVazao;
        grandeza sensorTemperatura;
        grandeza sensorAltura;

        //grandezas associadas ao controle da vazao. 
        float preenAnter = 100;
        float preenAtual = 100; //os tanques iniciam completos
};

class controlProper{
    public:
        //valores iniciais
        float consumo1 = 1.0;
        float consumo2 = 1.0;

        float vazao1 = 1.0;
        float vazao2 = 1.0;

        float delTempo = 1.0;
        float ganho = 1.2; //ganho para o controle proporcional
};

//fun��o utilizada para realiza��o do controle PI da vaz�o de controle
controlProper atuControleVazao(controlProper contStatus ,tanqueObjeto tanque1, tanqueObjeto tanque2, tanqueObjeto tanque3);

//funcao que atualiza os dados de altura
tanqueObjeto atuAltura(controlProper contStatus, tanqueObjeto tanque, int idTanque);

//fun��o utilizada para leitura auxiliar de press�o do sistema
grandeza atuSensorPressao(grandeza valor);

//fun��o utilizada para leitura auxiliar de vazao do sistema
grandeza atuSensorVazao(grandeza valor);

//fun��o utilizada para leitura auxiliar de temperatura do sistema
grandeza atuSensorTemperatura(grandeza valor);

//fun��o utilizada para leitura auxiliar de altura do sistema
grandeza atuSensorAltura(grandeza valor);

//fun��o que an�lisa os estados das interrup��es do sistema
bool analizaInterrupcoes( float interrupcao_tempo, float inicio_geral);

//fun��o que realiza um sleep de tempo recebido
void funcSleep(int temp_Sleep);

//fun��o que gera a randomiza��o dos processos de leitura
int randomGen(int lim_inf, int lim_sup);

//fun��o imprime o tempo passado
void tempo_passado(float inicio_geral);


#endif // functions
