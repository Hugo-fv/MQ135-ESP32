/* Programa para medir el CO2 en el ambiente con en sensor MQ135
 * PAGINAS IMPORTANTES
 * https://apps.automeris.io/wpd/ -OBTENER DATOS DE LA CURVA
 * https://github.com/Hugo-fv/MQ135-ESP32 -REPOSITORIO
 */

//Variales
float co2_actual = 412.97; // Niveles de CO2 en la atmosfera (calibración)
float R_load = 1000; //Resistencia de carga (PARA MAYOR PRESICION, DEBE SER DE 20kOHM)
float RS_mean = 0; //Resistencia del sensor (promedio) Rs = 1024*(RL/adc) - RL
float R0; //Resistencia del sensor con 100ppm de NH3 (calibracion)
float a = 5.1559, b = -0.347; // Coeficientes de la formula f(x) = ax^b (regresion exponencial)
float ppm; //PPM del CO2
float V_adc; //VOLTAJE DEL ADC
float alpha; //RS/R0
//Constantes
const int res_micro = 1024; //Resolucion del ADC del microcontrolador
const int V_ref = 5; //Voltaje entregado por el microcontrolador 
//Objetos
#define adc A0
//Arreglos
float RS[10]; //Almacenar 10 valores de RS (involucra adc)

void setup() {
  Serial.begin (9600);
  pinMode(adc, INPUT); 
  //Calculamos R0 (resistencia de calibracion)
  R0 = (2084.0)/(a*pow(co2_actual, b)); //Valor obtenido por el script de calibracion
}

void loop() {
  //Obtenemos el promedio de RS
  for (int i = 0; i<10; i++){
    V_adc = analogRead(adc);
    RS[i] = res_micro*(R_load/V_adc)-R_load;
  }
  for (int i = 0; i<10; i++){
    RS_mean = RS_mean + RS[i];
  }
  RS_mean = RS_mean/10;
  //Serial.println(RS_mean);
  //Serial.println(R0);
  //Coeficiente RS/R0
  alpha = RS_mean/R0;
  //Obtenemos el CO2 en ppm
  ppm = pow((alpha/a), 1/b);
  Serial.println(ppm);
  delay(100);
}
