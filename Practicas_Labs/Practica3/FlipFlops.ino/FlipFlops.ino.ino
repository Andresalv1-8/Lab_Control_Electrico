     // Andrés Alvarado C 202003822 Jafet Aguero M 2019035485
     // Fecha: 27/08/2022
     // Práctica 3

// Declaracion de constantes

   //Pines CLK
int EstadoLedtemp=2;
const int ledPin =  13; 
int ledState=LOW; 
unsigned long previousMillis = 0;                  
long voltaje=0;

   //FF_D
bool Q_D= false;
volatile bool D;

   // FF_T
bool Q_T= false;
volatile bool T;

   // FF_JK
bool Q_JK= false;
volatile bool J; 
volatile bool K;

  // FF_RS
bool Q_RS=false;

   //Entradas y salidas (botones y FF's)
const int j=9;
const int DirPinesEntradas[2]={4,3};
const int DirPinesSalidas[8]={12,11,10,9,8,7,6,5};
bool entrada[2];
bool salida[8]={false, false, false, false, false, false, false, false};


// Configuracion de Pines de entrada y salida
void setup()
{
  //Potenciómetro
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(EstadoLedtemp, INPUT);
  
  //Attaches
  attachInterrupt(digitalPinToInterrupt(2), Flip_Flops, RISING);
  
  //Incializa los pines "Entradas y salidas (botones y FF's)"
  for (int i = 0; i <= j; i++) 
  {
    if (i<2) 
    {
      pinMode(DirPinesEntradas[i], INPUT);
    }
    else 
    {
      pinMode(DirPinesSalidas[i-2], OUTPUT);
    }
  }
}  
 


//DEFINICION DE LAS FUNCIONES LÓGICAS

   //Función Flip_Flops
void Flip_Flops()
{
  //Flip Flop J_K
  J=entrada[0];
  K=entrada[1];
  Q_JK = (J&&(!Q_JK))||(!K&&(Q_JK));

  //Flip Flop T
  T=entrada[1];
  Q_T = (Q_T&&!T)||(!Q_T&&T);
  
  //Flip Flop D
  D=entrada[1];
  Q_D = D;
}

   //Función lectura de voltaje
void CLK()
{
  voltaje=analogRead(A0);
  voltaje=map(voltaje, 0, 1023, 0, 100);
  Serial.println(voltaje);
  long interval=voltaje;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}


//Funcion Flip Flop RS
bool FF_RS(bool S, bool R)
{
  return (Q_RS= S||!R&&Q_RS);  
}


// Lecturas y Ejecución de las salidas
void loop ()
{
  //lectura_voltaje();
  CLK();
  
  
//LECTURA DE LAS ENTRADAS Y SALIDAS
  for(int i=0; i<=j;i++)
  {
    if(i<2)
    {
      entrada[i]=digitalRead(DirPinesEntradas[i]);
    }
    else
    {
      digitalWrite(DirPinesSalidas[i-2],salida[i-2]);
    }
  }
  
  salida[0]=Q_JK;
  salida[1]=!Q_JK;
  salida[2]=Q_T;
  salida[3]=!Q_T;
  salida[4]=Q_D;
  salida[5]=!Q_D;
  salida[6]=FF_RS(entrada[0], entrada[1]);
  salida[7]=!FF_RS(entrada[0], entrada[1]);
  
}
