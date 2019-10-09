#pragma once

#include <stdbool.h>
struct mobile_adapter;

#ifdef __cplusplus
#define _Atomic
#endif

#define MOBILE_CONFIG_SIZE 0xC0
#define MOBILE_MAX_DATA_SIZE 0xFF
#define MOBILE_MAX_TCP_SIZE (MOBILE_MAX_DATA_SIZE - 1)

enum mobile_command {
    MOBILE_COMMAND_BEGIN_SESSION = 0x10,
    MOBILE_COMMAND_END_SESSION,
    MOBILE_COMMAND_DIAL_TELEPHONE,
    MOBILE_COMMAND_HANG_UP_TELEPHONE,
    MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL,
    MOBILE_COMMAND_TRANSFER_DATA,
    MOBILE_COMMAND_TELEPHONE_STATUS = 0x17,
    MOBILE_COMMAND_READ_CONFIGURATION_DATA = 0x19,
    MOBILE_COMMAND_WRITE_CONFIGURATION_DATA,
    MOBILE_COMMAND_TRANSFER_DATA_END = 0x1F,
    MOBILE_COMMAND_ISP_LOGIN = 0x21,
    MOBILE_COMMAND_ISP_LOGOUT,
    MOBILE_COMMAND_OPEN_TCP_CONNECTION,
    MOBILE_COMMAND_CLOSE_TCP_CONNECTION,
    MOBILE_COMMAND_DNS_QUERY = 0x28,
    MOBILE_COMMAND_ERROR = 0x6E
};

enum mobile_connection_state {
    MOBILE_CONNECTION_DISCONNECTED,
    MOBILE_CONNECTION_CALL,
    MOBILE_CONNECTION_INTERNET
};

struct mobile_adapter_commands {
    _Atomic bool session_begun;
    enum mobile_connection_state connection;
    bool tcp_open;
    unsigned packets_sent;
};

struct mobile_packet {
    enum mobile_command command;
    unsigned length;
    unsigned char data[MOBILE_MAX_DATA_SIZE];
};

extern bool mobile_session_begun;

struct mobile_packet *mobile_packet_process(struct mobile_adapter *adapter, struct mobile_packet *packet);
