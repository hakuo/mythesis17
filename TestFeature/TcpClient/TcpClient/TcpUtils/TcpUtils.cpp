#include "TcpUtils.h"
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <boost/crc.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sys/poll.h>

namespace TcpUtils {
#define MAX_NUM 9999

// create buffer to send to socket
void makeTxPackage(tcp_pkg_t *pkg, request_t cmd, response_t error_code, uint8_t *data, uint16_t len)
{
    if(pkg != NULL)
    {
        memset(pkg, 0, TCP_BUFFER_SIZE);
        pkg->header.cmd = cmd;
        pkg->header.error_code = error_code;
        if((data != NULL) && (len != 0))
        {
            memcpy(pkg->data, data, len);
        }
    }
}

//uint8_t* allocResponse(request_t cmd, response_t error_code, uint8_t *data, uint16_t len)
//{
//    tcp_pkg_t* buffer = (tcp_pkg_t*)calloc(TCP_BUFFER_SIZE, 1);
//    buffer->header.cmd = cmd;
//    buffer->header.error_code = error_code;
//    if((data != NULL) && (len != 0))
//    {
//        memcpy(buffer->data, data, len);
//    }
//    return (uint8_t*)buffer;
//}

// check memory whether afford to write file or not
bool checkAvailableToWrite(file_t file)
{
    bool ret = true;
    FILE* fp = NULL;
    fp = fopen(file.filepath.c_str(), "w");
    if(fp == NULL)
    {
        std::cout << "Open file " << file.filepath << " failed" << std::endl;
        ret = false;
    }

    if(ret && file.header.size <= 0)
    {
        std::cout << "Invalid file size" << std::endl;
        ret = false;
    }
    // check if we have enough memory
    if(ret && ftruncate(fileno(fp), file.header.size) != 0)
    {
        std::cout << "System don't have enough memory" << std::endl;
        ret = false;
    }
    std::cout << "File is OK to write" << std::endl;
    if(fp)
    {
        fclose(fp);
    }
    remove(file.filepath.c_str());
    return ret;
}

// write a buffer_data to file
// this function write file in append mode
// have to remove existed file befare beginning write a new file.
bool writeFileToMemory(const std::string filepath, const uint8_t *data, uint16_t datalen)
{
    bool ret = true;
    size_t nLen = 0;
    if(filepath.c_str() == NULL || data == NULL || datalen == 0)
    {
        std::cout << "Invalid input to write file" << std::endl;
        ret = false;
    }
    else
    {
        FILE* fp = NULL;
        fp = fopen(filepath.c_str(), "ab+");
        if(fp == NULL)
        {
            std::cout << "Open file " << filepath << " failed" << std::endl;
            ret = false;
        }
        else
        {
            nLen = fwrite(data, sizeof(uint8_t), (size_t)datalen, fp);
            if(nLen != datalen)
            {
                ret = false;
                std::cout << "Write to file failed" << std::endl;
            }
            fclose(fp);
        }
    }
    return ret;
}

// checkFile exist or not
// if file existed, return szLen
bool checkFileAvailable(const std::string filepath, size_t *szLen)
{
    struct stat buffer;
    if(stat(filepath.c_str(), &buffer) == 0)
    {
        if(szLen != NULL)
        {
            *szLen = buffer.st_size;
        }
        return true;
    }
    else
    {
        return false;
    }
}

// calculate file CRC
uint32_t calcFileCRC(const std::string filepath)
{
    boost::crc_32_type  result;
    std::ifstream ifs(filepath, std::ios_base::binary);
    if(ifs)
    {
        do
        {
            char  buffer[DATA_SIZE];
            ifs.read(buffer, DATA_SIZE);
            result.process_bytes( buffer, ifs.gcount() );
        } while (ifs);
    }
    else
    {
        std::cout << "Failed to open file " << filepath << std::endl;
    }

    std::cout << std::hex << std::uppercase << result.checksum() << std::endl;
    return (uint32_t)result.checksum();
}

// check download file is valid or not
bool verifyDownloadPackage(file_t file)
{
    struct stat st;
    if(stat(file.filepath.c_str(), &st) < 0)
    {
        std::cout << "Cann't stat file " << file.filepath << std::endl;
        return false;
    }

    if(st.st_size != file.header.size)
    {
        std::cout << file.filepath << ": size mismatch" << std::endl;
        return false;
    }

    if(calcFileCRC(file.filepath) != file.header.crc)
    {
        std::cout << file.filepath << ": CRC mismatch" << std::endl;
        return false;
    }
    return true;
}

//std::string ZeroPadNumber(int num)
//{
//    std::ostringstream ss;
//    ss << std::setw(7) << std::setfill('0') << num;
//    std::string result = ss.str();
//    if (result.length() > 7)
//    {
//        result.erase(0, result.length() - 7);
//    }
//    return result;
//}

// fill "0" before filename
// eg: 0001.jpg
std::string ZeroPadNumber(uint32_t num)
{
    std::ostringstream ss;
    ss << std::setw(4) << std::setfill( '0' ) << num;
    return ss.str();
}

// generate filepath based on file_type
// input: dir => directory where store file
// eg: file_type = TXT_FILE => *.txt
bool genFilePath(file_t &file, const char* dir)
{
    uint32_t num = 0;
    bool ret = false;
    std::string ext;
    if(createDirectory(dir))
    {
        ext = genFileExt(file.header.type);
        while(num <= MAX_NUM)
        {
            file.filepath = dir;
            file.filepath += "/";
            file.filepath += ZeroPadNumber(num);
            file.filepath += ext;
            //if(access(file.filepath.c_str(), F_OK) == -1)
            if(!checkFileAvailable(file.filepath))
            {
                // file doesn't exist
                ret = true;
                break;
            }
            ++num;
        }
    }
    return ret;
}

// check whether directory existed or not
bool checkDirExist(const char* dir)
{
    struct stat st;
    if(stat(dir, &st) != 0)
    {
        std::cout << "folder not exist" << std::endl;
        return false;
    }
    return (st.st_mode & S_IFDIR);
}

// equal to "mkdir -p <dir>" command
bool createDirectory(const char* dir)
{
    int ret = 0;
    if(!checkDirExist(dir))
    {
        // Directory not exist
        ret = mkdir(dir, ACCESSPERMS);
    }
    return (ret == 0);
}


//bool initEnv()
//{
//    return (createDirectory(DOWNLOAD_FOLDER) && createDirectory(UPLOAD_FOLDER));
//}

// get file_extension
// eg: abc.txt => txt
std::string getFileExt(const std::string filepath)
{
    size_t i = filepath.rfind('.', filepath.length());
    if(i != std::string::npos)
    {
        return(filepath.substr(i+1, filepath.length() - i));
    }
    return "";
}

// check file_name and extract file_type
// eg: *.png => PNG_FILE
// eg: *.txt => TXT_FILE
file_type_t getFileType(const std::string filepath)
{
    file_type_t ret = UNDEFINED;
    std::string fExt = getFileExt(filepath);
    if(compareStringInsensitive(fExt, "png"))
    {
        ret = TcpUtils::PNG_FILE;
    }
    if(compareStringInsensitive(fExt, "jpg"))
    {
        ret = TcpUtils::JPG_FILE;
    }
    if(compareStringInsensitive(fExt, "txt"))
    {
        ret = TcpUtils::TXT_FILE;
    }
    if(compareStringInsensitive(fExt, "wav"))
    {
        ret = TcpUtils::WAV_FILE;
    }
    return ret;
}

// generate extension for file based on file_type
// PNG_FILE => *.png
// TXT_FILE => *.txt
std::string genFileExt(file_type_t filetype)
{
    std::string ret = "";
    switch (filetype) {
    case PNG_FILE:
        ret = ".png";
        break;
    case JPG_FILE:
        ret = ".jpg";
        break;
    case TXT_FILE:
        ret = ".txt";
        break;
    case WAV_FILE:
        ret = ".wav";
        break;
    default:
        break;
    }
    return ret;
}

// remove file extension
// eg: abc.txt => abc
std::string removeExt(const std::string filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot);
}

