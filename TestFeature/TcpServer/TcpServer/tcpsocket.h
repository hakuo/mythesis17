#ifndef SOCKET_TYPES_H
#define SOCKET_TYPES_H

#include <stdint.h>

namespace TcpSocket {

#define SERVER_PORT 12345
#define DATA_SIZE 1024

typedef enum: uint8_t
{
    START_DOWNLOAD = 0, // notify target to receive file (send file_size, file_type, file_crc)
    TRANFER_FILE,       // send file context to target
    END_DOWNLOAD,       // notify target to complete download file
}request_t;

typedef enum: uint8_t
{
    REQUEST = 0,
    NEGATIVE_RESPONSE_RESEND,
    NEGATIVE_RESPONSE_NOTSEND,
    POSITIVE_RESPONSE,
}response_t;

typedef enum: uint8_t
{
    UNDEFINED = 0,
    IMG_FILE,
    TXT_FILE,
}file_type_t;

typedef struct
{
    request_t cmd;
    response_t error_code;
}header_t;

typedef struct
{
    header_t header;
    uint8_t data[DATA_SIZE];
}tcp_pkg_t;
#define BUFFER_SIZE sizeof(TcpSocket::tcp_pkg_t)

typedef struct
{
    file_type_t type;
    uint32_t size;
    uint32_t crc;
}file_info_t;

} // namaspace TcpSocket

#endif // SOCKET_TYPES_H
