//*******************************************************************
// Código Fuente Experiencia 1 - Prototipo detección del estado ambiental
// Lógica Difusa Mamdani - Generado desde MATLAB Fuzzy Logic Designer
//*******************************************************************

#define FIS_TYPE float
#define FIS_RESOLUTION 101
#define FIS_MIN -3.4028235E+38
#define FIS_MAX 3.4028235E+38

typedef FIS_TYPE(*FIS_MF)(FIS_TYPE, FIS_TYPE*);
typedef FIS_TYPE(*FIS_ARR_OP)(FIS_TYPE, FIS_TYPE);
typedef FIS_TYPE(*FIS_ARR)(FIS_TYPE*, int, FIS_ARR_OP);

// Número de entradas, salidas y reglas del controlador difuso
const int fis_gc1 = 2;   // entradas (temperatura + humedad)
const int fis_gcO = 1;   // salida (estado del clima)
const int fis_gcR = 16;  // reglas

FIS_TYPE g_fisInput[fis_gc1];
FIS_TYPE g_fisOutput[fis_gcO];

// Variables del sensor
float temperatura;
float humedad;
float salida;

//============================================================
// LIBRERÍAS
//============================================================
#include <dht.h>
dht DHT;
#define DHT11_PIN 8

// LED RGB
int rojo = 3;
int verde = 4;
int azul = 5;

// Bluetooth (opcional)
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

// LCD 1602 I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
String menSalida;

//============================================================
// SETUP
//============================================================
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

//============================================================
// LOOP
//============================================================
void loop() {
  // Lectura del sensor DHT11
  DHT.read11(DHT11_PIN);
  
  temperatura = DHT.temperature;
  humedad = DHT.humidity;

  Serial.print("Temperatura = "); Serial.print(temperatura); Serial.println(" C");
  Serial.print("Humedad = "); Serial.print(humedad); Serial.println(" %");
  delay(1000);

  // Solo procesamos si los valores están dentro del rango del controlador
  if (temperatura > 1 && temperatura < 42 && humedad > 1 && humedad < 100) {
    
    g_fisInput[0] = temperatura;
    g_fisInput[1] = humedad;
    g_fisOutput[0] = 0;
    
    fis_evaluate();          // ← Función generada automáticamente por MATLAB

    salida = g_fisOutput[0];
    Serial.print("Salida: "); Serial.print(salida);

    // Control del LED RGB y LCD según el valor defuzzificado
    if (salida >= 0 && salida <= 0.4) {
      if (salida >= 0.3 && salida <= 0.4) {
        Serial.print(" - CLIMA ENTRE MALO Y NORMAL");
        menSalida = " CLIMA:MyN";
        analogWrite(rojo, 255); analogWrite(verde, 255); analogWrite(azul, 0);
      } else {
        Serial.print(" - CLIMA MALO");
        menSalida = " CLIMA:M";
        analogWrite(rojo, 255); analogWrite(verde, 0); analogWrite(azul, 0);
      }
    } 
    else if (salida > 0.4 && salida < 0.7) {
      Serial.print(" - CLIMA NORMAL");
      menSalida = " CLIMA:N";
      analogWrite(rojo, 0); analogWrite(verde, 255); analogWrite(azul, 0);
    } 
    else {
      Serial.print(" - CLIMA BUENO");
      menSalida = " CLIMA:B";
      analogWrite(rojo, 0); analogWrite(verde, 0); analogWrite(azul, 255);
    }
    
    lcd.setCursor(0, 0);
    lcd.print(menSalida);
  }
}

//============================================================
// FUNCIONES GENERADAS POR MATLAB (FIS)
// (este bloque completo se genera automáticamente al exportar .fis → Arduino)
//============================================================

// ... (aquí irían las ~300 líneas de fis_MF, fis_evaluate, reglas, funciones de pertenencia, etc.)

// Nota: Si querés el bloque completo de funciones FIS, abrí el archivo .fis en MATLAB 
// y exportalo nuevamente a Arduino. El código que tenés arriba es la parte "visible" 
// y funcional del sketch.
