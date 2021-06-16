/* 
 * Universidad Técnica del Norte
 *              SISTEMAS EMBEBIDOS
 * Integrantes: Erazo Israel
 *              Guatemal Katherine
 *              Proyecto 2 bimestre
 *              
  */

#define N 200
#define Nk 5
extern double Signal[N];
extern double kernel[Nk];
float den=0, zj=0;
double h,f,m;
double c[200];

void setup()
{
Serial.begin(9600);
}

void loop(){
  den=0;
  for (int i = 0; i < Nk; i++){
    den=den+kernel[i];
  }
  
for (int i = 0; i < N-Nk; i++){
  for (int i2 = 0; i2 < Nk; i2++){
       c[i]=c[i]+kernel[i2]*Signal[i2+i];
  }
   c[i]=c[i]/den;
   Serial.print(String("Filtrado: ")+String(c[i]+100));
   Serial.print(",");
   Serial.println(String("Señal Original: ")+String(Signal[i+2]));
   c[i]=0;
  }

 SNR();
}

void SNR(){

//Promedio señal original v1
  float sum=0;
  for(int i=0;i<100;i++){
      sum = sum + Signal[i];
    }
     double promedio=sum/100;
    double v1=((promedio*5)/1023);
    Serial.println(String("Valor voltaje Señal: ")+String(v1));
    Serial.print("");
    
//Promedio señal Suavizada (v2) metodo de Gauss
     double sum2=0;
  for(int i=0;i<100;i++){
      sum2 = sum2 + Signal[i+1];
    }
    double promedio2=sum2/100;
    float v2=(promedio2*5)/1023;
    Serial.println(String("Valor en voltaje del filtro: ")+String(v2));
    Serial.print("");

 //Metrica SNR m=20*log(v2/v1)
    double metrica=20*log(v2/v1);
    Serial.println(String("Valor metrica snr en dBs: ")+String(metrica));
    Serial.print("");
    
  }
  
