#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
float getTemp(int file, int address);

void main() {
  int file;
  char *bus = "/dev/i2c-1";
  if ((file = open(bus, O_RDWR)) < 0)
  {
   printf("0 0");
       exit(1);
         }
while(1)
{
    float temp1 = getTemp(file, 0x60);
//      float temp2 = getTemp(file, 0x67);

        printf("%f", temp1);
        printf(" \n");
        sleep(1);
}
          exit(0);

}
float getTemp(int file, int address) {

        ioctl(file, I2C_SLAVE, address);

        char config[2] = {0};
        config[0] = 0x05;
        config[1] = 0x00;
        write(file, config, 2);
        config[0] = 0x06;
        config[1] = 0x00;
        write(file, config, 2);
        // check status flag
        char reg1[1] = {0};
        reg1[1] = 0x04;
        write(file, reg1, 1);
        //char stat[1] = {0};
        char data1[1] = {0};

    if(read(file, data1, 1) != 1) {
                return 0;
                  } else {
        char stat = (data1[1]);

        printf("Stat   ");
        printf("%x",stat);
        printf("   \n");
                }
        char reg[1] = {0x00};
        write(file, reg, 1);
        char data[2] = {0};
        if(read(file, data, 2) != 2)
        {
        printf("Erorr : Input/output Erorr \n");
        }
        else
        {
        int low_temp = data[0] & 0x80;
            float r;
            if (low_temp) {
                 // printf("Low temp\n");
         r = data[0] * 16 + data[1] / 16 - 4096;
            return r;
            } else {
            // printf("High temp\n");
          r = data[0] * 16 + data[1] * 0.0625;
           return r;
           sleep(1);
              }
                  }
                }
