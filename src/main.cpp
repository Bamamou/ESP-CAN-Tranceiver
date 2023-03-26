/* ESP32 Arduino CAN Send Basic Demo
 *     This example will send messages on the CAN bus
 *
 *     An external transceiver is required and should be connected 
 *     to the CAN_tx and CAN_rx gpio pins specified by CANInit. Be sure
 *     to use a 3.3V compatable transceiver such as the SN65HVD23x
 *
 */

#include <Arduino.h>
#include <ESP32CAN.h>

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32-Arduino-CAN Send Basic Demo");

  /* initialize and start, use pin 5 as CAN_tx and pin 4 as CAN_rx, CAN bus is set to 500kbps */
  ESP32Can.CANInit(GPIO_NUM_5, GPIO_NUM_4, ESP32CAN_SPEED_500KBPS);
}
//====================================================================================================================

void canSender() {
  twai_message_t tx_frame;
  
  tx_frame.extd = 0;              /* CAN ID is standard 11bit, for 29bit set to 1*/
  tx_frame.data_length_code = 8;  /* send 8 bytes of data */
  tx_frame.identifier = 0x123;    /* CAN id is 0x123 */

  /* assemble the 8 bytes of data */
  tx_frame.data[0] = 0xDE;
  tx_frame.data[1] = 0xAD;
  tx_frame.data[2] = 0xBE;
  tx_frame.data[3] = 0xEF;
  tx_frame.data[4] = 0xBA;
  tx_frame.data[5] = 0x5E;
  tx_frame.data[6] = 0xBA;
  tx_frame.data[7] = 0x11;

  ESP32Can.CANWriteFrame(&tx_frame); /* send the CAN message */

  Serial.println("CAN Frame Sent");

  /* delay before sending another CAN message*/
  delay(1000);
}

//================================================================================================================

void canReceiver() {
  twai_message_t rx_frame;
  
  if (ESP32CAN_OK == ESP32Can.CANReadFrame(&rx_frame)) {  /* only print when CAN message is received*/
     Serial.print("ID ");
    Serial.print(rx_frame.identifier, HEX);               /* print the CAN ID*/
    Serial.print(" DL ");
    Serial.print(rx_frame.data_length_code);              /* print number of bytes in data frame*/
    Serial.print(" ");
    for (int i=0; i<rx_frame.data_length_code; i++) {     /* print the data frame*/
      Serial.print(rx_frame.data[i], HEX);
    }

    Serial.println();
  }
  
  delay(1000);
}
void loop(){
 // To change this code to a receiver just uncomment the canReceiver()
  // canSender();
 canReceiver();
}