// Autogenerated C header file for WIFI
#ifndef _JACDAC_SPEC_WIFI_H
#define _JACDAC_SPEC_WIFI_H 1

#define JD_SERVICE_CLASS_WIFI  0x18aae1fa

// enum APFlags (uint32_t)
#define JD_WIFI_APFLAGS_HAS_PASSWORD 0x1
#define JD_WIFI_APFLAGS_WPS 0x2
#define JD_WIFI_APFLAGS_HAS_SECONDARY_CHANNEL_ABOVE 0x4
#define JD_WIFI_APFLAGS_HAS_SECONDARY_CHANNEL_BELOW 0x8
#define JD_WIFI_APFLAGS_IEEE_802_11B 0x100
#define JD_WIFI_APFLAGS_IEEE_802_11A 0x200
#define JD_WIFI_APFLAGS_IEEE_802_11G 0x400
#define JD_WIFI_APFLAGS_IEEE_802_11N 0x800
#define JD_WIFI_APFLAGS_IEEE_802_11AC 0x1000
#define JD_WIFI_APFLAGS_IEEE_802_11AX 0x2000
#define JD_WIFI_APFLAGS_IEEE_802_LONG_RANGE 0x8000

/**
 * Argument: results pipe (bytes). Return list of WiFi network from the last scan.
 * Scans are performed periodically while not connected (in particular, on startup and after current connection drops),
 * as well as upon `reconnect` and `scan` commands.
 */
#define JD_WIFI_CMD_LAST_SCAN_RESULTS 0x80

/**
 * Return list of WiFi network from the last scan.
 * Scans are performed periodically while not connected (in particular, on startup and after current connection drops),
 * as well as upon `reconnect` and `scan` commands.
 */
typedef struct jd_wifi_results {
    uint32_t flags;  // APFlags
    uint32_t reserved;
    int8_t rssi; // dB
    uint8_t channel;
    uint8_t bssid[6];  // u8[6]
    char ssid[33];  // string
} jd_wifi_results_t;


/**
 * Automatically connect to named network if available. Also set password if network is not open.
 */
#define JD_WIFI_CMD_ADD_NETWORK 0x81
typedef struct jd_wifi_add_network {
    char ssid[0];  // string0
    // char password[0];  // string0
} jd_wifi_add_network_t;


/**
 * No args. Initiate a scan, wait for results, disconnect from current WiFi network if any,
 * and then reconnect (using regular algorithm, see `set_network_priority`).
 */
#define JD_WIFI_CMD_RECONNECT 0x82

/**
 * Argument: ssid string (bytes). Prevent from automatically connecting to named network in future.
 * Forgetting a network resets its priority to `0`.
 */
#define JD_WIFI_CMD_FORGET_NETWORK 0x83

/**
 * No args. Clear the list of known networks.
 */
#define JD_WIFI_CMD_FORGET_ALL_NETWORKS 0x84

/**
 * Set connection priority for a network.
 * By default, all known networks have priority of `0`.
 */
#define JD_WIFI_CMD_SET_NETWORK_PRIORITY 0x85
typedef struct jd_wifi_set_network_priority {
    int16_t priority;
    char ssid[0];  // string
} jd_wifi_set_network_priority_t;


/**
 * No args. Initiate search for WiFi networks. Generates `scan_complete` event.
 */
#define JD_WIFI_CMD_SCAN 0x86

/**
 * Argument: results pipe (bytes). Return list of known WiFi networks.
 * `flags` is currently always 0.
 */
#define JD_WIFI_CMD_LIST_KNOWN_NETWORKS 0x87

/**
 * Return list of known WiFi networks.
 * `flags` is currently always 0.
 */
typedef struct jd_wifi_network_results {
    int16_t priority;
    int16_t flags;
    char ssid[0];  // string
} jd_wifi_network_results_t;


/**
 * Read-write bool (uint8_t). Determines whether the WiFi radio is enabled. It starts enabled upon reset.
 */
#define JD_WIFI_REG_ENABLED JD_REG_INTENSITY

/**
 * Read-only bool (uint8_t). Indicates whether or not we currently have an IP address assigned.
 */
#define JD_WIFI_REG_CONNECTED 0x180

/**
 * Read-only bytes. 0, 4 or 16 byte buffer with the IPv4 or IPv6 address assigned to device if any.
 */
#define JD_WIFI_REG_IP_ADDRESS 0x181

/**
 * Read-only bytes. The 6-byte MAC address of the device.
 */
#define JD_WIFI_REG_EUI_48 0x182

/**
 * Read-only string (bytes). SSID of the access-point to which device is currently connected.
 * Empty string if not connected.
 */
#define JD_WIFI_REG_SSID 0x183

/**
 * Emitted upon successful join and IP address assignment.
 */
#define JD_WIFI_EV_GOT_IP JD_EV_ACTIVE

/**
 * Emitted when disconnected from network.
 */
#define JD_WIFI_EV_LOST_IP JD_EV_INACTIVE

/**
 * A WiFi network scan has completed. Results can be read with the `last_scan_results` command.
 * The event indicates how many networks where found, and how many are considered
 * as candidates for connection.
 */
#define JD_WIFI_EV_SCAN_COMPLETE 0x80
typedef struct jd_wifi_scan_complete {
    uint16_t num_networks;
    uint16_t num_known_networks;
} jd_wifi_scan_complete_t;


/**
 * Emitted whenever the list of known networks is updated.
 */
#define JD_WIFI_EV_NETWORKS_CHANGED 0x81

#endif
