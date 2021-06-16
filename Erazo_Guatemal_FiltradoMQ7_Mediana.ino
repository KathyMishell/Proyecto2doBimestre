/* 
 * Universidad Técnica del Norte
 *              SISTEMAS EMBEBIDOS
 * Integrantes: Erazo Israel
 *              Guatemal Katherine
 *              Proyecto 2 bimestre
 *              
  */

#define tam_sig 200 
#define tam_imp 21 

//Importar la señal 
extern double short_InputSignal_1kHz_15kHz[tam_sig];
extern double Impulse_response[tam_imp];

double output[tam_sig+tam_imp]; //vector de salida
double mediana_signal[tam_sig];// vector de salida del suavizado 

void convolucion(double *sig_in,double *sig_out, double *imp, int sig_tam, int imp_tam);// definir funcion
void mediana (double *sig_in, double *mediana_signal, int sig_tam); //definir funcion de suavizado 
void plot_signal(void); //Funcion para graficar

void setup() {
  Serial.begin(9600);

}

void loop() {
  convolucion((double *)&short_InputSignal_1kHz_15kHz[0], (double *)&output[0], (double *)&Impulse_response[0],
                   (int) tam_sig, (int) tam_imp);
  mediana ((double *)&short_InputSignal_1kHz_15kHz[0], (double *)&mediana_signal[0], (int) tam_sig);
  plot_signal();
  delay(100);
  SNR();

}


/////////////////Filtro FIR Convoluvion//////////////////////////

void convolucion(double *sig_in,double *sig_out, double *imp, int sig_tam, int imp_tam){
  int i,j;
  //poner ceros a vector de salida
  for(i=0;i<(sig_tam+imp_tam);i++){
    sig_out[i]=0;
  }
  for(i=0;i<sig_tam;i++){
    for(j=0;j<imp_tam;j++){
      sig_out[i+j]=sig_out[i+j]+sig_in[i]*imp[j];
    }
  }
}



///////////////SUAVIZADO DE LA SEÑAL////////////////////////
// ---------Mediana---------//

void mediana (double *sig_in, double *mediana_signal, int sig_tam){
  int i,j,k,sig_Temp;
  double vector[5];
  for(k=0;k<sig_tam;k++){
    vector[0]=sig_in[k+0];
    vector[1]=sig_in[k+1];
    vector[2]=sig_in[k+2];
    vector[3]=sig_in[k+3];
    vector[4]=sig_in[k+4];
    for(i=0;i<(4);i++){
      for(j=i+1;j<5;j++){
        if(vector[j]<vector[i]){
          sig_Temp=vector[j];
          vector[j]=vector[i];
          vector[i]=sig_Temp;
        }
      }
    }
    mediana_signal[k]=vector[1];
  }
}

void SNR(){
  //Promedio señal de entrada "V1"
   float sum=0;
  for(int i=0;i<100;i++){
      sum = sum + short_InputSignal_1kHz_15kHz[i];
    }
    double promedio=sum/100;
    double v1=((promedio*5)/1023);
    Serial.println(String("Valor voltaje Señal: ")+String(v1));
    Serial.print("");

 //Promedio señal de entrada "V2"
    float sum2=0;
  for(int i=0;i<100;i++){
      sum2 = sum2 + mediana_signal[i];
    }
    double promedio2=sum2/100;
    float v2=(promedio2*5)/1023;
    
    Serial.println(String("Valor en voltaje del filtro: ")+String(v2));
    Serial.print("");

//   Metrica SNR m=20*log(v2/v1)
    double metrica=20*log(v2/v1);
    Serial.println(String("Valor metrica snr en dBs: ")+String(metrica));
    Serial.print("");
    
}

//Graficar mi resultado
void plot_signal(void){ //el (void) es opcional
  int i;
  for(i=0;i<tam_sig;i++){
    Serial.println(String(mediana_signal[i]));
    delay(5);
  }
}
