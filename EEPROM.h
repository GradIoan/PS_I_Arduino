/*
 * EEPROM.h
 *
 * Created: 12/3/2016 10:46:59 PM
 *  Author: Ionut
 */ 

  #include <avr/io.h>
  #include <avr/interrupt.h>

  void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
  unsigned char EEPROM_read(unsigned int uiAddress);
