#ifndef FINGERPRINT_MODULE_H
#define FINGERPRINT_MODULE_H

// Function to initialize fingerprint sensor
void fingerprint_init();

// Function to enroll new fingerprint
int fingerprint_enroll(int id);

// Function to verify fingerprint
int fingerprint_verify();

// Function to delete stored fingerprint
int fingerprint_delete(int id);

#endif // FINGERPRINT_MODULE_H
