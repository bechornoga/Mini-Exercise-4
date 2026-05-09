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

    // Here, we set the destination IP address to be '127.0.0.1', which means that the client
    // will communicate with a server that is running on the same machine.
    const char* ip_address = "127.0.0.1";
    // Here, we set the destination port to 5555. This is the port number on which the
    // server will be listening for incoming TCP connections.
    const int port_no = 5555;

    /* 
    A socket is a communication’s endpoint.
    In lines 37-40, we try to create a socket object called "s" that will use IPv4
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
    In line 47, we declare a struct of type 'sockaddr_in' called 'sin'. This structure is
    used to store IPv4 address information, such as the address family, the port number,
    and the IP address of the destination server.
    */
    struct sockaddr_in sin;

    /*
    First, we initialize the 'sin' structure to zero using the memset() function to ensure
    that all fields of the structure are set to a known value before we change
    them as we want.
    Then, we change some of the values of the fields of the 'sin' structure to match
    the destination server we want to communicate with.
    'sin_family'- AF_INET, meaning IPv4 addresses.
    'sin_addr.s_addr'- The representation of the IP address that we want to communicate
    with in binary format. This is done using the inet_addr() function, which converts the
    IP address from its string representation to a binary format that can be used in
    network communication.
    'sin_port'- the port number in network byte order. This is done using the htons()
    function, which converts the port number from host byte order to network byte order.
    */
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    /*
    We use the connect() function to connect the socket with a specific address and port.
    We call the connect() function with three arguments:
    1. The file descriptor of the socket we want to connect (sock).
    2. A pointer to a struct sockaddr that contains the address
    and port we want to connect to. We cast the pointer to the correct type
    because the connect() function expects a pointer to a struct sockaddr by using a type
    cast.
    3. The size of the address structure, which is given by sizeof(sin).
    If the connect() function returns a value less than 0, it means that there was
    an error connecting to the server, and we print an error message.
    */
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    /*
    The array 'data_addr' contains the string "Im a message" that we want to send to the server.
    The variable 'data_len' holds the length of the data we want to send,
    which is calculated using the strlen() function.
    */
    char data_addr[] = "Im a message";
    int data_len = strlen(data_addr);
    /*
    The send() function is used to send data over the socket.
    It takes four arguments:
    1. The file descriptor of the socket we want to send data through (sock).
    2. A pointer to the data we want to send (data_addr).
    3. The length of the data we want to send (data_len).
    4. Flags (0 in this case, meaning no special options).

    The send() function returns the number of bytes sent, or -1 if there was an error.
    If there was an error, we do nothing.
    */
    int sent_bytes = send(sock, data_addr, data_len, 0);

    // Change: I added an error message that will be printed if there was an error
    // sending the data to the server.
    if (sent_bytes < 0) {
    // error
        perror("An error occurred while sending data to the server.");
    }

    /*
    The array 'buffer' is used to store the data received from the server.
    The variable 'expected_data_len' holds the length of the data we expect to receive,
    which is calculated using the sizeof() function.
    The recv() function is used to receive data over the socket.
    It takes four arguments:
    1. The file descriptor of the socket we want to receive data from (sock).
    2. A pointer to the buffer where we want to store the received data (buffer).
    3. The length of the buffer (expected_data_len).
    4. Flags (0 in this case, meaning no special options).
    The recv() function returns the number of bytes received, or -1 if there was an error.
    If the returned value is 0, it means that the connection is closed, and we do nothing.
    If read_bytes < 0, it means there was an error, and we do nothing.
    If there was no error and the connection is not closed, we print the received data to the console.
    */
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
    }

    // Finally, we close the socket to clean up and release the system resources.
    close(sock);

    // We return 0 to indicate that the program ended successfully.
    return 0;
}