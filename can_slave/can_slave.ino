#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication

struct can_frame canMsg; 
MCP2515 mcp2515(10);                 // SPI CS Pin 10 
 
void setup() {
  SPI.begin();                       //инициализируем связь по протоколу SPI
  Serial.begin(115200);                //инициализируем последовательную связь со скоростью 9600 бод 
  Serial.println("Serial start");
  mcp2515.reset();                          
  mcp2515.setBitrate(CAN_125KBPS,MCP_8MHZ); //устанавливаем скорость шины CAN 500 кбит/с и частоту кварцевого генератора 8 МГц
  mcp2515.setNormalMode();                  //устанавливаем CAN-шину в обычный режим
}
void loop() 
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
     int x = canMsg.data[0];         
     int y = canMsg.data[1];       
        
      Serial.print("Serial recive ");
      Serial.print(x);
      Serial.print(' ');
      Serial.println(y);
    }
}
