// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
#include <LiquidCrystal.h>

// Inicializacion de Variables
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int pulsos = 2;
int pulses = 0;
bool select = 0; //1 RUN, 0 STOP;
int vals = 0;
int old_vals = 0;
bool val_up = 0;
bool val_down = 0;
bool var_antup = 0;
bool var_antdown = 0;

int valR = 1;
int old_valR = 0;
int valL = 0;
int old_valL = 0;
int estado_giro = 0;//0 R, 1 L

   //Variables de tiempo para cambio de estado
long intervaloPaso1 = (1000/pulsos);
long intervaloPaso2;
long intervaloPaso3;
long intervaloPaso4;
unsigned long previusmsPaso1 = 0;
unsigned long previusmsPaso2 = 0;
unsigned long previusmsPaso3 = 0;
unsigned long previusmsPaso4 = 0;

   //Salidas 
const int j=4;
const int DirPinesEntradas[5]={13,12,11,10,9};
bool entrada[5];


// Posiciones Unipolar
bool S_1=0;
bool S_2=0;
bool S_3=0;
bool S_4=0;

   // Posiciones BipolarH1
bool Q_1R = 0;
bool Q_2R = 0;
bool Q_3R = 0;
bool Q_4R = 0;


  //Definicion Estados
#define Paso0 0
#define Paso1 1
#define Paso2 2
#define Paso3 3
#define Paso4 4

int estadoActual = Paso0;



   // Inicializacion Pines
void setup()
{
  lcd.begin(16, 2);
  
  for (int i = 0; i <= j; i++) 
  {
    pinMode(DirPinesEntradas[i], INPUT);
  }
  
  Serial.begin(9600);
  
}


   // Definicion de Funciones
// Funciones de Cambio Motor Bipolar Derecha
void paso1BI1()
{
  Q_1R = 1;
  Q_2R = 0;
  Q_3R = 1;
  Q_4R = 0;
  lcd.setCursor(0, 0);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
}
void paso1BI2()
{
  Q_1R = 1;
  Q_2R = 0;
  Q_3R = 1;
  Q_4R = 0;
  lcd.setCursor(0, 1);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
}

void paso2BI1()
{
  Q_1R = 1;
  Q_2R = 0;
  Q_3R = 0;
  Q_4R = 1;
  lcd.setCursor(0, 0);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
}

void paso2BI2()
{
  Q_1R = 0;
  Q_2R = 1;
  Q_3R = 0;
  Q_4R = 1;
  lcd.setCursor(0, 1);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
}

void paso3BI1()
{
  Q_1R = 0;
  Q_2R = 1;
  Q_3R = 0;
  Q_4R = 1;
  lcd.setCursor(0, 0);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
  
  
}

void paso3BI2()
{
  Q_1R = 0;
  Q_2R = 1;
  Q_3R = 0;
  Q_4R = 1;
  lcd.setCursor(0, 1);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
}

void paso4BI1()
{
  Q_1R = 0;
  Q_2R = 1;
  Q_3R = 0;
  Q_4R = 1;
  lcd.setCursor(0, 0);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
}

void paso4BI2()
{
  Q_1R = 1;
  Q_2R = 0;
  Q_3R = 1;
  Q_4R = 0;
  lcd.setCursor(0, 1);
  lcd.print(Q_1R);
  lcd.print(Q_2R);
  lcd.print(Q_3R);
  lcd.print(Q_4R);
}


void paso1UP()
{
  S_1=1;
  S_2=1;
  S_3=0;
  S_4=0;
  
  lcd.setCursor(5,0);
  lcd.print(S_1);
  
  lcd.setCursor(6,0);
  lcd.print(S_2);
  
  lcd.setCursor(7,0);
  lcd.print(S_3);
  
  lcd.setCursor(8,0);
  lcd.print(S_4);
}

void paso2UP()
{
  S_1=0;
  S_2=1;
  S_3=1;
  S_4=0;
  
  lcd.setCursor(5,0);
  lcd.print(S_1);
  
  lcd.setCursor(6,0);
  lcd.print(S_2);
  
  lcd.setCursor(7,0);
  lcd.print(S_3);
  
  lcd.setCursor(8,0);
  lcd.print(S_4);
  
}
void paso3UP()
{
  S_1=0;
  S_2=0;
  S_3=1;
  S_4=1;
  
  lcd.setCursor(5,0);
  lcd.print(S_1);
  
  lcd.setCursor(6,0);
  lcd.print(S_2);
  
  lcd.setCursor(7,0);
  lcd.print(S_3);
  
  lcd.setCursor(8,0);
  lcd.print(S_4);
  
}
void paso4UP()
{
  S_1=1;
  S_2=0;
  S_3=0;
  S_4=1;
  
  lcd.setCursor(5,0);
  lcd.print(S_1);
  
  lcd.setCursor(6,0);
  lcd.print(S_2);
  
  lcd.setCursor(7,0);
  lcd.print(S_3);
  
  lcd.setCursor(8,0);
  lcd.print(S_4);
}


