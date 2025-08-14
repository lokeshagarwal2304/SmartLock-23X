#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H

// Function to initialize Bluetooth module
void bluetooth_init();

// Function to read data from Bluetooth
int bluetooth_read(char *dataBuffer, int bufferSize);

// Function to send data over Bluetooth
void bluetooth_send(const char *message);

#endif // BLUETOOTH_MODULE_H
