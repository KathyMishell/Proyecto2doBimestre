/* 
 * Universidad Técnica del Norte
 *              SISTEMAS EMBEBIDOS
 * Integrantes: Erazo Israel
 *              Guatemal Katherine
 *              Proyecto 2 bimestre
 *              
  */
#include <ListLib.h>
#include "datos.h"
#include "datos_Prueba.h"
int filMQ135=0;
int filMQ7=0;
int filEtiq=0;
int a=0;
int resultado;
int respuesta;
int n=0;


List <int> list; 
void bayesiano(int etiquetas, int columnas, int filas, float r);
void setup() {
Serial.begin(9600);
Serial.println("*******************Algoritmo de Aprendizaje de máquina Bayesiano - Prueba de datos (30)*****************");
}

void loop() {

  
  if(a<30){
    
  bayesiano(2,3,170,0.2); // llamada al metodo   
    
switch(resultado){
  
  case 1:
    Serial.print("Aire Contaminado --> ");
    Serial.println(String("MQ135: ")+String(filMQ135)+String("  MQ7: ")+String(filMQ7));
    delay(500);
  break;
  case 2:
    Serial.print("Aire Limpio --> ");
    Serial.println(String("MQ135: ")+String(filMQ135)+String("  MQ7: ")+String(filMQ7));
    delay(500);
  break;
  }
}
  if(resultado==filEtiq){
    n++;
  }
  if(a==30){
    Serial.println("Cantidad total de pruebas tomadas: 30");
    Serial.println(String("Cantidad total de aciertos: ")+String(n));
    Serial.println(String("Accuracy = ")+(n/30)*100+String("%"));
    a++;
   }


}


void bayesiano(int etiquetas, int columnas, int filas, float r){
 int i=0; // variable de recorrido en matriz
 int j=0; // variable de recorrido en matriz
 int k=0; // variable de recorrido en matriz
 int t=0; // variable de recorrido en matriz
 float p_x=0.0; // probabilidad marginal
 float distancia=0.0; 
 float sumatoria=0.0;
 float normalizador=0.0;
 float dist_mayor=0.0001;
 float aux=0; // auxiliar de cambio de variable
filMQ135=matriz_Prueba[a][0];
filMQ7=matriz_Prueba[a][1];
filEtiq=matriz_Prueba[a][2];

float matriz_Prueba [3]={filMQ135,filMQ7,filEtiq};
   float prob [4][etiquetas];
   
    for(i=0;i<4;i++){
       for(j=0;j<etiquetas;j++){
          prob[i][j]=0;         
          if(i==0)              
          prob[i][j]=j+1;       
        }
      }
    
    for(i=0;i<etiquetas;i++){               
        for(j=0;j<filas;j++){               
          if(matriz[j][columnas-1]==i+1)    
            prob[1][i]++;                   
          }
      }


    
    for(i=0;i<filas;i++){
       for(j=0;j<columnas-1;j++){
         sumatoria=sumatoria+pow(matriz[i][j]-matriz_Prueba[j],2); 
        }
        distancia=sqrt(sumatoria); 
        sumatoria=0;
        if(distancia>dist_mayor)
          dist_mayor=distancia; 
      }
      distancia=0; 
    
    for(i=0;i<filas;i++){
       for(j=0;j<columnas-1;j++){
         sumatoria=sumatoria+pow(matriz[i][j]-matriz_Prueba[j],2);
       }
        distancia=sqrt(sumatoria); 
        sumatoria=0;
        normalizador=distancia/dist_mayor; 
        if(normalizador<r)
            list.Add(i); 
    }
    
    for(i=0;i<list.Count();i++){                          
      for(j=0;j<etiquetas;j++){                           
          if(matriz[list[i]][columnas-1]==prob[0][j])     
            prob[2][j]++;                                 
        }
      }
      
      p_x=float(list.Count())/float(filas); 
   for(k=0;k<etiquetas;k++){
      prob[3][k]=((prob[1][k]/filas)*(prob[2][k]/prob[1][k]))/p_x;
    }
            
      for(k=0;k<etiquetas;k++){
         if(prob[3][k]>aux){
           resultado=int(prob[0][k]);
           aux=prob[3][k];
          }
        }

    a++;
  for(int x=0;x<171;x++){
    list.Remove(x);
    }
  
 }
