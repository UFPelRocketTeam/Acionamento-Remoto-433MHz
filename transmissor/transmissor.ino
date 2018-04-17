#include <VirtualWire.h> //Insere a biblioteca VirtualWire
#define T_BOT 5          //Define o pino 5 para o botao
char T_C_IGNITOR[2];         //Armazena o estado do ignitor
int T_IGNITOR = 0;           //Define o ignitor como nivel logico baixo
int IGN_STATE= -1;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
  
void setup() 
{                 //Chama a função setup
  pinMode(T_BOT,INPUT_PULLUP); //Configura o pino 5 como entrada
  vw_set_tx_pin(2);            //Configura o pino 2 como transmissor
  vw_setup(2000);              //Velocidade de trasmissao em bps
}
 
void loop()
{
    if ( (millis() - lastDebounceTime) > debounceDelay)
    {
      if((digitalRead(T_BOT) == LOW) && (IGN_STATE <0))
      {                 //Configura o botao como acionado
        T_IGNITOR = !T_IGNITOR;                               //Inverte o estado do ignitor
        itoa(T_IGNITOR, T_C_IGNITOR, 2);                      //Converte os dados de int para char
        vw_send((uint8_t *)T_C_IGNITOR, strlen(T_C_IGNITOR)); //Envia os dados
        vw_wait_tx();                                 //Aguarda a transmissao de dados
        lastDebounceTime = millis(); //set the current time
        IGN_STATE=-IGN_STATE;
        delay(100);                                   //Tempo em que o ignitor permanece em alto
    
     }
     else if ((digitalRead(T_BOT)==HIGH) && (IGN_STATE>0))
     {
       lastDebounceTime = millis(); //set the current time
       IGN_STATE=-IGN_STATE;
     }
    }
}

