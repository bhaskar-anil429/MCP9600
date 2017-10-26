#include<Wire.h>
#define Addr 0x64
long data1;
long data2;
long temp;
byte stat;
void setup()
{
  // Initialise I2C communication
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  temrmo_set();
  device_set();
  
}
int read_temp()
{
  Wire.beginTransmission(Addr);
  Wire.write(0x00);
  Wire.endTransmission();
   Wire.requestFrom(Addr, 2);
    if (Wire.available() == 2)
  {
   data1 = Wire.read();
   data2 = Wire.read();
//  Serial.println(data1);
//  Serial.println(data2);
   if((data1 & 0x80) == 0x80)
  {
    data1 = data1 & 0x7F;
   temp = 1024 - ( data1 * 16 + data2/16);
  Serial.print("Temperature :");
  Serial.print(temp);
  Serial.println("\n");
  }
  else 
  data1 = data1 *16;
  data2 = data2 * 0.0625;
//  Serial.println(data1);
//  Serial.println(data2);
  temp = data1 + data2;
//   temp = ( data1 * 16 + data2/16);
  Serial.print("Temperature :");
  Serial.print(temp);
  Serial.println("\n");
  }
}


int temp_stat()
{
  Wire.beginTransmission(Addr);
  Wire.write(0x04);
  Wire.endTransmission();
  delay(50);
  Wire.requestFrom(Addr, 1);
    if (Wire.available() == 1)
  {
   stat = Wire.read();
  }
 // Serial.print(stat);
  return stat;
}
int temp_stat_clr()
{
  Wire.beginTransmission(Addr);
  Wire.write(0x04);
  Wire.write(0x0F);
  Wire.endTransmission();
}

int temrmo_set()
{
  Wire.beginTransmission(Addr);
  Wire.write(0x05);
  Wire.write(0x00);
  Wire.endTransmission();
}

int device_set()
{
  Wire.beginTransmission(Addr);
  Wire.write(0x06);
  Wire.write(0x00);
  Wire.endTransmission();
}
void loop()
{
  
  temp_stat();
 //   char thermo_stat = &temp_stat;
    byte thermo_ready =  (stat && 0x40); 
//     Serial.println(stat); 
//     Serial.println(thermo_ready); 
    if(thermo_ready)
    {
      read_temp();
    //  Serial.print("hello");
    }
   temp_stat_clr();
delay(1000);
}