void controladorEstds() //Función que controla el cambio de estado
{
  unsigned long currentMillis = millis();
  pulses=subida_pulse();
  
  if(estadoActual==Paso4){
    estadoActual=Paso0;
  }
  
  
  if ((currentMillis-previusmsPaso1)>=intervaloPaso1   && (estadoActual==Paso0))
  {
    previusmsPaso1 = currentMillis;
    estadoActual = Paso1;
    intervaloPaso2 = (1000/pulses) + (intervaloPaso1);
   
  }
  
  if (((currentMillis-previusmsPaso2)>=intervaloPaso2) && (estadoActual==Paso1))
  {
    previusmsPaso2 = currentMillis;
    estadoActual = Paso2;
    intervaloPaso3 = (1000/pulses) + (intervaloPaso2);
    
  }
  
  if (((currentMillis-previusmsPaso3)>=intervaloPaso3) && (estadoActual==Paso2))
  {
    previusmsPaso3 = currentMillis;
    estadoActual = Paso3;
    intervaloPaso4 = (1000/pulses) + (intervaloPaso3);
    
  }
  
  if (((currentMillis-previusmsPaso4)>=intervaloPaso4) && (estadoActual==Paso3))
  {
    previusmsPaso4 = currentMillis;
    estadoActual = Paso4;
    intervaloPaso1 = (1000/pulses) + (intervaloPaso4);
    //Serial.println("paso4");
  }
}

void cambioEstadosR() //Funcion que llama cada estado (Giro Derecha)
{
  switch (estadoActual) 
  {
   
    case Paso1:
    paso1UP();
    paso1BI1();
    paso1BI2();
    Serial.println("paso1");
    break;
    
    case Paso2:
    paso2UP();
    paso2BI1();
    paso2BI2();
    Serial.println("paso2");
    break;
    
    case Paso3:
    paso3UP();
    paso3BI1();
    paso3BI2();
    Serial.println("paso3");
    break; 
    
    case Paso4:
    paso4UP();
    paso4BI1();
    paso4BI2();
    Serial.println("paso4");
    break;
    
    default:
    break;
    
  }
 
}

void cambioEstadosL() //Funcion que llama cada estado (Giro Izquierda)
{
  switch (estadoActual) 
  {
    case Paso1:
    paso4UP();
    paso4BI1();
    paso4BI2();
    Serial.println("paso4");
    break;
    
    case Paso2:
    paso3UP();
    paso3BI1();
    paso3BI2();
    Serial.println("paso3");
    break;
    
    case Paso3:
    paso2UP();
    paso2BI1();
    paso2BI2();
    Serial.println("paso2");
    break; 
    
    case Paso4:
    paso1UP();
    paso1BI1();
    paso1BI2();
    Serial.println("paso1");
    break;
    
    default:
    break;
    
  }
  
 
}

int subida_pulse()
{
    val_up= entrada[4]; // lee el estado del Boton select si el boton esta presionado o no  y cambia el estado a encendido u apagado
  if ((val_up == HIGH) && (var_antup == LOW))
  {
    
    if(pulsos<20){
      pulsos=pulsos+1;
    }
    
    
  }
    var_antup = val_up;  // vals es ahora viejo, vamos a almacenarlo
  
  val_down= entrada[3]; // lee el estado del Boton select si el boton esta presionado o no  y cambia el estado a encendido u apagado
  if ((val_down == HIGH) && (var_antdown == LOW))
  {
    
    if(pulsos>2){
      pulsos=pulsos-1;     
    }
    
    
  }
    var_antdown = val_down;

  if(pulsos<10){

    lcd.setCursor(13,1);
    lcd.print(" ");

    lcd.setCursor(12,1);
    lcd.print(pulsos);


    
    }else{
      lcd.setCursor(12,1);
      lcd.print(pulsos);
      }

  return pulsos;
}

void seleect()
{
  vals= entrada[0]; // lee el estado del Boton select si el boton esta presionado o no  y cambia el estado a encendido u apagado
  if ((vals == HIGH) && (old_vals == LOW))
  {
    select=1-select;
  }
    old_vals = vals;  // vals es ahora viejo, vamos a almacenarlo
  
  if(select==1)
  {
    lcd.setCursor(8,1);
    lcd.print(" ");
    
    lcd.setCursor(5,1);
    lcd.print("RUN");
    
    lcd.setCursor(10,0);
    lcd.print("PULSOS");
    lcd.setCursor(12,1);
    lcd.print(pulsos);
    
    controladorEstds();
    subida_pulse();
    selectorgiro();
  }
  
  else
  {
    lcd.setCursor(0,0);
    lcd.print("                ");
    
    lcd.setCursor(0,1);
    lcd.print("     ");
    
    lcd.setCursor(5,1);
    lcd.print("STOP");
    
    lcd.setCursor(9,1);
    lcd.print("       ");
    
  }
} 

void selectorgiro()
{
  valR= entrada[2]; // lee el estado del Boton Right si el boton esta presionado o no  y cambia el estado a encendido u apagado
  if ((valR == HIGH) && (old_valR == LOW))
  {
    estado_giro=0;
  }
    old_valR = valR;  // valR es ahora viejo, se almacena
  
  
  valL= entrada[1]; // lee el estado del Boton Left si el boton esta presionado o no  y cambia el estado a encendido u apagado
  if ((valL == HIGH) && (old_valL == LOW))
  {
    estado_giro=1;
  }
    old_valL = valL;
  
  if(estado_giro==0 && select==1)
  {
    lcd.setCursor(9,1);
    lcd.print(">>");
    cambioEstadosR();
  }
  
  else if (estado_giro==1 && select==1)
  {
    lcd.setCursor(9,1);
    lcd.print("<<");
    cambioEstadosL();
  }
  
}


  // Ejecución
void loop()
{  
  for (int i = 0; i <= j; i++) 
  {
    entrada[i]=digitalRead(DirPinesEntradas[i]);
  }
  
  seleect();
  
}
