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
///// this function will read the hot and cold junction temp
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
    byte low_temp = data1 && 0x80;
   if(low_temp)
   {
//    data1 = data1 & 0x7F;
//   temp = 1024 - ( data1 * 16 + data2/16);
  temp = ( data1 * 16 + data2/16) - 4096;
  Serial.print("Temperature :");
  Serial.print(temp);
  Serial.println("\n");
  }
  else
  {
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
}

/// this function can be used to see if the temp conversion is complete or not
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

/// this functon can be used to clear the temp conversion flag
int temp_stat_clr()
{
  Wire.beginTransmission(Addr);
  Wire.write(0x04);
  Wire.write(0x0F);
  Wire.endTransmission();
}
////// this function can be used to set the thermocuple configuration 
int temrmo_set()
{
  Wire.beginTransmission(Addr);
  Wire.write(0x05);
  Wire.write(0x00);
  Wire.endTransmission();
}
////////////// this function can be used to set the device config
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
    byte thermo_ready =  (stat && 0x40); 

    if(thermo_ready)
    {
      read_temp();
    //  Serial.print("hello");
    }
   temp_stat_clr();
delay(1000);
}
