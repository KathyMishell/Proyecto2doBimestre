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
 #include <MsTimer2.h>
 #include <EEPROM.h>

int dato=0;
int on=0;
  
void setup() {
  Serial.begin(9600);
 
  dato = EEPROM.read(0);   
  if(dato==1){
      Serial.print(String("{")+String(analogRead(0))+String(",")+String(analogRead(1)));
      Serial.println("},");
      }
    //dato = EEPROM.read(0);    
  //EEPROM.write(0,0);

  if(dato<75){    
      dato++;
      EEPROM.update(0,dato);
      wdt_enable(WDTO_4S);
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
    }
  else{
      wdt_enable(WDTO_15MS);
      EEPROM.write(0,0);
      
    }
 
}

void loop() {
  if(dato<75){
      
      delay(1000);
      sleep_mode();
    }

}