// compare string in insensitive case
// eg: png vs PNG => equal
// eg: png vs png => equal
bool compareStringInsensitive(const std::string str1, const std::string str2)
{
    return boost::iequals(str1, str2);
}

void freePointer(tcp_pkg_t *pointer)
{
    if(pointer != NULL)
    {
        delete pointer;
        pointer = NULL;
    }
}

#define TIMEOUT 1000 // 1 sec
#define MAX_TIMEOUT_EVENT 5

// recv socket with non-blocking mode
// this function only call recv when socket decriptor have message to read
// it returns false after TIME_OUT * MAX_TIME_EVENT
bool recvSock(int sockfd, void *buffer, ssize_t *szLen)
{
    if(sockfd < 0 || buffer == NULL || szLen == NULL)
    {
        std::cout << "recvSock() input invalid" << std::endl;
        return false;
    }

    int rc;
    struct pollfd fd;
    fd.fd = sockfd;
    fd.events = POLLIN;
    fd.revents = 0;

    int count = 0;
    do
    {
        rc = poll(&fd, 1, TIMEOUT);
        if(rc < 0)
        {
            // error
            std::cout << "poll() error" << std::endl;
            break;
        }

        if(rc > 0)
        {
            *szLen = recv(sockfd, buffer, TCP_BUFFER_SIZE, 0);
            return true;
        }
        // timeout
        count++;
    }while(count < MAX_TIMEOUT_EVENT);
    return false;

}

// send a message to server which sockfd
bool sendSock(int sockfd, void *buffer, size_t szLen)
{
    if(sockfd < 0 || buffer == NULL || szLen == 0)
    {
        std::cout << "Invalid package to send" << std::endl;
        return false;
    }
    int rc;
    rc = send(sockfd, buffer, szLen, 0);
    return (rc < 0) ? false : true;
}


// send message to server and recv feed back
bool sendPackage(int sockfd, tcp_pkg_t *txBuffer, tcp_pkg_t *rxBuffer, ssize_t *szRecv)
{
    while(1)
    {
        if(sendSock(sockfd, txBuffer, TCP_BUFFER_SIZE) == false)
        {
            return false;
        }

        if(recvSock(sockfd, rxBuffer, szRecv) == false)
        {
            return false;
        }

        if(rxBuffer->header.error_code == NEGATIVE_RESPONSE_NOTSEND)
        {
            return false;
        }

        if(rxBuffer->header.error_code == NEGATIVE_RESPONSE_RESEND_ALL)
        {
            return false;
        }

        if(rxBuffer->header.error_code == POSITIVE_RESPONSE)
        {
            // break to continue next type
            return true;
        }
        // remain only resend case
    }
}

// get IP address of the input interface
std::string getIp(const char *interface)
{
    struct ifaddrs *ifaddr, *ifa;
    int s;
    char host[NI_MAXHOST] = {0};

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return "";
    }


    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        s=getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

        if((strcmp(ifa->ifa_name, interface)==0)&&(ifa->ifa_addr->sa_family==AF_INET))
        {
            if (s != 0)
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                return "";
            }
            printf("\tInterface : <%s>\n",ifa->ifa_name );
            printf("\t  Address : <%s>\n", host);
            break;
        }
        memset(host, 0, NI_MAXHOST);
    }

    freeifaddrs(ifaddr);
    return host;
}

}














