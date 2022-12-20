// Autogenerated C header file for DeviceScript Manager
#ifndef _JACDAC_SPEC_DEVICE_SCRIPT_MANAGER_H
#define _JACDAC_SPEC_DEVICE_SCRIPT_MANAGER_H 1

#define JD_SERVICE_CLASS_DEVICE_SCRIPT_MANAGER  0x1134ea2b

// enum MessageFlags (uint8_t)
#define JD_DEVICE_SCRIPT_MANAGER_MESSAGE_FLAGS_TO_BE_CONTINUED 0x1

/**
 * Argument: bytecode_size B uint32_t. Open pipe for streaming in the bytecode of the program. The size of the bytecode has to be declared upfront.
 * To clear the program, use `bytecode_size == 0`.
 * The bytecode is streamed over regular pipe data packets.
 * The bytecode shall be fully written into flash upon closing the pipe.
 * If `autostart` is true, the program will start after being deployed.
 * The data payloads, including the last one, should have a size that is a multiple of 32 bytes.
 * Thus, the initial bytecode_size also needs to be a multiple of 32.
 */
#define JD_DEVICE_SCRIPT_MANAGER_CMD_DEPLOY_BYTECODE 0x80

/**
 * Report: Argument: bytecode_port pipe_port (uint16_t)
 */

/**
 * Argument: bytecode pipe (bytes). Get the current bytecode deployed on device.
 */
#define JD_DEVICE_SCRIPT_MANAGER_CMD_READ_BYTECODE 0x81

/**
 * Argument: data bytes. Get the current bytecode deployed on device.
 */

/**
 * Generated by `console.log()` calls from DeviceScript program.
 * The counter starts at `0`, increments by `1` for each packet and wraps around.
 * It can be used to detect if some messages are missing.
 * If message is too long to fit in a single packet, it will be fragmented (this is not implemented yet).
 * In a fragmented message, all packets except for the last one have `ToBeContinued` flag set.
 * Note that `counter` field will increase in each fragment.
 * `log_message` reports are only sent when `logging == true`.
 */
#define JD_DEVICE_SCRIPT_MANAGER_CMD_LOG_MESSAGE 0x82
typedef struct jd_device_script_manager_log_message_report {
    uint8_t counter;
    uint8_t flags;  // MessageFlags
    char message[0];  // string
} jd_device_script_manager_log_message_report_t;


/**
 * Read-write bool (uint8_t). Indicates if the program is currently running.
 * To restart the program, stop it (write `0`), read back the register to make sure it's stopped,
 * start it, and read back.
 */
#define JD_DEVICE_SCRIPT_MANAGER_REG_RUNNING 0x80

/**
 * Read-write bool (uint8_t). Indicates wheather the program should be re-started upon `reboot()` or `panic()`.
 * Defaults to `true`.
 */
#define JD_DEVICE_SCRIPT_MANAGER_REG_AUTOSTART 0x81

/**
 * Read-write bool (uint8_t). `log_message` reports are only sent when this is `true`.
 * It defaults to `false`.
 */
#define JD_DEVICE_SCRIPT_MANAGER_REG_LOGGING 0x82

/**
 * Read-only uint32_t. The size of current program.
 */
#define JD_DEVICE_SCRIPT_MANAGER_REG_PROGRAM_SIZE 0x180

/**
 * Read-only uint32_t. Return FNV1A hash of the current bytecode.
 */
#define JD_DEVICE_SCRIPT_MANAGER_REG_PROGRAM_HASH 0x181

/**
 * Read-only bytes. Return 32-byte long SHA-256 hash of the current bytecode.
 */
#define JD_DEVICE_SCRIPT_MANAGER_REG_PROGRAM_SHA256 0x182

/**
 * Returns the runtime version number compatible with [Semver](https://semver.org/).
 * When read as 32-bit little endian integer a version `7.15.500` would be `0x07_0F_01F4`.
 */
#define JD_DEVICE_SCRIPT_MANAGER_REG_RUNTIME_VERSION 0x183
typedef struct jd_device_script_manager_runtime_version {
    uint16_t patch;
    uint8_t minor;
    uint8_t major;
} jd_device_script_manager_runtime_version_t;


/**
 * Emitted when the program calls `panic(panic_code)` or `reboot()` (`panic_code == 0` in that case).
 * The byte offset in byte code of the call is given in `program_counter`.
 * The program will restart immediately when `panic_code == 0` or in a few seconds otherwise.
 */
#define JD_DEVICE_SCRIPT_MANAGER_EV_PROGRAM_PANIC 0x80
typedef struct jd_device_script_manager_program_panic {
    uint32_t panic_code;
    uint32_t program_counter;
} jd_device_script_manager_program_panic_t;


/**
 * Emitted after bytecode of the program has changed.
 */
#define JD_DEVICE_SCRIPT_MANAGER_EV_PROGRAM_CHANGE JD_EV_CHANGE

#endif
