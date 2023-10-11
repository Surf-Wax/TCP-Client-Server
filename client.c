/*  Bryce Thorpe
*   TCP Client for Windows
*
*   This project demonstrates a simple client-server communication system implemented in C for Windows. 
*   The client and server can exchange messages, and the server performs a string reversal operation on the 
*   received data.
*   
*/  

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

// displays an error message and terminates the program if an error occurs
void error(char *msg)
{
   perror(msg);
   exit(1);
}


int main(int argc, char *argv[])
{
   WSADATA wsaData;
   SOCKET sockfd;
   struct sockaddr_in serv_addr;
   char buffer[256];
   int n;

   // checks if the hostname and port number are provided as command-line arguments. If not, it displays an error message and terminates the program.
   if (argc < 3) {
       fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
       exit(1);
   }

   // initialize winsock library
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
       fprintf(stderr, "Failed to initialize winsock\n");
       exit(1);
   }

   // creates TCP socket using socket() function
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == INVALID_SOCKET)
       error("ERROR opening socket");

   // initialize new 'serv_addr' structure, which holds server's address and port number
   memset(&serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(atoi(argv[2]));

   // server's address set using 'inet_pton()' to convert server's IP address from string to binary format
   if (inet_pton(AF_INET, argv[1], &(serv_addr.sin_addr)) <= 0)
       error("ERROR invalid server address");

   // establishes connection to server using 'connect()'
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
       error("ERROR connecting");

   // prompt the user to enter a message, store in the buffer array
   printf("Please enter the message: ");
   memset(buffer, 0, sizeof(buffer));
   fgets(buffer, sizeof(buffer) - 1, stdin);

   // sends the message to the server using 'send()'
   n = send(sockfd, buffer, strlen(buffer), 0);
   if (n < 0)
       error("ERROR writing to socket");

   // recieves the server's response using 'recv()'
   memset(buffer, 0, sizeof(buffer));
   n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
   if (n < 0)
       error("ERROR reading from socket");

   // print response to stdout (console)
   printf("Server response: %s\n", buffer);

   // close socket and clean up winsock resources
   closesocket(sockfd);
   WSACleanup();

   return 0;