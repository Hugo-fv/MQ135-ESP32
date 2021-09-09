  //Calcular R0 con 5 minutos
float RL = 1000.0;
int i = 0;
float RS = 0.0;
bool bandera = 0;
float adc;
unsigned long t_i = 0, t_f = 0;
unsigned long tiempo_final_local = 0, tiempo_inicial_local=0;
void setup() {
  pinMode (A0, INPUT);
  pinMode (13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (bandera != 1){
    t_f = millis();
    if (t_f - t_i < 300000){
      digitalWrite(13, 1);
      tiempo_final_local = millis();
      if (tiempo_final_local - tiempo_inicial_local >= 1000){
        tiempo_inicial_local = tiempo_final_local;
        adc = analogRead(A0);
        RS = RS + 1024*(RL/adc)-RL;
        i = i+1;
        Serial.println(i);
        Serial.println(RS);
      }
    }
    if (t_f - t_i > 300000){
     digitalWrite(13, 0);
     RS = RS/;i
     Serial.print("RS promedio:");
     Serial.print(RS);
     bandera = 1;
  }

  }
  
}
