// Cantidad de pulsos
#define TRAIN_LENGTH 32
// En microsegundos
#define LOW_LIMIT 600
#define HIGH_LIMIT 1800
#define INIT_LIMIT 4000
#define IN 2
#define LED 13
long start, delta = 0;
uint32_t value;
int pos = 0;
boolean has_value = false;
unsigned int key[10];
void inputPin() {
  noInterrupts();
  if (has_value) return;
  if (digitalRead(IN) == HIGH) {
    start = micros();
  }
  else {
    delta = micros() - start;
    if (delta < LOW_LIMIT) {
      value <<= 1;
      value |= 1;
      ++pos;
    }
    else if (delta < HIGH_LIMIT) {
      value <<= 1;
      value |= 0;
      ++pos;
    }
    else if (delta > INIT_LIMIT) {
      value = 0;
      pos = 0;
    }
    if (pos == TRAIN_LENGTH) {
      has_value = true;
    }
  }
  interrupts();
}
void setup()
{
  key[0] = 0x9768;
  key[1] = 0xCF30;
  key[2] = 0xE718;
  key[3] = 0x857A;
  key[4] = 0xEF10;
  key[5] = 0xC738;
  key[6] = 0xA55A;
  key[7] = 0xBD42;
  key[8] = 0xB54A;
  key[9] = 0xAD52;
  Serial.begin(9600);
  pinMode(IN, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  attachInterrupt(0, inputPin, CHANGE);
}
void loop()
{
  int i;
  if (has_value) {
    Serial.print("V: ");
    Serial.println(value);
    Serial.println(value & 0x0000FFFF, HEX);
    i = 0;
    while(i<10 && (key[i] != (value & 0x0000FFFF))) ++i;
    //Serial.println(i);
    //while(i--) {
     // digitalWrite(LED, HIGH);
     // delay(400);
     // digitalWrite(LED, LOW);
     // delay(200);
    //}
    Serial.println(i);
    has_value = false;
    pos = 0;
  }
}
