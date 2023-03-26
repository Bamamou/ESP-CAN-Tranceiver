# ESP-CAN-Tranceiver
+ Sending and receiving data between two ESP in the canbus using CAN_TLL from DevEBox
+ In the loop function, call the canSend() or CanReceive to send or receive data in the bus
+ Make sure to match the GPIO to your setting (RX and TX)
+ Make sure to choose the required baud rate of the bus
+ Make sure to connect CANH to CANH and CANL to CANL
