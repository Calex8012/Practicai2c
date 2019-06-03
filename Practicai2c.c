#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use I2C(Master,Fast,sda=PIN_C4,scl=PIN_C3)

#define RTC_DS1307_WRITE_ADDRESS 0xD0
#define RTC_DS1307_READ_ADDRESS 0xD1
#define DIRECCION_INICIO_LECTURA_DATOS 0X00
#define ACK 0

void rtc_get_time(byte &hr, byte &min, byte &sec, byte &dia, byte &mes, byte &year, &impresion);
int hr,sec,min,year,mes,dia;
int BCDaBIN(byte bcd);
int impresion=0;

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
   #use fast_io(c)
#endif

void main (void){
   while(1){
       if(impresion==1)
      {
         printf("Hora %u,Minuto %u,Segundos %u",hr,min,sec);
         impresion=0;
      }
   }
}
int BCDaBIN(BYTE bcd)
{
   int varia;
   varia=bcd;
   varia>>=1;
   varia &= 0x78;
   return (varia + (varia>>2) + (bcd & 0x0f));
}

void rtc_get_time(byte &hr, byte &min, byte &sec, byte &dia, byte &mes, byte &year, &impresion){
   i2c_start();
   i2c_write(RTC_DS1307_WRITE_ADDRESS);
   i2c_write(DIRECCION_INICIO_LECTURA_DATOS);
   i2c_start();
   i2c_write(RTC_DS1307_READ_ADDRESS);
   sec=BCDaBIN(i2c_read()&0x7F);
   min=BCDaBIN(i2c_read()&0x7F);
   hr=BCDaBIN(i2c_read()&0x3F);
   dia=BCDaBIN(i2c_read()&0x07);
   mes=BCDaBIN(i2c_read()&0x1F);
   year=BCDaBIN(i2c_read(ACK)&0xF1);
   i2c_stop();
   impresion=1;
}
