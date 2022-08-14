// Andrés Alvarado C 202003822 Jafet Aguero M 
// Fecha: 13/08/2022
// Laboratorio 1

// Declaracion de constantes
const int j=5;
const int DirPinesEntradas[4]={3,4,5,6};
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

bool NAND_2INPUT(bool X, bool Y){
  if (X == 1 && Y == 1){
    return 0;
  }
  else{
    return 1;
  }
}

bool NAND_3INPUT(bool X, bool Y, bool Z){
  if (X == 1 && Y == 1 && Z == 1){
    return 0;
  }
  else{
    return 1;
  }
} 

bool NAND_4INPUT(bool X, bool Y, bool Z, bool W){
  if (X == 1 && Y == 1 && Z == 1 && W == 1){
    return 0;
  }
  else{
    return 1;
  }
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
  salida[0]=NAND_3INPUT(NAND_2INPUT(entrada[1], entrada[3]),NAND_2INPUT(entrada[0],entrada[1]),NAND_3INPUT(entrada[0],entrada[2],entrada[3]));
  salida[1]=NAND_4INPUT(NAND_3INPUT(!entrada[0],!entrada[1],entrada[2]),NAND_3INPUT(entrada[0],entrada[1],entrada[2]),NAND_3INPUT(entrada[0],entrada[1],entrada[3]),NAND_4INPUT(entrada[0],!entrada[1],!entrada[2],!entrada[3]));
}
