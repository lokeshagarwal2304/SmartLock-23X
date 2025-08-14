#ifndef RFID_MODULE_H
#define RFID_MODULE_H

// Function to initialize RFID reader
void rfid_init();

// Function to read RFID card UID
int rfid_read(char *uidBuffer, int bufferSize);

// Function to verify UID with stored database
int rfid_verify(const char *uid);

#endif // RFID_MODULE_H

