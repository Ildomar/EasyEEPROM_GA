
#include "EasyEEPROM_GA.h"

/**********************************************************************************************
 * Função que recebe uma String, analisa se há espaço suficiente, e salva na memória.
 * Retorna um valor de 3 a 1023 caso tenha sucesso.
 * Se não, retorna -1 caso encontre inscosistência na frase, ou 0 para indicar memória cheia.
 * 
 * return 0; //String vazia ou inconsistente.
 * return -x; // x = -(valor atual de bytes livres na memória). * 
 *********************************************************************************************/
int EasyEEPROM_GA::writeTextInEEPROM(String text){
  int id=3;

  return id;
}//fim func

/**********************************************************************************************
 * Função que recebe uma ID (Endereço da memoria), analisa se há dados salvos neste endereço.
 * Retorna o texto lido.
 * Se não, retorna "" caso não encontre um texto válido para o endereço * 
 *********************************************************************************************/
String EasyEEPROM_GA::readTextInEEPROM(int id){
  String resp="";


  return resp;
}//fim func


/**********************************************************************************************
 * Função que Retorna um texto lido e seta com o endereço do próximo texto a variável representada 
 * pelo endereço "&next".
 * 
 * Quando não houver mais um próximo texto para ser lido, é passado o valor -1 para "&next".
 * 
 * Retorna o texto lido.
 * Se não, retorna "".
 * 
 * Exemplo de uso:
 * EasyEEPROM_GA eeprom;
 * int nextID=0; //Sempre deve ser inicializada com 0 (Zero).
 * String text="";
 * do{
 *    text = eeprom.readNextTextInEEPROM(nextID);
 *    Serial.print(F("Texto: "));Serial.print(nextID);Serial.print(F(" - "));Serial.println(text);
 *    text="";//É importante sempre evitar manter dados na RAM para não estourar.
 * }while(nextID!=-1);
 * 
 *********************************************************************************************/
String EasyEEPROM_GA::readNextTextInEEPROM(int &next){
  String resp="";
  
  if(next==0){
    next=3;
    resp="TESTE";
  }else{
      if(next==8){
      next=-1;
      resp="End";
    }else{
      resp="OPA";
      next++;
    }
  }
  
  
  return resp;
}//fim func
