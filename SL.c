#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_PIN_LENGTH 10
#define MAX_RFID_LENGTH 20
#define MAX_FINGERPRINT_LENGTH 15
#define MAX_LOG_ENTRY 256
#define LOG_FILE "access_log.txt"
#define CONFIG_FILE "lock_config.txt"
#define DEFAULT_ATTEMPT_LIMIT 3
#define ADMIN_PASSWORD "ADMIN123"

typedef struct {
    char master_pin[MAX_PIN_LENGTH];
    char authorized_rfid[MAX_RFID_LENGTH];
    char authorized_fingerprint[MAX_FINGERPRINT_LENGTH];
    int attempt_limit;
    bool logging_enabled;
    bool hardware_mode;
    bool admin_panel_enabled;
    int failed_attempts;
    bool alarm_active;
    bool door_locked;
} DoorLockConfig;

DoorLockConfig config = {
    .master_pin = "1234",
    .authorized_rfid = "RFID001",
    .authorized_fingerprint = "FP001",
    .attempt_limit = DEFAULT_ATTEMPT_LIMIT,
    .logging_enabled = true,
    .hardware_mode = true,
    .admin_panel_enabled = true,
    .failed_attempts = 0,
    .alarm_active = false,
    .door_locked = true
};

void initializeSystem();
void displayMainMenu();
void unlockDoor();
void lockDoor();
void adminPanel();
void setNewPin();
void viewAccessLog();
void clearAccessLog();
void simulateHardware(const char* action, bool success);
void logAccess(const char* method, const char* input, bool success);
void triggerAlarm();
void resetAlarm();
bool authenticatePin();
bool authenticateRFID();
bool authenticateFingerprint();
bool adminAuthentication();
void saveConfiguration();
void loadConfiguration();
void displaySystemStatus();
void unlockWithRFID();
void unlockWithFingerprint();

void initializeSystem() {
    printf("Smart Door Lock System Initializing...\n");
    printf("=====================================\n");

    loadConfiguration();

    if (config.hardware_mode) {
        printf("Hardware Mode: ENABLED\n");
        simulateHardware("SYSTEM_INIT", true);
    }

    if (config.logging_enabled) {
        printf("Logging: ENABLED\n");
        logAccess("SYSTEM", "INITIALIZATION", true);
    }

    printf("System Ready!\n\n");
}

void displayMainMenu() {
    printf("\nSMART DOOR LOCK CONTROL PANEL\n");
    printf("==================================\n");
    printf("Door Status: %s\n", config.door_locked ? "LOCKED" : "UNLOCKED");
    printf("Failed Attempts: %d/%d\n", config.failed_attempts, config.attempt_limit);
    printf("Alarm Status: %s\n", config.alarm_active ? "ACTIVE" : "NORMAL");
    printf("\n");
    printf("1. Unlock Door (PIN)\n");
    printf("2. Unlock Door (RFID)\n");
    printf("3. Unlock Door (Fingerprint)\n");
    printf("4. Lock Door\n");
    printf("5. System Status\n");
    printf("6. View Access Log\n");
    printf("7. Admin Panel\n");
    printf("8. Reset Alarm\n");
    printf("0. Exit System\n");
    printf("\nSelect option: ");
}

void unlockDoor() {
    if (!config.door_locked) {
        printf("Door is already unlocked!\n");
        return;
    }
    if (config.alarm_active) {
        printf("ALARM ACTIVE! Contact administrator.\n");
        return;
    }
    printf("\nPIN Authentication Required\n");
    if (authenticatePin()) {
        config.door_locked = false;
        config.failed_attempts = 0;
        printf("ACCESS GRANTED! Door unlocked.\n");
        simulateHardware("UNLOCK", true);
        logAccess("PIN", "****", true);
    } else {
        config.failed_attempts++;
        printf("ACCESS DENIED! Invalid PIN.\n");
        printf("Failed attempts: %d/%d\n", config.failed_attempts, config.attempt_limit);
        simulateHardware("UNLOCK", false);
        logAccess("PIN", "INVALID", false);
        if (config.failed_attempts >= config.attempt_limit) {
            triggerAlarm();
        }
    }
}

void lockDoor() {
    if (config.door_locked) {
        printf("Door is already locked!\n");
        return;
    }
    config.door_locked = true;
    printf("Door locked successfully!\n");
    simulateHardware("LOCK", true);
    logAccess("MANUAL", "LOCK", true);
}

bool authenticatePin() {
    char input_pin[MAX_PIN_LENGTH];
    printf("Enter PIN: ");
    scanf("%s", input_pin);
    return strcmp(input_pin, config.master_pin) == 0;
}

bool authenticateRFID() {
    char input_rfid[MAX_RFID_LENGTH];
    printf("Scan RFID Card (Enter RFID ID): ");
    scanf("%s", input_rfid);
    return strcmp(input_rfid, config.authorized_rfid) == 0;
}

