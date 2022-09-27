/*Trabalho 1: Sistemas de Tempo Real
    Exportação do programa para microcontrolador com as limitações de tempo.


    Aluno: Victor Hugo Marques Vieira.
    Matrícula: 150047649. */

long randNumber;

///DEFINIÇÕES DE CLASSES
//CLASSE UTILIZADA NA CARACTERIZAÇÃO DA LEITURA DOS SENSORES
class grandeza {
  public:
    float valor; //utilizado para guardar o valor de leitura
    int tempoLeit; //utilizado para manejo do tempo de leitura
    bool estado; //utilizado para determinar se o estado da leitura � preocupante
};

//CLASSE UTILIZADA NA CARACTERIZAÇÃO DE TANQUES
class tanqueObjeto {
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

//CLASSE UTILIZADA NA RETENSÃO DOS DADOS DE CONTROLE
class controlProper {
  public:
    //valores iniciais
    float consumo1 = 1.0;
    float consumo2 = 1.0;

    float vazao1 = 1.0;
    float vazao2 = 1.0;

    float delTempo = 1.0;
    float ganho = 1.2; //ganho para o controle proporcional
};

//Definições de constantes globais utilizadas no programa
unsigned long temp_ciclo = 900 ; //tempo de cada ciclo

unsigned long temp_ini = millis();

unsigned long temp_dif = 0;

controlProper contStatus;

//Inicialização dos objetos que herdario os valores das funções
tanqueObjeto tanque1;
tanqueObjeto tanque2;
tanqueObjeto tanque3;

/////SETUP///////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

/////LOOP///////////////////////////////////////////////
void loop() {
    if(tanque1.preenAtual <= 0 || tanque2.preenAtual <= 0 || tanque3.preenAtual <= 0 ){
      delay(1000000000);
    }
    else{
      temp_ini = millis();
    
      ///PRIMEIRO CICLO
      //Controle vazao
      contStatus = atuControleVazao(contStatus, tanque1, tanque2, tanque3);
      tanque1 = atuAltura(contStatus, tanque1, 1);
      tanque2 = atuAltura(contStatus, tanque2, 2);
      tanque3 = atuAltura(contStatus, tanque3, 3);
                  analisaInterrucao();
    
      //atualizo as funcoes do TANQUE 1
      tanque1.sensorPressao = atuSensorPressao(tanque1.sensorPressao);
      tanque1.sensorVazao = atuSensorVazao(tanque1.sensorVazao);
                  analisaInterrucao();
    
      //atualizo as funcoes do TANQUE 2
      tanque2.sensorPressao = atuSensorPressao(tanque2.sensorPressao);
      tanque2.sensorVazao = atuSensorVazao(tanque2.sensorVazao);
                  analisaInterrucao();
    
      //atualizo as funcoes do TANQUE 3
      tanque3.sensorPressao = atuSensorPressao(tanque3.sensorPressao);
      tanque3.sensorVazao = atuSensorVazao(tanque3.sensorVazao);
                  analisaInterrucao();

      Serial.println("C1");
      Serial.println(tanque1.preenAtual);
      Serial.println(tanque2.preenAtual);
      Serial.println(tanque3.preenAtual);
      Serial.println(contStatus.vazao1);
      Serial.println(contStatus.vazao2);
      Serial.println(contStatus.consumo1);
      Serial.println(contStatus.consumo2);
      anaSleep(); //Analiso e imprimo as 
      Serial.println("\n");
    
      ///SEGUNDO CICLO
      temp_ini = millis();
      //Controle vazao
      contStatus = atuControleVazao(contStatus, tanque1, tanque2, tanque3);
      tanque1 = atuAltura(contStatus, tanque1, 1);
      tanque2 = atuAltura(contStatus, tanque2, 2);
      tanque3 = atuAltura(contStatus, tanque3, 3);
                  analisaInterrucao();
    
      //atualizo as funcoes do TANQUE 1
      tanque1.sensorTemperatura = atuSensorTemperatura(tanque1.sensorTemperatura);
      tanque1.sensorAltura = atuSensorAltura(tanque1.sensorAltura);
                  analisaInterrucao();
    
      //atualizo as funcoes do TANQUE 2
      tanque2.sensorTemperatura = atuSensorTemperatura(tanque2.sensorTemperatura);
      tanque2.sensorAltura = atuSensorAltura(tanque2.sensorAltura);
                  analisaInterrucao();
    
      //atualizo as funcoes do TANQUE 3
      tanque3.sensorTemperatura = atuSensorTemperatura(tanque3.sensorTemperatura);
      tanque3.sensorAltura = atuSensorAltura(tanque3.sensorAltura);
                  analisaInterrucao();
    
      Serial.println("C2");
      Serial.println(tanque1.preenAtual);
      Serial.println(tanque2.preenAtual);
      Serial.println(tanque3.preenAtual);
      Serial.println(contStatus.vazao1);
      Serial.println(contStatus.vazao2);
      Serial.println(contStatus.consumo1);
      Serial.println(contStatus.consumo2);
      anaSleep();//vejo qual longe do fim do ciclo para inicio do proximo
      Serial.println("\n");
    }
}

////FUNÇÕES DESENVOLVIDAS///////////////////////////////////////////////

//Funcao que analisa o tempo necess�rio para o sincronismo
void anaSleep() {
    //vejo o tempo necess�rio para atingir o per�odo do ciclo
    //pauso o sistema para atingir este tempo
    //testo para caso o ciclo tenha sido ultrapassado
    temp_dif =temp_ciclo- (millis() - temp_ini);
  
    Serial.println(temp_dif);
    funcSleep(temp_dif);
  
    return;
}

//Analisa interrupçoes
void analisaInterrucao(){
  funcSleep(randomGen(15, 25));
  return; 
}

//função utilizada para realiza��o do controle PI da vaz�o de controle
controlProper atuControleVazao(controlProper contStatus,
                               tanqueObjeto tanque1,
                               tanqueObjeto tanque2,
                               tanqueObjeto tanque3) {
  funcSleep(randomGen(225, 300));

  float number;

  //Utilizando um consumo randomico
  number = 0.01 * float(random(75,100));
  contStatus.consumo1 = number;

  /*if(tanque1.preenAtual>=50){
    number = 0.01 * float(random(75,100));
    contStatus.consumo2 = number;
  }
  else{
    contStatus.consumo2 = 0;
  }*/
  number = 0.01 * float(random(75,100));
  contStatus.consumo2 = number;

  float media = (tanque1.preenAtual + tanque2.preenAtual + tanque3.preenAtual) / 3;
  contStatus.vazao1 = contStatus.ganho * (tanque1.preenAtual - media);
  contStatus.vazao2 = contStatus.ganho * (tanque3.preenAtual - media);

  return contStatus;
}

tanqueObjeto atuAltura(controlProper contStatus, tanqueObjeto tanque, int idTanque) {
  tanque.preenAnter = tanque.preenAtual;

  //selecionar o calculo para diferentes valores.
  switch (idTanque)
  {
    case 1:
      tanque.preenAtual = tanque.preenAnter -
                          contStatus.consumo1 * contStatus.delTempo -
                          contStatus.vazao1 * contStatus.delTempo;
      break;
    case 2:
      tanque.preenAtual = tanque.preenAnter +
                          contStatus.vazao1 * contStatus.delTempo +
                          contStatus.vazao2 * contStatus.delTempo;
      break;
    case 3:
      tanque.preenAtual = tanque.preenAnter -
                          contStatus.consumo2 * contStatus.delTempo -
                          contStatus.vazao2 * contStatus.delTempo;
      break;
  }

  return tanque;
}

//funcao utilizada para leitura auxiliar de pressao do sistema
grandeza atuSensorPressao(grandeza valor) {
  funcSleep(randomGen(75, 100));
  return valor;
}

//funcao utilizada para leitura auxiliar de vazao do sistema
grandeza atuSensorVazao(grandeza valor) {
  funcSleep(randomGen(75, 100));
  return valor;
}

//funcao utilizada para leitura auxiliar de pressao do sistema
grandeza atuSensorTemperatura(grandeza valor) {
  funcSleep(randomGen(75, 100));
  return valor;
}

//funcao utilizada para leitura auxiliar de pressao do sistema
grandeza atuSensorAltura(grandeza valor) {
  funcSleep(randomGen(75,100));
  return valor;
}

//funcao que realiza um sleep de tempo recebido
void funcSleep(int temp_Sleep) {
  delay(temp_Sleep);
  return;
}

//funcao que gera a randomizado dos processos de leitura
int randomGen(int lim_inf, int lim_sup) {
  return random(lim_inf, lim_sup);
}
