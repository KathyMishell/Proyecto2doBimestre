/* 
 * Universidad Técnica del Norte
 *              SISTEMAS EMBEBIDOS
 * Integrantes: Erazo Israel
 *              Guatemal Katherine
 *              Proyecto 2 bimestre
 *              
  */
 #include <avr/power.h>
 #include <avr/sleep.h>
 #include <avr/wdt.h>
 #include <EEPROM.h>
 //#include <LiquidCrystal.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 #include <SoftwareSerial.h>
 #include "datos.h"

 int S_MQ135=0;
 int S_MQ7 = 1;
 int limp =7;
 int contam=6;
 int dato=0;
 int respuesta;
 int eti1 = 1;
 int eti2 = 2;
 SoftwareSerial serial2(2,3); //llamamos al sofware serial 
  //LiquidCrystal lcd(13,12,11,10,9,8);
LiquidCrystal_I2C lcd(0x27,16,2);
int knn (int k, int etiquetas, int tam_col, int col_fil); // definir la func
void setup() {
Serial.begin(9600);
Serial2.begin(9600);
lcd.init();
////Encender la luz de fondo.
lcd.backlight();
//lcd.begin(16,2);
  pinMode(limp,OUTPUT);
  pinMode(contam,OUTPUT);
  dato = EEPROM.read(0);
  //dato = EEPROM.read(0);    
  //EEPROM.write(0,0);
   
  if(dato==1){
    S_MQ135 = analogRead(0); 
    S_MQ7 = analogRead(1);
    
    respuesta=knn(3,2,3,200);  
  switch(respuesta){
    case 1:
      Serial.print(eti1);
      Serial.print(",");
      delay(1);
      Serial.print(S_MQ135);  
      Serial.print(";");
      delay(1);
      Serial.println(S_MQ7);    
      digitalWrite(limp,LOW);
      digitalWrite(contam,HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.println("AIRE CONTAMINADO");
      lcd.setCursor(0,1);
      lcd.print(String("MQ135:")+String(S_MQ135));
      lcd.setCursor(9,1);
      lcd.print(String("MQ7:")+String(S_MQ7));
    break;
    case 2:
      Serial.print(eti2);
      Serial.print(",");
      delay(1);
      Serial.print(S_MQ135);  
      Serial.print(";");
      delay(1);
      Serial.println(S_MQ7);
      digitalWrite(limp,HIGH);
      digitalWrite(contam,LOW);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.println("AIRE LIMPIO   ");
      lcd.setCursor(0,1);
      lcd.print(String("MQ135:")+String(S_MQ135));
      lcd.setCursor(9,1);
      lcd.print(String("MQ7:")+String(S_MQ7));
      
    break;
  }
      }
  
  if(dato<3){    
      dato++;
      EEPROM.update(0,dato);
      wdt_enable(WDTO_4S);
      set_sleep_mode(SLEEP_MODE_IDLE);
      sleep_enable();      
    }
  else{      
      wdt_enable(WDTO_15MS);
      EEPROM.write(0,0);      
    } 
}

void loop() {
  if(dato<3){      
      delay(1000);
      sleep_mode();
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

float datos_prueba [3]={S_MQ135,S_MQ7,1};

 float matriz_k [3][k];
 for(;i<k;i++){
  matriz_k[0][i]=i+1.00;
  matriz_k[1][i]=0; 
  matriz_k[2][i]=2500.0+i;
  }
  i=0;

  float matriz_eti[2][etiquetas];
  for(;i<etiquetas;i++){
      matriz_eti[0][i]=i+1.0;
      matriz_eti[1][i]=0.0;
    }

   for(;fil<tam_fil;fil++){
      for(col=0;col<tam_col-1;col++){
          potencia=potencia+pow(matriz[fil][col]-datos_prueba[col],2);
        }
        raiz=sqrt(potencia);
        potencia=0;        
        if(raiz<matriz_k[2][k-1]){
          matriz_k[2][k-1]=raiz;
          matriz_k[1][k-1]=matriz[fil][tam_col-1]; 
          // ordenar matriz por metodo de burbuja
          for(i=0;i<k;i++){
             for(j=i+1;j<k;j++){
               if(matriz_k[2][i]>matriz_k[2][j]){
                 // distancia
                  aux=matriz_k[2][i];
                  matriz_k[2][i]=matriz_k[2][j];
                  matriz_k[2][j]=aux;
                  //etiqueta
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
 return label;
};