bool authenticateFingerprint() {
    char input_fp[MAX_FINGERPRINT_LENGTH];
    printf("Place finger on scanner (Enter Fingerprint ID): ");
    scanf("%s", input_fp);
    return strcmp(input_fp, config.authorized_fingerprint) == 0;
}

void adminPanel() {
    if (!adminAuthentication()) {
        printf("Admin authentication failed!\n");
        return;
    }
    int choice;
    do {
        printf("\nADMIN CONTROL PANEL\n");
        printf("=======================\n");
        printf("1. Change Master PIN\n");
        printf("2. Set RFID Card\n");
        printf("3. Set Fingerprint\n");
        printf("4. Emergency Unlock\n");
        printf("5. View Access Log\n");
        printf("6. Clear Access Log\n");
        printf("7. Reset Alarm\n");
        printf("8. System Configuration\n");
        printf("0. Back to Main Menu\n");
        printf("\nAdmin Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                setNewPin(); break;
            case 2:
                printf("Enter new RFID ID: ");
                scanf("%s", config.authorized_rfid);
                printf("RFID updated successfully!\n"); break;
            case 3:
                printf("Enter new Fingerprint ID: ");
                scanf("%s", config.authorized_fingerprint);
                printf("Fingerprint updated successfully!\n"); break;
            case 4:
                config.door_locked = false; config.failed_attempts = 0;
                printf("EMERGENCY UNLOCK ACTIVATED!\n");
                logAccess("ADMIN", "EMERGENCY_UNLOCK", true); break;
            case 5:
                viewAccessLog(); break;
            case 6:
                clearAccessLog(); break;
            case 7:
                resetAlarm(); break;
            case 8:
                displaySystemStatus(); break;
            case 0:
                printf("Exiting admin panel...\n"); break;
            default:
                printf("Invalid option!\n"); break;
        }
    } while (choice != 0);
}

bool adminAuthentication() {
    char admin_pass[50];
    printf("Enter Admin Password: ");
    scanf("%s", admin_pass);
    return strcmp(admin_pass, ADMIN_PASSWORD) == 0;
}

void setNewPin() {
    char new_pin[MAX_PIN_LENGTH], confirm_pin[MAX_PIN_LENGTH];
    printf("Enter new PIN: ");
    scanf("%s", new_pin);
    printf("Confirm new PIN: ");
    scanf("%s", confirm_pin);
    if (strcmp(new_pin, confirm_pin) == 0) {
        strcpy(config.master_pin, new_pin);
        printf("PIN updated successfully!\n");
        saveConfiguration();
        logAccess("ADMIN", "PIN_CHANGE", true);
    } else {
        printf("PINs do not match!\n");
    }
}

void simulateHardware(const char* action, bool success) {
    printf("\nHARDWARE SIMULATION\n");
    printf("======================\n");
    if (strcmp(action, "UNLOCK") == 0) {
        printf(success ? "GREEN LED ON\nMotor: UNLOCKED\n" : "RED LED ON\nMotor: LOCKED\n");
    } else if (strcmp(action, "LOCK") == 0) {
        printf("BLUE LED ON\nMotor: LOCKED\n");
    } else if (strcmp(action, "ALARM") == 0) {
        printf("ALARM TRIGGERED!\n");
    } else if (strcmp(action, "SYSTEM_INIT") == 0) {
        printf("System Ready with Startup Beep\n");
    }
    printf("======================\n");
}

void logAccess(const char* method, const char* input, bool success) {
    FILE* log_file = fopen(LOG_FILE, "a");
    if (!log_file) {
        printf("Could not open log file!\n"); return;
    }
    time_t now = time(NULL);
    char* time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';
    fprintf(log_file, "[%s] Method: %s | Input: %s | Result: %s | Attempts: %d\n",
            time_str, method, input, success ? "SUCCESS" : "FAILED", config.failed_attempts);
    fclose(log_file);
}

void viewAccessLog() {
    FILE* log_file = fopen(LOG_FILE, "r");
    if (!log_file) {
        printf("No access log found.\n"); return;
    }
    printf("\nACCESS LOG\n============\n");
    char line[MAX_LOG_ENTRY];
    while (fgets(line, sizeof(line), log_file)) {
        printf("%s", line);
    }
    fclose(log_file);
}

void clearAccessLog() {
    FILE* log_file = fopen(LOG_FILE, "w");
    if (log_file) {
        fclose(log_file);
        printf("Access log cleared!\n");
        logAccess("ADMIN", "LOG_CLEARED", true);
    } else {
        printf("Error clearing log file!\n");
    }
}

