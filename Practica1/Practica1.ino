// Declaracione de constantes
const int j=6;
const int DirPinesEntradas[2]={2,3};
const int DirPinesSalidas[5]={8,7,6,5,4};
bool entrada[2];
bool salida[5]={false, false, false, false, false};

// Configuracion de Pines de entrada y salida
void setup(){
 // initializa los pines:
  for (int i = 0; i <= j; i++) {
    if (i<2) {
      pinMode(DirPinesEntradas[i], INPUT);
    }
    else {
      pinMode(DirPinesSalidas[i-2], OUTPUT);
    }
  }
}

//DEFINICION DE LAS FUNCIONES LÓGICAS

bool AND (bool X, bool Y ){
  if (X == 1  && Y == 1){
    return 1;
  }
  else{
    return 0;
  }
}

bool OR (bool X, bool Y ){
  if(X== 1 || Y==1){
    return 1;
  }
  else{
    return 0;
  }
}

bool XOR (bool X, bool Y ){
  if((X==1 && Y==1)  || (X==0 && Y==0)){
    return 0;
  }
  else{
    return 1;
  }
}

bool NOR (bool X, bool Y ){
  if(X==1 || Y==1){
    return 0;
  }
  else{
    return 1;
  }
}


bool NAND (bool X, bool Y ){
  if (X == 1  && Y == 1){
    return 0;
  }
  else{
    return 1;
  }
}




void loop (){
  
 //LECTURA DE LAS ENTRADAS Y SALIDAS
  for(int i=0; i<=j;i++){
    if(i<2){
      entrada[i]=digitalRead(DirPinesEntradas[i]);
    }
    else{
      digitalWrite(DirPinesSalidas[i-2],salida[i-2]);
    }
  }
 
  //EJECUCION DEL PROGRAMA
  salida[0]=AND(entrada[1],entrada[0]);
  salida[1]=OR(entrada[1],entrada[0]);
  salida[2]=XOR(entrada[1],entrada[0]);
  salida[3]=NOR(entrada[1],entrada[0]);
  salida[4]=NAND(entrada[1],entrada[0]);
}

