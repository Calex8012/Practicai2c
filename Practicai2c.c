#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use I2C(Master,Fast,sda=PIN_C4,scl=PIN_C3)

#define RTC_DS1307_WRITE_ADDRESS 0xD0
#define RTC_DS1307_READ_ADDRESS 0xD1
#define DIRECCION_INICIO_LECTURA_DATOS 0X00
#define ACK 0

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
   #use fast_io(c)
#endif

void main (void){
   while(1){
      
   }
}