void triggerAlarm() {
    config.alarm_active = true;
    printf("\nSECURITY ALARM TRIGGERED!\n===============================\nToo many failed attempts!\nSystem locked for security.\nContact administrator.\n===============================\n");
    simulateHardware("ALARM", true);
    logAccess("SYSTEM", "ALARM_TRIGGERED", true);
}

void resetAlarm() {
    config.alarm_active = false;
    config.failed_attempts = 0;
    printf("Alarm reset successfully!\n");
    logAccess("ADMIN", "ALARM_RESET", true);
}

void displaySystemStatus() {
    printf("\nSYSTEM STATUS\n================\n");
    printf("Door Status: %s\n", config.door_locked ? "LOCKED" : "UNLOCKED");
    printf("Failed Attempts: %d/%d\n", config.failed_attempts, config.attempt_limit);
    printf("Alarm Status: %s\n", config.alarm_active ? "ACTIVE" : "NORMAL");
    printf("Logging: %s\n", config.logging_enabled ? "ENABLED" : "DISABLED");
    printf("Hardware Mode: %s\n", config.hardware_mode ? "ENABLED" : "DISABLED");
    printf("Admin Panel: %s\n", config.admin_panel_enabled ? "ENABLED" : "DISABLED");
    printf("Master PIN: ****\n");
    printf("RFID ID: %s\n", config.authorized_rfid);
    printf("Fingerprint ID: %s\n", config.authorized_fingerprint);
}

void saveConfiguration() {
    FILE* config_file = fopen(CONFIG_FILE, "w");
    if (config_file) {
        fprintf(config_file, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n",
                config.master_pin,
                config.authorized_rfid,
                config.authorized_fingerprint,
                config.attempt_limit,
                config.logging_enabled,
                config.hardware_mode,
                config.admin_panel_enabled);
        fclose(config_file);
    }
}

void loadConfiguration() {
    FILE* config_file = fopen(CONFIG_FILE, "r");
    if (config_file) {
        fscanf(config_file, "%s\n%s\n%s\n%d\n%d\n%d\n%d\n",
               config.master_pin,
               config.authorized_rfid,
               config.authorized_fingerprint,
               &config.attempt_limit,
               (int*)&config.logging_enabled,
               (int*)&config.hardware_mode,
               (int*)&config.admin_panel_enabled);
        fclose(config_file);
    }
}

void unlockWithRFID() {
    if (!config.door_locked) {
        printf("Door is already unlocked!\n"); return;
    }
    if (config.alarm_active) {
        printf("ALARM ACTIVE! Contact administrator.\n"); return;
    }
    printf("\nRFID Authentication\n=======================\n");
    if (authenticateRFID()) {
        config.door_locked = false; config.failed_attempts = 0;
        printf("ACCESS GRANTED! Door unlocked via RFID.\n");
        simulateHardware("UNLOCK", true);
        logAccess("RFID", config.authorized_rfid, true);
    } else {
        config.failed_attempts++;
        printf("ACCESS DENIED! Invalid RFID.\n");
        simulateHardware("UNLOCK", false);
        logAccess("RFID", "INVALID", false);
        if (config.failed_attempts >= config.attempt_limit) triggerAlarm();
    }
}

void unlockWithFingerprint() {
    if (!config.door_locked) {
        printf("Door is already unlocked!\n"); return;
    }
    if (config.alarm_active) {
        printf("ALARM ACTIVE! Contact administrator.\n"); return;
    }
    printf("\nFingerprint Authentication\n=============================\n");
    if (authenticateFingerprint()) {
        config.door_locked = false; config.failed_attempts = 0;
        printf("ACCESS GRANTED! Door unlocked via fingerprint.\n");
        simulateHardware("UNLOCK", true);
        logAccess("FINGERPRINT", config.authorized_fingerprint, true);
    } else {
        config.failed_attempts++;
        printf("ACCESS DENIED! Invalid fingerprint.\n");
        simulateHardware("UNLOCK", false);
        logAccess("FINGERPRINT", "INVALID", false);
        if (config.failed_attempts >= config.attempt_limit) triggerAlarm();
    }
}

int main() {
    initializeSystem();
    int choice;
    do {
        displayMainMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: unlockDoor(); break;
            case 2: unlockWithRFID(); break;
            case 3: unlockWithFingerprint(); break;
            case 4: lockDoor(); break;
            case 5: displaySystemStatus(); break;
            case 6: viewAccessLog(); break;
            case 7:
                if (config.admin_panel_enabled) adminPanel();
                else printf("Admin panel is disabled!\n");
                break;
            case 8: resetAlarm(); break;
            case 0:
                printf("Shutting down Smart Door Lock System...\n");
                saveConfiguration();
                logAccess("SYSTEM", "SHUTDOWN", true);
                printf("System shutdown complete. Goodbye!\n");
                break;
            default: printf("Invalid option! Please try again.\n"); break;
        }
        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); getchar();
        }
    } while (choice != 0);
    return 0;
}

