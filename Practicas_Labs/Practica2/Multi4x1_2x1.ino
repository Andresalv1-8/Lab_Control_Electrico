// Andrés Alvarado C 202003822 Jafet Aguero M 2019035485
// Fecha: 13/08/2022
// Práctica 2

// Declaracion de constantes
const int j=5;
const int DirPinesEntradas[4]={6,5,4,3};
const int DirPinesSalidas[2]={7,8};
bool entrada[4];
bool salida[2]={false,false};

// Configuracion de Pines de entrada y salida
void setup()
{
 // initializa los pines:
  for (int i = 0; i <= j; i++)
  {
    if (i<4) 
    {
      pinMode(DirPinesEntradas[i], INPUT);
    }
    else 
    {
      pinMode(DirPinesSalidas[i-4], OUTPUT);
    }
  }
}

//DEFINICION DE LAS FUNCIONES LÓGICAS


bool Mux8x1(bool I0, bool I1, bool I2, bool I3, bool I4, bool I5, bool I6, bool I7, bool S2, bool S1, bool S0)
{
  return ((!S2*!S1*!S0*I0)+(!S2*!S1*S0*I1)+(!S2*S1*!S0*I2)+(!S2*S1*S0*I3)+(S2*!S1*!S0*I4)+(S2*!S1*S0*I5)+(S2*S1*!S0*I6)+(S2*S1*S0*I7));
}


bool Mux4x1 (bool I0, bool I1, bool I2, bool I3, bool S1, bool S0){
 return ((!S1*!S0*I0)+(!S1*S0*I1)+(S1*!S0*I2)+(S0*S1*I3));
}


bool Mux2x1(bool I0, bool I1, bool S0){
 return ((!S0*I0)+(S0*I1)); 
}


void loop ()
{
  
 //LECTURA DE LAS ENTRADAS Y SALIDAS
  for(int i=0; i<=j;i++)
  {
    if(i<4)
    {
      entrada[i]=digitalRead(DirPinesEntradas[i]);
    }
    else
    {
      digitalWrite(DirPinesSalidas[i-4],salida[i-4]);
    }
  }
 
  //EJECUCION DEL PROGRAMA
  salida[0]= Mux8x1(entrada[0], false, false, !entrada[0], entrada[0], !entrada[0], !entrada[0], entrada[0], entrada[1], entrada[2], entrada[3]);
  salida[1]= Mux2x1(Mux4x1(entrada[0],0,0,!entrada[0],entrada[2],entrada[3]),Mux4x1(entrada[0],!entrada[0],!entrada[0],entrada[0],entrada[2],entrada[3]),entrada[1]);
}
