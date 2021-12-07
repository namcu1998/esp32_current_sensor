#define INPUT_CURRENT_SENSOR 32
#define INPUT_VOLTAGE_SENSOR 34
double mVperAmp = 50;
double ACSoffset = 1136;
float  R1_VOLTAGE = 68000; //68K
float  R2_VOLTAGE = 6800; // 6.8K

double return_current_value(int pin_no)
{
  double tmp = 0;
  double avg = 0;
  double ADCVoltage = 0;
  double Amps = 0;
  for (int z = 0; z < 150; z++)
  {
    tmp = tmp + analogRead(pin_no);
  }
  avg = tmp / 150;
  ADCVoltage = ((avg / 4095.0) * 3300); // Gets you mV
  Amps = ((ADCVoltage - ACSoffset) / mVperAmp);
  return Amps;
}

double return_voltage_value(int pin_no)
{
  double tmp = 0;
  double ADCVoltage = 0;
  double inputVoltage = 0;
  double avg = 0;
  for (int i = 0; i < 150; i++)
  {
    tmp = tmp + analogRead(pin_no);
  }
  avg = tmp / 150;
  ADCVoltage = ((avg * 3.3) / (4095)) + 0.138;
  inputVoltage = ADCVoltage / (R2_VOLTAGE / (R1_VOLTAGE + R2_VOLTAGE)); // formula for calculating voltage in i.e. GND
  return inputVoltage;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float input_voltage = abs(return_voltage_value(INPUT_VOLTAGE_SENSOR));
  float input_current = abs(return_current_value(INPUT_CURRENT_SENSOR));
  input_current = input_current - 0.025;
  Serial.println(input_current);  
}




















