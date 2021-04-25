//Programa: Teste GY-521
// Publicação: Blog do Arduino Ômega.
//Programador: Engº Leandro Castro.
//Baseado no programa original de JohnChi

//Carrega a biblioteca Wire
#include<Wire.h>

const int MPU = 0x68; // Variável que irá armazenar o endereço do módulo
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; //Criando variaveis de inclinação e acelaração.

void setup()
{
  Serial.begin(9600); // Iniciando objeto serial com parâmetro de taxa de transmissão
  
  Wire.begin(); // Iniciando objetos do módulo
  Wire.beginTransmission(MPU) // Adicionando tipo de CI do módulo;
  Wire.write(0x6B);

  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

}
void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // Começando com o registrador 0x3B (ACCEL_YOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU, 14, true);
  //Armazena o valor dos sensores nas variáveis correspondentes
  AcY = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_YOUT_H) & 0x3C (ACCEL_YOUT_L)
  AcX = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_XOUT_H) & 0x3E (ACCEL_XOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

 
  
  //Envia valor X do acelerometro para a serial e o LCD
  Serial.print("Inclinacao X = "); Serial.print(AcX);
  
 
 //Envia valor Y do acelerometro para a serial e o LCD
  Serial.print(" | Inclinacao Y = "); Serial.print(AcY);

  //Envia valor Z do acelerometro para a serial e o LCD
  Serial.print(" | Inclinacao Z = "); Serial.print(AcZ);
  

 //Envia valor X do giroscopio para a serial e o LCD
  Serial.print(" | Vel.Inclinacao X = "); Serial.print(GyX);
 

 //Envia valor Y do giroscopio para a serial e o LCD
  Serial.print(" | Vel.Inclinacao Y = "); Serial.print(GyY);

  //Envia valor Z do giroscopio para a serial e o LCD
  Serial.print(" | Vel.Inclinacao Z = "); Serial.println(GyZ);

  //Aguarda 100 ms e reinicia o processo
  delay(100);
}
