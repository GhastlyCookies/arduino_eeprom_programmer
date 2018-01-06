# arduino_eeprom_programmer
You do not really need to buy a $50 EEPROM programmer when you can make one yourself on a breadboard with an Arduino, now we are limited by the number of pins on arduino sometimes as i have a uno which only has 13 digital pins so you can also use a shift register like me to shift in the bits into parallel pins of the EEPROM

NOTE: PIN CONNECTIONS ARE MENTIONED IN THE CODE.

memWritedata() \\Writing to memory with custom array size and custom memory location.
memShowcontents() \\display all the contents within selected range default is 256 locations starting from 0 but can be increased.
showData() \\display data that is about to be written.

Here is a serial com port dump from my display EEPROM with signed and unsigned binary numbers encoded as 7 segment display characters:

[[https://addzlabs.files.wordpress.com/2018/01/untitled2.jpg?w=680|alt=octocat]]
