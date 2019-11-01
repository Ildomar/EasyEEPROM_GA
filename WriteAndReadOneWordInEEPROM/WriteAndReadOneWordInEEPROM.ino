/***************************************************************************************************
* Projeto: WriteAndReadOneWordInEEPROM.ino
*
*   @Author: Ildomar Coelho
*   Data criação: 30/10/2019
*
*   Data Revisão: 30/10/2019
*
*   Descrição: Exemplo que mostra a escrita e leitura de uma palavra na EEPROM do Arduino.
*
*
*
* Revisão 01 ======== 01/10/2019===================================================================
* 
* -> Feito estrutura inicial da biblioteca EasyEEPROM_GA.h, mas ainda sem implementar.
* -> Preparado um exemplo para testar gravação e leitura na EEPROM com uso da EasyEEPROM_GA.h
* 
* Status:
*     - Reconhecndo os comandos ALL, @R-  e @W-
*     - Faltando implementar funcionalidades da EasyEEPROM_GA.h para fazer uso real dos comandos.
*     
*     --OBS.: Até esta revisão ainda não está sendo feito acesso à EERPOM.
*
****************************************************************************************************/

#include "EasyEEPROM_GA.h"

#define DEBUG

inline byte bt1 = A4; //Botão 1
inline byte bt2 = A5; //Botão 2


 EasyEEPROM_GA eeprom;


 /*========== VARIÁVEIS PARA USO DE DADOS DA SERIAL ================================*/
 String inputString="";
 bool isStringComplete = false;




void trataComando();
int convertToInteger(String dados);


 

/***************************************************************************************************
 **************       Setup                     ****************************************************
 **************************************************************************************************/
void setup(){
    Serial.begin(9600);

    pinMode(bt1,INPUT_PULLUP);//Define como entrada com resistor de pull-up.
    pinMode(bt2,INPUT_PULLUP);//Define como entrada com resistor de pull-up.

    Serial.println(F("************ Programa para Escrita e Leitura na EERPOM ************************************\n*"));
    Serial.println(F("* Autor: Ildomar Coelho"));
    Serial.println(F("* Comandos:"));
    Serial.println(F("*\tALL\t\t-> Imprime todos os textos (com seus endereços) salvos na EEPROM;"));
    Serial.println(F("*\t@R-xxxx\t\t-> Lê o texto salvo no endereço indicado por xxxx (de 3 a 1020);"));
    Serial.println(F("*\t@W-bla bla ...\t-> Salva na EERPOM o texto escrito após o comando \"@W-\".\n*"));
    Serial.println(F("* Obs.: Use apenas 'nova-linha' (\\n) no Terminal Serial\n*"));
    Serial.println(F("*******************************************************************************************\n"));
    
}//fim setup

/***************************************************************************************************
 **************       Loop                      ****************************************************
 **************************************************************************************************/
void loop(){
  //Função que analisa se há dados na Serial para tratar
  if(isStringComplete){

    //Serial.println(inputString);

    trataComando();

    
    isStringComplete = false;
    inputString = "";
    
  }
  
  if(digitalRead(bt1)==LOW){
    while(digitalRead(bt1)==LOW){delay(5);}

    
    delay(200);
  }
}//fim loop








/***************************************************************************************************
 **************       Função para tratamento de comandos    *****************************************
 **************************************************************************************************/
void trataComando(){  
  int tam = inputString.length();  
  String cmd= inputString.substring(0,3);//Coleta os 3 primeiros caracteres equivalentes ao CMD
  if(cmd=="ALL" && tam==4){
    int nextID=0; //Sempre deve ser inicializada com 0 (Zero).
    String text="";
    do{
      text = eeprom.readNextTextInEEPROM(nextID);
      Serial.print(F("Texto: "));Serial.print(nextID);Serial.print(F(" - "));Serial.println(text);
      text="";//É importante sempre evitar manter dados na RAM para não estourar.
    }while(nextID!=-1);
  }else{
    if(tam>4){
      String dados = inputString.substring(3,tam-1);//Coleta tudo após os 3 primeiros caracteres.

      int tam2 = dados.length();
      
      if(cmd.equals("@W-")){
        Serial.print(F("Salvando: ["));Serial.print(dados);Serial.println(F("]..."));
      }else{
        if(cmd.equals("@R-") && tam2<=4){
          int idInt= convertToInteger(dados);
          //Mesmo se a conversão for um sucesso, ainda se restringe ao valor mínimo de ID que é 3.
          if(idInt>=3){
            Serial.print(F("Lendo texto ID: "));Serial.println(idInt);
            //ler aqui
          }else{
            Serial.println(F("Erro: A ID deve conter apenas numeros inteiros, E deve inciar a partir de 3."));         
          }
        }else{
          Serial.println(F("ID inconsistente!"));
          Serial.print(F("ID: "));Serial.println(dados);
        }
      }//fim else
      
          
    }else{
       Serial.println(F("Tamanho insuficiente!"));
    }//fim else
     
  }//fim else
 
}//fim func



/***************************************************************************************************
 * Função para cerrificar se String pode ser convertida em um valor inteiro    ********************
 **************************************************************************************************/
int convertToInteger(String dados){
  int tam=0, valor=0;
  boolean isOk=true;
  tam = dados.length();

  char c=0;
  for(int i=0; i<tam;i++){
    c=dados.charAt(i);    
     // Serial.println(c);
    if(c<48 || c>57){
      isOk=false;//Detectado caractere não conversível para valores de 0 a 9.
      i=tam;//finaliza análise
    }
  }//fim for

  if(isOk){//se é um valor conversível... converte para inteiro
   // Serial.println("OK");
    for(int i=0; i<tam;i++){
      valor*=10;//desloca o valor para esquerda, se for diferente de zero
      c=dados.charAt(i);
      valor+=c-48;//soma o valor com o novo dado convertido para inteiro       
      //Serial.print(F("->"));Serial.println(valor,DEC);   
    }
  }
  return valor;
}//fim func










/*////// PARALELOS ////////////////////////////////////////////////////////////////////////////////////*/
 
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  //Serial.println("->");
  if(isStringComplete==true){
    isStringComplete=false;
    inputString="";
  }
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      isStringComplete = true;
    }
  }
}
