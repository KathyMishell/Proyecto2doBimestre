/* 
 * Universidad Técnica del Norte
 *              SISTEMAS EMBEBIDOS
 * Integrantes: Erazo Israel
 *              Guatemal Katherine
 *              Proyecto 2 bimestre
 *              
  */

#include "datos.h"
#include "datos_Prueba.h"
int s_analogica_mq135=0;
int s_analogica_mq7 = 1;
int respuesta;
int filMQ135=0;
int filMQ7=0;
int filEtiq=0;
int a=0;
int n=0;

int knn (int k, int etiquetas, int tam_col, int col_fil); // definir la func
void setup() {
Serial.begin(9600);
Serial.println("*******************Algoritmo de Aprendizaje de máquina KNN - Prueba de datos (30)*****************");
}

void loop() {



respuesta=knn(3,2,3,170); 
if(a<30){
switch(respuesta){
  
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
  if(respuesta==filEtiq){
    n++;
  }
  if(a==30){
    Serial.println("Cantidad total de pruebas tomadas: 30");
    Serial.println(String("Cantidad total de aciertos: ")+String(n));
    Serial.println(String("Accuracy = ")+(n/30)*100+String("%"));
    a++;
   }
}

int knn (int k, int etiquetas, int tam_col, int tam_fil){
int col;
int fil=0;
int i=0;
int j;
float aux;
float aux_etiqueta;
float potencia;
float raiz;
int label;
String salida="";     
filMQ135=matriz_Prueba[a][0];
filMQ7=matriz_Prueba[a][1];
filEtiq=matriz_Prueba[a][2];
float matriz_Prueba [3]={filMQ135,filMQ7,filEtiq};

 float matriz_k [3][k];
 for(;i<k;i++){
  matriz_k[0][i]=i+1.00;  //  |   1 |   2   |   3   |
  matriz_k[1][i]=0; //     |  0  |   0   |   0   |
  matriz_k[2][i]=2500.0+i;// |2500 | 25001 | 25002 | 
  }
  i=0;
 
  float matriz_eti[2][etiquetas];
  for(;i<etiquetas;i++){
      matriz_eti[0][i]=i+1.0; // |  1 |  2 |  3  |
      matriz_eti[1][i]=0.0;   // |  0 |  0 |  0  |
    }

   for(;fil<tam_fil;fil++){
      for(col=0;col<tam_col-1;col++){ // menos la ultima columna que corresponde a la etiqueta
          potencia=potencia+pow(matriz[fil][col]-matriz_Prueba[col],2);
        }
        raiz=sqrt(potencia);
        potencia=0;
        
        if(raiz<matriz_k[2][k-1]){
          matriz_k[2][k-1]=raiz;
          matriz_k[1][k-1]=matriz[fil][tam_col-1]; 
          
          for(i=0;i<k;i++){
             for(j=i+1;j<k;j++){
               if(matriz_k[2][i]>matriz_k[2][j]){
                 // distancia
                  aux=matriz_k[2][i];
                  matriz_k[2][i]=matriz_k[2][j];
                  matriz_k[2][j]=aux;
                 
                  aux_etiqueta=matriz_k[1][i];
                  matriz_k[1][i]=matriz_k[1][j];
                  matriz_k[1][j]=aux_etiqueta;
                }
              } 
            } 
        }
    } 
    
    for(i=0;i<etiquetas;i++){
      for(j=0;j<k;j++){
          if(matriz_eti[0][i]==matriz_k[1][j]){
            matriz_eti[1][i]++;
          }
        }
      }

    for(i=0;i<etiquetas-1;i++){
       if(matriz_eti[1][i]<matriz_eti[1][i+1])
        label=(int)matriz_eti[0][i+1];    
        else 
        label=(int)matriz_eti[0][i];      
      }
      a++;  
 return label;
};
