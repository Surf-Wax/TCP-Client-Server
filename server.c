/*  Bryce Thorpe
*   TCP Server for Windows
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

void error(char *msg)
{
   perror(msg);
   exit(1);
}

// function for reversing the string recieved from the client
void reverseString(char* str)
{
   int length = strlen(str);
   int start = 0;
   int end = length -1;

   // iterate over the string from both ends and swap the chars until we reach the middle.
   // swaps first char with the last char, second char with the second-to-last char, and so on.
   while (start < end)
   {
       char temp = str[start];
       str[start] = str[end];
       str[end] = temp;
       start++;
       end--;
   }
}


int main(int argc, char *argv[])
{
   WSADATA wsaData;
   SOCKET sockfd, newsockfd;
   int portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n;

   // checks if a port number is provided as a command-line argument. If not, it displays an error message and terminates the program.
   if (argc < 2) {
       fprintf(stderr, "ERROR, no port provided\n");
       exit(1);
   }

   // initializes the Winsock library using the WSAStartup() function. It checks if the initialization was successful and displays an error message if it failed.
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
       fprintf(stderr, "Failed to initialize winsock\n");
       exit(1);
   }

   // creates a TCP socket using the socket() function. It checks if the socket creation was successful and calls the error() function if it failed.
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == INVALID_SOCKET)
       error("ERROR opening socket");

   //  initialize the serv_addr structure, which holds information about the server's address and port number.
   memset(&serv_addr, 0, sizeof(serv_addr));
   portno = atoi(argv[1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   // binds the socket to the server address and port number specified in the serv_addr structure using the bind() function. It checks if the binding was successful and calls the error() function if it failed.
   if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
       error("ERROR on binding");

   // starts listening for incoming connections on the socket with a maximum queue size of 5 pending connections.
   listen(sockfd, 5);

   // accept a client connection using the accept() function. Waits until a client connects and creates a new socket ('newsockfd') for communication with the client. Calls error function if failed.
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
   if (newsockfd == INVALID_SOCKET)
       error("ERROR on accept");

   // receives data from the client using the recv() function. It reads up to sizeof(buffer) - 1 bytes of data into the buffer array.
   memset(buffer, 0, sizeof(buffer));
   n = recv(newsockfd, buffer, sizeof(buffer) - 1, 0);
   if (n < 0)
       error("ERROR reading from socket");
   printf("Here is the message: %s\n", buffer);

   // reverses string sent by client
   reverseString(buffer);
   printf("Reversed string: %s\n", buffer);

   // sends a response message to the client using the send() function.
   n = send(newsockfd, buffer, strlen(buffer), 0);
   if (n < 0)
       error("ERROR writing to socket");

   // close the client socket (newsockfd), the server socket (sockfd), and perform cleanup of the Winsock library
   closesocket(newsockfd);
   closesocket(sockfd);
   WSACleanup();

   return 0;
}
