//
//  TcpipSocket.c
//  tcpip


#include "TcpipSocket.h"
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //read write close
#include <netdb.h> //hostent
#include <errno.h>
#include <string.h>
#define LOOPBACK_ADDRESS            "127.0.0.1"
#define TAP_LOCAL_ADDRESS            "10.50.0.1"

#ifdef TEST_LOCAL//==ON
#define USED_ADDR                LOOPBACK_ADDRESS
#else
#define USED_ADDR                TAP_LOCAL_ADDRESS
#endif

char Routing_Activation[15];
char DoIP_DiagMessage[14];
char DoIP_RegimeMoteur[16];
int sockfd = 0, n = 0;
struct sockaddr_in serv_addr;
void Tester_init(void)
{
    Routing_Activation[0]=DoIP_Version;
    Routing_Activation[1]=DoIP_Version_inv;
    Routing_Activation[2]=(char)0x00;
    Routing_Activation[3]=(char)0x05;
    Routing_Activation[4]=(char)0x00;
    Routing_Activation[5]=(char)0x00;
    Routing_Activation[6]=(char)0x00;
    Routing_Activation[7]=(char)0x07;
    Routing_Activation[8]=(char)0x0E;
    Routing_Activation[9]=(char)0x00;
    Routing_Activation[10]=(char)0x00;
    Routing_Activation[11]=(char)0x00;
    Routing_Activation[12]=(char)0x00;
    Routing_Activation[13]=(char)0x00;
    Routing_Activation[14]=(char)0x00;

    DoIP_DiagMessage[0]=DoIP_Version;
    DoIP_DiagMessage[1]=DoIP_Version_inv;
    DoIP_DiagMessage[2]=(char)(0x80);
    DoIP_DiagMessage[3]=(char)(0x01);
    DoIP_DiagMessage[4]=(char)(0x00);
    DoIP_DiagMessage[5]=(char)(0x00);
    DoIP_DiagMessage[6]=(char)(0x00);
    DoIP_DiagMessage[7]=(char)(0x06);
    DoIP_DiagMessage[8]=(char)(0x0E); //@recep /@emission
    DoIP_DiagMessage[9]=(char)(0x00);
    DoIP_DiagMessage[10]=(char)(0x03); //815 03 2F
    DoIP_DiagMessage[11]=(char)(0x2F);
    DoIP_DiagMessage[12]=(char)0x10; // service  0x22
    DoIP_DiagMessage[13]=(char)0x03; // 0xD4
 //   memset(DoIP_DiagMessage, '0', sizeof(DoIP_DiagMessage));
   // REGIME MOTEUR
    DoIP_RegimeMoteur[0]=DoIP_Version;
    DoIP_RegimeMoteur[1]=DoIP_Version_inv;
    DoIP_RegimeMoteur[2]=(char)(0x80);
    DoIP_RegimeMoteur[3]=(char)(0x01);
    DoIP_RegimeMoteur[4]=(char)(0x00);
    DoIP_RegimeMoteur[5]=(char)(0x00);
    DoIP_RegimeMoteur[6]=(char)(0x00);
    DoIP_RegimeMoteur[7]=(char)(0x07);
    DoIP_RegimeMoteur[8]=(char)(0x0E); //@recep /@emission
    DoIP_RegimeMoteur[9]=(char)(0x00);
    DoIP_RegimeMoteur[10]=(char)(0x03); //815
    DoIP_RegimeMoteur[11]=(char)(0x2F);
    DoIP_RegimeMoteur[12]=(char)0x22; // service  0x22
    DoIP_RegimeMoteur[13]=(char)0xD4; // 0xD4
    DoIP_RegimeMoteur[14]=(char)(0x00);
    DoIP_RegimeMoteur[15]=(char)(0x00);
   // memset(DoIP_RegimeMoteur, '0', sizeof(DoIP_RegimeMoteur));
    
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");

    } else{
    printf("Socket file descriptor is created \n");
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(13400);
    if(inet_pton(AF_INET, USED_ADDR, (void *) &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
    }

    printf("Connecting to %s\n",USED_ADDR);
}

void Tester_Connect(void)
{
    int result = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
     if( result < 0 )
        {
               printf("Error: Connect Failed \n");
        printf("Reason: %s\n", strerror(errno));
        exit(0);
        }else{
        printf("Connected to %s, and PORT: %d \n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
    }
    

}
                          // INIT AND CONNECT FINISH //
                               // NEW BEGINNING //

                          // SEND RoutingActivation //
void Tester_SendRoutingActivation(void)
{
    write(sockfd, Routing_Activation,sizeof(Routing_Activation));
   
}

                   // SEND AND RECEIVE DIAG MESSAGE //

void Tester_DIAG_MESSAGE(unsigned char instanceID)
{
      DoIP_DiagMessage[13]=0x03;
      DoIP_DiagMessage[14]=0x00;
    printf(" Send Diag Msg \n");
      if(write(sockfd, DoIP_DiagMessage,sizeof(DoIP_DiagMessage)) > 0){
          printf("Diag Msg", sizeof(DoIP_DiagMessage));
    }else{
        printf("Failed to write handleStart (0x03)\n");
    }

}
                               // FONCTION READ//


 
char readResponse(){
    //TODO: TO handle also the pending responses
    printf("Getting response ...\n");
    unsigned char Response[256]= {0};

    if((n=read(sockfd, Response, sizeof(Response) - 1)) > 0){
        Response[n] = 0;
        
        Response[n] = 0;
        printf("response : \n");
        for (int i=12; i<n; i++)
        {
           
           printf("%2x ", Response[i]);
          
           // int vOut = (int)Response[i];
           
          //  printf("%d",vOut);
        //long n = strtol(Response[i], NULL, 16);
       // printf("n=%ld\n", n);
         }
        
        printf("\n");
        
        }else{
            printf("%s\n", strerror(errno));
        }
    
       // n = 0;
        return Response[n];
   
}
                           // FONCTION StopDIAG_MESSAGE//
void Tester_StopDIAG_MESSAGE(unsigned char instanceID)
{
      DoIP_DiagMessage[13]=0x03;
      //DoIP_DiagMessage[16]=instanceID;
      if (write(sockfd, DoIP_DiagMessage,sizeof(DoIP_DiagMessage)) > 0){
          printf("Written handle stop  with length %lu: \n", sizeof(DoIP_DiagMessage));
    }else{
        printf("Failed to write handle stop (0x03)\n");
    }
}
                        // FONCTION close socket//

void tcpipSocket_close(int sock) {
  close(sockfd);
}
                     // SEND AND STOP REGIME MOTEUR //
                         // SEND REGIME MOTEUR //

void Tester_REGIME_MOTEUR(unsigned char instanceID)
{
      //DoIP_DiagMessage[13]=0x03;
    DoIP_RegimeMoteur[13]=(char)0xD4; // 0xD4
    DoIP_RegimeMoteur[14]=(char)(0x00);//
     
      if(write(sockfd, DoIP_RegimeMoteur,sizeof(DoIP_RegimeMoteur)) > 0){
          printf("Written REGIME_MOTEUR: %lu \n", sizeof(DoIP_RegimeMoteur));
    }else{
        printf("Failed to write handleStart \n");
    }

}
                     //STOP REGIME MOTEUR //

void Tester_StopREGIME_MOTEUR(unsigned char instanceID)
{
    DoIP_RegimeMoteur[13]=(char)0xD4; // 0xD4
    DoIP_RegimeMoteur[14]=(char)(0x00);
      if (write(sockfd, DoIP_RegimeMoteur,sizeof(DoIP_RegimeMoteur)) > 0){
          printf("Written handle stop  with length %lu: \n", sizeof(DoIP_RegimeMoteur));
    }else{
        printf("Failed to write handle stop \n");
    }
}


