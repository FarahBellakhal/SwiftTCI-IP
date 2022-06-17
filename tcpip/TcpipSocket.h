//
//  TcpipSocket.h
//  tcpip
//

#ifndef TcpipSocket_h
#define TcpipSocket_h
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#define DoIP_Generic_Header_Length (0x08)
#define DoIP_Version (0x02)
#define DoIP_Version_inv (0xFD)
#define DoIP_TesterSourceAddress (0x0E)
//#define DoIP_ECUAddress (0x5555)
#define DoIP_ECUAddress (0xBBBB)
#define Camera_Routine (601)
#define Routing_Activation_Request (0x00)
#define Routing_Activation_Request_Length (0x00)
#define DiagMessage (0x8001)
#define DiagMessage_Length (0x0000009)
void Tester_init(void);
void Tester_Connect(void);
char readResponse();
void Tester_SendRoutingActivation(void);
void Tester_DIAG_MESSAGE(unsigned char);
void Tester_StopDIAG_MESSAGE(unsigned char);
void Tester_REGIME_MOTEUR(unsigned char);
void Tester_StopREGIME_MOTEUR(unsigned char);
struct pair_int_char {
    int key;
    char* value;
   
};

#endif
#ifdef __cplusplus
extern "C" {
#endif
/*
  int tcpipSocket_connect(const char* serverName, int portno);
  void tcpipSocket_send();
void createVehicleIdentificationResponse();
  void tcpipSocket_close(int sock);
void createAndSendVehicleIdentificationRequest( const char* address);
//int createGenericHeader(enum PayloadType type, uint32_t length);
unsigned char* createDiagnosticMessage(unsigned char sourceAddress [2], unsigned char targetAddress [2], unsigned char* userData, int userDataLength);
void sendDiagnosticMessage(unsigned char* targetAddress, unsigned char* userData, int userDataLength);
int sock;
int emptyMessageCounter = 0;
const int _DiagnosticPositiveACKLength = 5;
const int _DiagnosticMessageMinimumLength = 4;

const unsigned char _ValidDiagnosticMessageCode = 0x00;
const unsigned char _InvalidSourceAddressCode = 0x02;
const unsigned char _UnknownTargetAddressCode = 0x03;
const int _GenericHeaderLength = 8;
const int _NACKLength = 1;

const unsigned char _IncorrectPatternFormatCode = 0x00;
const unsigned char _UnknownPayloadTypeCode = 0x01;
const unsigned char _InvalidPayloadLengthCode = 0x04;

enum PayloadType {
    NEGATIVEACK,
    ROUTINGACTIVATIONREQUEST,
    ROUTINGACTIVATIONRESPONSE,
    VEHICLEIDENTREQUEST,
    VEHICLEIDENTRESPONSE,
    DIAGNOSTICMESSAGE,
    DIAGNOSTICPOSITIVEACK,
    DIAGNOSTICNEGATIVEACK,
    ALIVECHECKRESPONSE,
};

struct GenericHeaderAction {
    enum PayloadType type;
    unsigned char value;
};

struct pair_int_char {
    int key;
    char* value;
   
};
struct sockaddr ;


struct sockaddr_in ;

const char* serverName; int portno;
int broadcast = 1;
   struct sockaddr_in _serverAddr, _clientAddr;
   unsigned char sourceAddress [2];
   
   unsigned char VINResult [17];
   unsigned char LogicalAddressResult [2];
   unsigned char EIDResult [6];
   unsigned char GIDResult [6];
   unsigned char FurtherActionReqResult;*/
#ifdef __cplusplus
}
#endif

/* TcpipSocket_h */
