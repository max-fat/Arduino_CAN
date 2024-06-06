#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

struct can_frame canMsg;
MCP2515 mcp2515(10);

  int h = 0x1;       //считываем значение влажности
  int t = 0x77;    // считываем значение температуры
  
void setup() 
{
  while (!Serial);
  Serial.begin(115200);
  
  SPI.begin();               //инициализация связи по протоколу SPI

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS,MCP_8MHZ); //устанавливаем скорость шины CAN 500 кбит/с и частоту кварцевого генератора 8 МГц
  mcp2515.setNormalMode();
}
void loop() 
{

  canMsg.can_id  = 0x02;           // устанавливаем CAN id в 0x036
  canMsg.can_dlc = 8;               // длина поля данных CAN = 8
  canMsg.data[0] = h;               //обновляем значение влажности в поле [0]
  canMsg.data[1] = t;               // обновляем значение температуры в поле [1]
  canMsg.data[2] = 0x00;            //все остальные поля устанавливаем в 0
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg);     //передаем CAN сообщение
  Serial.print("Serial send ");
  Serial.println(h++);
  delay(100);
}
