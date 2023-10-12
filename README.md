# TCP-Client-Server

TCP Client and TCP Server written in C for Windows.

## Introduction

This project demonstrates a simple client-server communication system implemented in C. The client and server can exchange messages, and the server performs a string reversal operation on the received data.

## Purpose

I developed this project as part of my CYBV 310 - Intro to Security Programming I course at the University of Arizona. The purpose is to provide a basic example of network communication.

## Prerequisites

Before running the code, ensure that you have the necessary development environment set up, including a C compiler.

## Usage

### TCP Client

The client program allows you to connect to a server and send messages for processing. To use the client:

1. Compile the client source code using your C compiler.
2. Run the compiled client executable, providing the server's hostname and port as command-line arguments.

Example:
```shell
./client <hostname> <port>
```
3. Follow the prompts to enter a message, and the client will send it to the server.
4. The server will process the message, and the client will display the server's response.

### TCP Server

The server program listens for incoming client connections, processes the received messages, and sends back the reversed message. To use the server:

1. Compile the server source code using your C compiler.
2. Run the compiled server executable, providing the port to listen on as a command-line argument.

Example:
```shell
./server <port>
```
The server will start listening for incoming client connections.

3. Connect a client to the server as explained in the client section.
4. The server will receive the client's message, reverse it, and send back the reversed message to the client.

<img width="500" alt="image" src="https://github.com/Surf-Wax/TCP-Client-Server/assets/145292208/dff010e5-cb32-45ac-8694-13c8626ef0ee">

<img width="500" alt="image" src="https://github.com/Surf-Wax/TCP-Client-Server/assets/145292208/66541744-bfa7-450c-8af2-b3a773371375">
