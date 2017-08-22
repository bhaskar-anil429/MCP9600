# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
#https://store.ncd.io/product/mcp9600-k-type-thermocouple-i2c-mini-module/
import smbus
import time
address = 0x65
# Get I2C bus
bus = smbus.SMBus(1)
#bus.write_byte_data(address, 0xC0, 0x00)
# config sensor for thermocouple type and filter
bus.write_byte_data(address, 0x05, 0x07)
# config sensor for sample and mode
bus.write_byte_data(address, 0x06, 0x7c)
#bus.write_byte(address,0xC0)

while True:
        bus.write_byte(address,0x00)
        data = bus.read_i2c_block_data(address, 0x00, 2)
        temp =( data[0]*16 + data[1]/16)
        ftemp = temp*1.8+32
        print "temp in C : %.2f temp" %temp
        print "temp in f : %.2f ftemp" %ftemp
        time.sleep(1)
