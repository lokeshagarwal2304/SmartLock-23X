#ifndef AUTO_LOCK_H
#define AUTO_LOCK_H

// Function to start auto-lock timer
void auto_lock_start(int seconds);

// Function to cancel auto-lock timer
void auto_lock_cancel();

// Function to execute lock when timer ends
void auto_lock_trigger();

#endif // AUTO_LOCK_H
