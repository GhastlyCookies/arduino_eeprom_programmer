
int iter  = 1; //ignore
byte clk  = 2; //shift register clk pin
byte latch= 3; //shift register latch pin
byte ser  = 4; //shift register serial input 
byte wEn  = 5; //EEPROM write enable pin(ACTIVE LOW)
byte mem  = 6; //start of the data pin sequence(this means pin 6 should get the LSB from EEPROM)
byte oE   = 1; //EEPROM output enable pin(ACTIVE LOW)

byte data[] = {B1111110, //0
               B1001000, //1
               B0111101, //2
               B1101101, //3
               B1001011, //4
               B1100111, //5
               B1110111, //6
               B1001100, //7
               B1111111, //8
               B1101111,
               B1011111,
               B1110011,
               B0110110,
               B1111001,
               B0110111,
               B0010111};
byte data2[] ={B1111110, //0
               B1001000, //1
               B0111101, //2
               B1101101, //3
               B1001011, //4
               B1100111, //5
               B1110111, //6
               B1001100, //7
               B11111111, //-8
               B11001100, //-7
               B11110111, //-6
               B11100111, //-5
               B11001011, //-4
               B11101101, //-3
               B10111101, //-2
               B11001000, //-1
               };               
byte erase[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};              

void memContents(){ //show contents of the memory *currently configured upto 256 locations but can be modified
  byte num = 0;
  Serial.println("Current Memory contents:");
  digitalWrite(oE,LOW);
  delay(10);
  for(int i=6; i<=13; i++){pinMode(i,INPUT);}
  for(int i=0; i<=255; i++){
    num = 0;
    digitalWrite(latch,LOW);
    shiftOut(ser,clk,MSBFIRST,i);
    digitalWrite(latch,HIGH);
    delay(1);
    for(int j=mem; j<=13; j++){  
    num = num + (digitalRead(j)<<(j-mem));
    }
    Serial.print(i,DEC);
    Serial.print("\t");
    Serial.print(num,BIN);
    Serial.print("\t");
    Serial.println(num,HEX);  
    }
    for(int i=6; i<=13; i++){pinMode(i,OUTPUT);}  
}

void memWritedata(byte ledata[],int lim,int loc){ //write data to the EEPROM *memWrite(data array, number of locations to be written, begining location in EEPROM)
  Serial.println("GhastlyCookies: writting to memory....");
  digitalWrite(oE,HIGH);
  delay(10);
  for(int i=6; i<=13; i++){pinMode(i,OUTPUT);}
  for(int i=(0+loc); i<=(lim+loc); i++){
    digitalWrite(latch,LOW);
    shiftOut(ser,clk,MSBFIRST,i);
    digitalWrite(latch,HIGH);
    delay(1);
    for(int j=6; j<=13; j++){
      digitalWrite(j,bitRead(ledata[(i-loc)],(j-mem)));
      }
    delay(100);  
    digitalWrite(wEn,LOW);
    delay(10);
    digitalWrite(wEn,HIGH);
    delay(10);    
    }
 Serial.print(lim+1,DEC);
 Serial.println(" bytes written....");
 Serial.println("GhastlyCookies: done.");     
}

void showData(byte ledata[],int lim,int loc){
  Serial.println(" ");
  Serial.println("GhastlyCookies: You have entered following data to be programmed:"); 
  for(int i=(0+loc); i<=(lim+loc); i++){
    Serial.print(i,DEC);
    Serial.print("\t");
    Serial.print(ledata[i],BIN);
    Serial.print("\t");
    Serial.println(ledata[i],HEX);  
    }
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0; i<=13; i++){pinMode(i,OUTPUT);}
  digitalWrite(oE,HIGH);
  digitalWrite(wEn,HIGH);
  for(int i=6; i<=13; i++){digitalWrite(i,LOW);}
}

void loop() {
if(iter > 0){
  int datalim = (sizeof(data)-1);
  int eraselim = (sizeof(erase)-1);
  int data2lim = (sizeof(data2)-1);
  
  memContents();
  memWritedata(data,datalim,0);
  memWritedata(data2,data2lim,16);
  memContents();          
}
iter=0;
delay(1000);  
}
