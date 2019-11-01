/******************************************************************************
 * Arquivo: Bliblioteca EasyEEPROM_GA.h
 * 
 * Descrição: 
 *    Permite escrever pequenos textos/frases na EEPROM de forma simples.
 *    Como funciona:
 *    --> Através da função "int writeTextInEEPROM(String text)",
 *        o sistema escolhe automáticamente a parte vazia da memória
 *        e faz a escrita.
 *        Após escrever com sucesso, essa função retorna uma ID (endereço) da frase salva.
 *        Essa ID (de 3 a 1023) deve ser salva para que seja possível, futuramente, 
 *        recuperar a informação salva.
 *    --> Através da função "String readTextInEEPROM(int id)",
 *        o sistema retorna a frase salva no endereço indicado no parâmetro ID.
 * 
 * @Author: Ildomar COelho
 * Data criação: 30/10/2019
 * 
 * Data revisão: 30/10/2019
 * 
 * 
 */

 #ifndef EASYEEPROM_GA_H
 #define EASYEEPROM_GA_H

 #include <Arduino.h>


 class EasyEEPROM_GA{

  public:

    int writeTextInEEPROM(String text);
  
    String readTextInEEPROM(int id);

    String readNextTextInEEPROM(int &next);

  private:

  


  
 };//fim classe
 #endif //Fim biblioteca






 
