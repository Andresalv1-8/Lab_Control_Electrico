// Andrés Alvarado C 202003822 Jafet Aguero M 2019035485
// Fecha: 13/08/2022
// Laboratorio 1

// Declaracion de constantes
const int j=9;
const int DirPinesEntradas[4]={6,5,4,3};
const int DirPinesSalidas[6]={12,11,10,9,8,7};
bool entrada[4];
bool salida[6]={false,false,false,false,false,false};

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

bool NOR2(bool X, bool Y){
  return !(X || Y);
}

bool NOR3(bool X, bool Y, bool Z){
  return !(X || Y || Z);
} 


bool AND2(bool X, bool Y){
  return (X && Y);
}

bool AND3(bool X, bool Y, bool Z){
  return (X && Y && Z);
}

bool OR2(bool X, bool Y){
  return (X || Y);
}


bool OR3(bool X, bool Y, bool Z){
  return (X || Y || Z);
}

bool NOT(bool X){
  return !(X);
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
  salida[2]=NAND_3INPUT(NAND_2INPUT(entrada[1], entrada[3]),NAND_2INPUT(entrada[0],entrada[1]),NAND_3INPUT(entrada[0],entrada[2],entrada[3]));
  salida[3]=NAND_2INPUT(NAND_2INPUT(1,NAND_2INPUT(NAND_3INPUT(entrada[3],entrada[1],entrada[0]),NAND_3INPUT(entrada[0],entrada[1],entrada[2]))),NAND_2INPUT(1,NAND_2INPUT(NAND_3INPUT(entrada[2],!entrada[0],!entrada[1]),NAND_2INPUT(NAND_2INPUT(1,NAND_2INPUT(entrada[0],!entrada[1])),NAND_2INPUT(1,NAND_2INPUT(!entrada[2],!entrada[3]))))));
  salida[4]=OR3(AND2(entrada[1],entrada[3]),AND2(entrada[0],entrada[1]),AND3(entrada[0],entrada[2],entrada[3]));
  salida[5]=OR2(OR3(AND3(NOT(entrada[0]),NOT(entrada[1]),entrada[2]),AND2(AND3(NOT(entrada[1]),entrada[0],NOT(entrada[2])),NOT(entrada[3])),AND3(entrada[0],entrada[1],entrada[3])),AND3(entrada[0],entrada[1],entrada[2]));
}
