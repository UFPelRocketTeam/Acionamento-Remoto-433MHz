#include <VirtualWire.h> //Insere a biblioteca VirtualWire
#define R_IGNITOR 8          //Define o pino 8 para o IGNITOR
char R_C_IGN[2];         //Armazena o estado do IGNITOR
int R_BOT = 0;           //Configura o botao como nao acionado
 
void setup() 
{         
  pinMode(R_IGNITOR, OUTPUT); //Configura o pino 8 como saída
  vw_set_rx_pin(4);       //Configura o pino 4 como receptor
  vw_setup(2000);         //Velocidade de trasmissao em bps
  vw_rx_start();          //Inicializa o receptor
}
 
void loop()
{                           
    uint8_t buf[VW_MAX_MESSAGE_LEN];     //Armazena os dados
    uint8_t buflen = VW_MAX_MESSAGE_LEN; //Define o tamanho dos dados
    if(vw_get_message(buf, &buflen)) 
    {   //Verifica se exite dados
      int a;                             
      for(a = 0; a < buflen; a++)
      {        
        R_C_IGN[a] = char(buf[a]);       //Armazena dados
      }
      R_C_IGN[buflen] = '\0';
      int R_BOT = atoi(R_C_IGN);          //Converte os dados de char para int
      if(R_BOT == 1)
      {                    //Se o botao for acionado, aciona o IGNITOR
        digitalWrite(R_IGNITOR, HIGH);        //Configura o IGNITOR com nivel logico alto             
      }
      if(R_BOT == 0) 
      {                    //Se o botao nao for acionado, nao aciona o ignitor
        digitalWrite(R_IGNITOR, LOW);         //Configura o ignitor como desligado
    
      }
    }
}
