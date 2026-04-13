// Experiencia 2 - Mecanismo de avance autoajustable
// Código basado en el artículo de Encina et al.

#include <efll.h>
#include <StepperMotor.h>

// Definición de pines
const int TriggerPin = 9;
const int EchoPin = 10;

// Motores paso a paso (ejemplo con Adafruit Motor Shield)
StepperMotor motor1(1);
StepperMotor motor2(2);

// Variables
int cm = 0;
int cma = 0;
int vel = 0;

// Crear sistema difuso
Fuzzy *difuso = new Fuzzy();

// Definir conjuntos difusos para DISTANCIA
FuzzySet *cerca = new FuzzySet(10, 30, 40);
FuzzySet *distante = new FuzzySet(35, 70, 90);
FuzzySet *lejos = new FuzzySet(80, 150, 200);

// Definir conjuntos difusos para VELOCIDAD
FuzzySet *lento = new FuzzySet(0, 10, 20);
FuzzySet *crucero = new FuzzySet(9, 40, 60);
FuzzySet *corrida = new FuzzySet(50, 70, 100);

// Definir conjuntos difusos para AVANCE (salida)
FuzzySet *acercar = new FuzzySet(0, 5, 10);
FuzzySet *seguir = new FuzzySet(7, 20, 50);
FuzzySet *atrapar = new FuzzySet(45, 70, 100);

// Agregar conjuntos al sistema
difuso->addFuzzySet(distancia, cerca);
difuso->addFuzzySet(distancia, distante);
difuso->addFuzzySet(distancia, lejos);
difuso->addFuzzySet(velocidad, lento);
difuso->addFuzzySet(velocidad, crucero);
difuso->addFuzzySet(velocidad, corrida);
difuso->addFuzzySet(avance, acercar);
difuso->addFuzzySet(avance, seguir);
difuso->addFuzzySet(avance, atrapar);

// Reglas del controlador difuso
FuzzyRuleAntecedent *cercaYLento = new FuzzyRuleAntecedent();
cercaYLento->joinWithAND(cerca, lento);
FuzzyRuleConsequent *acercarCons = new FuzzyRuleConsequent();
acercarCons->addOutput(acercar);
FuzzyRule *regla1 = new FuzzyRule(1, cercaYLento, acercarCons);
difuso->addFuzzyRule(regla1);

FuzzyRuleAntecedent *cercaYCrucero = new FuzzyRuleAntecedent();
cercaYCrucero->joinWithAND(cerca, crucero);
FuzzyRuleConsequent *seguirCons = new FuzzyRuleConsequent();
seguirCons->addOutput(seguir);
FuzzyRule *regla2 = new FuzzyRule(2, cercaYCrucero, seguirCons);
difuso->addFuzzyRule(regla2);

FuzzyRuleAntecedent *cercaYCorrida = new FuzzyRuleAntecedent();
cercaYCorrida->joinWithAND(cerca, corrida);
FuzzyRule *regla3 = new FuzzyRule(3, cercaYCorrida, atraparCons);
difuso->addFuzzyRule(regla3);

FuzzyRuleAntecedent *distanteYLento = new FuzzyRuleAntecedent();
distanteYLento->joinWithAND(distante, lento);
FuzzyRule *regla4 = new FuzzyRule(4, distanteYLento, acercarCons);
difuso->addFuzzyRule(regla4);

FuzzyRuleAntecedent *distanteYCrucero = new FuzzyRuleAntecedent();
distanteYCrucero->joinWithAND(distante, crucero);
FuzzyRule *regla5 = new FuzzyRule(5, distanteYCrucero, seguirCons);
difuso->addFuzzyRule(regla5);

FuzzyRuleAntecedent *distanteYCorrida = new FuzzyRuleAntecedent();
distanteYCorrida->joinWithAND(distante, corrida);
FuzzyRule *regla6 = new FuzzyRule(6, distanteYCorrida, atraparCons);
difuso->addFuzzyRule(regla6);

FuzzyRuleAntecedent *lejosYLento = new FuzzyRuleAntecedent();
lejosYLento->joinWithAND(lejos, lento);
FuzzyRule *regla7 = new FuzzyRule(7, lejosYLento, acercarCons);
difuso->addFuzzyRule(regla7);

FuzzyRuleAntecedent *lejosYCrucero = new FuzzyRuleAntecedent();
lejosYCrucero->joinWithAND(lejos, crucero);
FuzzyRule *regla8 = new FuzzyRule(8, lejosYCrucero, seguirCons);
difuso->addFuzzyRule(regla8);

FuzzyRuleAntecedent *lejosYCorrida = new FuzzyRuleAntecedent();
lejosYCorrida->joinWithAND(lejos, corrida);
FuzzyRule *regla9 = new FuzzyRule(9, lejosYCorrida, seguirCons);
difuso->addFuzzyRule(regla9);

void setup() {
    Serial.begin(9600);
    pinMode(TriggerPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    motor1.setSpeed(70);
    motor2.setSpeed(70);
}

void loop() {
    velocidad();
    difuso->setInput(1, cm);
    difuso->setInput(2, vel);
    difuso->fuzzify();
    float avanceMotor = difuso->defuzzify(1);
    
    Serial.print("Avance: ");
    Serial.println(avanceMotor);
    
    int pasos = avanceMotor * 3;
    Serial.print("Pasos: ");
    Serial.println(pasos);
    
    for (int paso = 0; paso <= pasos; paso++) {
        motor1.step(1, FORWARD, DOUBLE);
        motor2.step(1, BACKWARD, DOUBLE);
    }
    delay(100);
}

void velocidad() {
    cm = ping(TriggerPin, EchoPin);
    vel = (cm - cma);
    Serial.print("Distancia: ");
    Serial.print(cm);
    Serial.print(" Velocidad: ");
    Serial.println(vel);
    cma = cm;
    delay(1000);
}

int ping(int TriggerPin, int EchoPin) {
    long duration, distanceCm;
    digitalWrite(TriggerPin, LOW);
    delayMicroseconds(4);
    digitalWrite(TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);
    duration = pulseIn(EchoPin, HIGH);
    distanceCm = duration * 10 / 292 / 2;
    return distanceCm;
}
