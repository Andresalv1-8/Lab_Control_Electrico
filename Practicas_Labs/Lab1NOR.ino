// Andrés Alvarado C 202003822 Jafet Aguero M 2019035485
// Fecha: 13/08/2022
// Laboratorio 1

// Declaracion de constantes
const int j=5;
const int DirPinesEntradas[4]={6,5,4,3};
const int DirPinesSalidas[2]={8,7};
bool entrada[4];
bool salida[2]={false, false};

// Configuracion de Pines de entrada y salida
void setup(){
 // initializa los pines:
  for (int i = 0; i <= j; i++) {
    if (i<4) {
      pinMode(DirPinesEntradas[i], INPUT);
    }
    else {
      pinMode(DirPinesSalidas[i-4], OUTPUT);
    }
  }
}

//DEFINICION DE LAS FUNCIONES LÓGICAS

bool NOR2(bool X, bool Y){
  return !(X || Y);
}

bool NOR3(bool X, bool Y, bool Z){
  return !(X || Y || Z);
} 


void loop (){
  
 //LECTURA DE LAS ENTRADAS Y SALIDAS
  for(int i=0; i<=j;i++){
    if(i<4){
      entrada[i]=digitalRead(DirPinesEntradas[i]);
    }
    else{
      digitalWrite(DirPinesSalidas[i-4],salida[i-4]);
    }
  }
 
  //EJECUCION DEL PROGRAMA
  salida[0]=NOR2(NOR2(0,NOR3(NOR2(entrada[0],entrada[1]),NOR2(entrada[1],entrada[2]),NOR2(entrada[0],entrada[3]))),NOR2(entrada[1],entrada[3]));
  salida[1]=NOR2(NOR2(0,NOR3(NOR2(entrada[0],entrada[2]),NOR2(entrada[0],NOR2(0,entrada[1])),NOR3(entrada[3],entrada[2],NOR2(0,entrada[1])))),NOR2(0,NOR2(NOR3(entrada[1],NOR2(0,entrada[0]),NOR2(0,entrada[3])),NOR3(entrada[1],NOR2(0,entrada[0]),NOR2(0,entrada[2])))));
}
