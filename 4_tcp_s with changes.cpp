// In lines 2-8, we include the necessary headers for our program.
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// In line 11, we use namespace std to avoid having to prefix standard library names with "std::".
using namespace std;

// In line 15, we define the main function, which is the entry point of our program.
int main() {

    // Here, we set the destination IP address to be '5555'.
    // This is the port number on which the server will be listening for incoming TCP connections.
    const int server_port = 5555;

    /* 
    A socket is a communication’s endpoint.
    In lines 34-37, we try to create a socket object called "sock" that will use IPv4
    addresses and the TCP protocol for communication.
    The socket() function gets 3 arguments:
    1. The first argument is the address family- In our case, AF_INET. It indicates that
    we would like to use IPv4 addresses.
    2. The second argument specifies the type of socket- In our case, SOCK_STREAM.
    It indicates that we want to use the TCP protocol for communication.
    3. The third argument specifies the protoco- In our case, 0. It means that we want
    to use the default protocol for TCP.
    The socket() function returns a file descriptor for the new socket, or -1 if there 
    was an error. If there was an error, we print an error message.
    */
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    /*
    In line 44, we declare a struct of type 'sockaddr_in' called 'sin'. This structure is
    used to store IPv4 address information, such as the address family, the port number,
    and the IP address of this server.
    */
    struct sockaddr_in sin;
    /*
    First, we initialize the 'sin' structure to zero using the memset() function to ensure
    that all fields of the structure are set to a known value before we change
    them as we want.
    Then, we change some of the values of the fields of the 'sin' structure to match
    this server's information.
    'sin_family'- AF_INET, meaning IPv4 addresses.
    'sin_addr.s_addr'- INADDR_ANY, which tells the server to listen for
    incoming packets on all available network interfaces of this machine.
    'sin_port'- the port number in network byte order. This is done using the htons()
    function, which converts the port number from host byte order to network byte order.
    */
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    /*
    We use the bind() function to bind the socket with a specific address and port.
    We call the bind() function with three arguments:
    1. The file descriptor of the socket we want to bind (sock).
    2. A pointer to a struct sockaddr that contains the address
    and port we want to bind to. We cast the pointer to the correct type
    because the bind() function expects a pointer to a struct sockaddr by using a type
    cast.
    3. The size of the address structure, which is given by sizeof(sin).
    If the bind() function returns a value less than 0, it means that there was
    an error binding the socket, and we print an error message.
    */
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    /*
    In these lines, we tell the server to start listening for incoming connections. The maximum number
    of queued connections is 5. If the listen() function returns a value less than 0, it means that
    there was an error with listening to the socket, and we print an error message.
    */
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }

    /*
    We create a struct of type 'sockaddr_in' called 'client_sin' to store the client's address information
    when a client connects to the server. We also create an unsigned int variable called 'addr_len'
    to store the size of the client's address structure.
    We use the accept() function to accept a connection from a client. This function will not return
    until a client connects to the server. 
    When a client connects, the function returns a new socket file descriptor for the client
    connection, which we store in the variable 'client_sock'.
    The accept() function takes three arguments:
    1. The file descriptor of the listening socket ('sock').
    2. A pointer to a struct sockaddr that will be filled with the client's address information.
    We cast the pointer to the correct type because the accept() function expects a pointer to a
    struct sockaddr by using a type cast.
    3. A pointer to a variable that contains the size of the client's address structure.
    The function will update this variable with the actual size of the client's address.
    
    If the accept() function returns a value less than 0, it means that there was an error accepting
    the client connection, and we print an error message.
    */
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }

    /*
    We create a buffer array to store the data received from the client. We also create an
    integer variable called 'expected_data_len' to store the size of the buffer.
    We use the recv() function to receive data from the client. This function takes four arguments:
    1. The file descriptor of the client socket ('client_sock').
    2. A pointer to the buffer where we want to store the received data ('buffer').
    3. The length of the buffer ('expected_data_len').
    4. Flags (0 in this case, meaning no special options).
    The recv() function returns the number of bytes received, or -1 if there was an error.
    If the returned value is 0, it means that the connection is closed, and we do nothing.
    If read_bytes < 0, it means there was an error, and we do nothing.
    If there was no error and the connection is not closed, we print the received data to the console.
    */
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

    if (client_sock < 0) {
        perror("error accepting client");
    }

    /*
    We create a buffer array to store the data received from the client. We also create an
    integer variable called 'expected_data_len' to store the size of the buffer.
    We use the recv() function with the following parameters to receive data from the client:
    1. The file descriptor for the client socket ('client_sock').
    2. A pointer to the 'buffer' array.
    3. The size of the buffer ('expected_data_len').
    4. 0: No other flags.
    The recv() function returns the number of bytes received, or -1 if there was an error.
    If the returned value is 0, it means that the connection is closed, and we do nothing.
    If read_bytes < 0, it means there was an error, and we do nothing.
    If there was no error and the connection is not closed, we print the received data to the console.
    */
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
    }

    /*
    Change: I changed the message that the server sends back to the client to be
    the message that the server received from the client with the last character being
    '1'.
    This means that if the client sends a message to the server, the server will send back the
    same message but without the last character.
    */

    buffer[read_bytes - 1] = '1';

    /*
    The send() function is used to send data over the socket.
    It takes four arguments:
    1. The file descriptor of the client socket we want to send data through (client_sock).
    2. A pointer to the data we want to send (buffer).
    3. The length of the data we want to send (read_bytes).
    4. Flags (0 in this case, meaning no special options).

    The send() function returns the number of bytes sent, or -1 if there was an error.
    If there was an error, we print an error message using the perror() function.
    */
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);

    if (sent_bytes < 0) {
        perror("error sending to client");
    }

    // Finally, we close the client socket and the server socket to clean up and release the
    // system resources.
    close(client_sock);
    close(sock);

    // We return 0 to indicate that the program ended successfully.
    return 0;
}