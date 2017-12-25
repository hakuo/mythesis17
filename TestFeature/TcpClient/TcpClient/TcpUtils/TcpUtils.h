#ifndef SOCKET_TYPES_H
#define SOCKET_TYPES_H

#include <stdint.h>
#include <string>

namespace TcpUtils {

//#define SERVER_PORT 12345
#define DATA_SIZE 1024
#define DOWNLOAD_FOLDER "./recv/"
#define UPLOAD_FOLDER "./send/"

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
    NEGATIVE_RESPONSE_RESEND_ALL,
    NEGATIVE_RESPONSE_NOTSEND,
    POSITIVE_RESPONSE,
}response_t;

typedef enum: uint8_t
{
    UNDEFINED = 0,
    PNG_FILE,
    JPG_FILE,
    TXT_FILE,
    WAV_FILE,
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
#define TCP_BUFFER_SIZE sizeof(TcpUtils::tcp_pkg_t)

typedef struct
{
    file_type_t type;
    uint32_t size;
    uint32_t crc;
}file_info_t;

typedef struct
{
    file_info_t header;
    std::string filepath;
}file_t;
tcp_pkg_t *makeTxPackage(request_t cmd, response_t error_code, uint8_t* data = NULL, uint16_t len = 0);
//uint8_t* allocResponse(request_t cmd, response_t error_code, uint8_t* data = NULL, uint16_t len = 0);
bool checkAvailableToWrite(file_t file);
bool writeFileToMemory(const std::string filepath, const uint8_t *data, uint16_t datalen);
bool checkFileAvailable(const std::string filepath, size_t *szLen = NULL);
uint32_t calcFileCRC(const std::string filepath);
bool verifyDownloadPackage(file_t file);
bool genFilePath(file_t &file, const char *dir);
std::string ZeroPadNumber(uint32_t num);
bool checkDirExist(const char* dir);
bool createDirectory(const char* dir);
bool initEnv();
std::string getFileExt(const std::string filepath);
file_type_t getFileType(const std::string filepath);
std::string genFileExt(file_type_t file_type);
bool compareStringInsensitive(const std::string str1, const std::string str2);

} // namaspace TcpUtils

#endif // SOCKET_TYPES_H
