// In lines 2-8, we include the necessary headers for our program.
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// In line 11, we use namespace std to avoid having to
// prefix standard library names with "std::".
using namespace std;

// In line 15, we define the main function, which is the entry point of our program.
int main() {

    // Here, we set the destination IP address to be '127.0.0.1', which means that the client
    // will communicate with a server that is running on the same machine.

    // Change: I changed the ip address to "10.0.0.50" (the local IP address of
    // my machine) instead of "127.0.0.1", which means that the client will be communicating
    // with a server that is running on the same machine but using the local IP address instead
    // of the loopback address.
    const char* ip_address = "10.0.0.50";
    // Here, we set the destination port to 5555. This is the port number on which the
    // server will be listening for incoming UDP packets.
    const int port_no = 5555;

    /* A socket is a communication’s endpoint.
    In lines 37-40, we try to create a socket object called "s" that will use IPv4
    addresses and the UDP protocol for communication.
    The socket() function gets 3 arguments:
    1. The first argument is the address family- In our case, AF_INET. It indicates that
    we would like to use IPv4 addresses.
    2. The second argument specifies the type of socket- In our case, SOCK_DGRAM.
    It indicates that we want to use the UDP protocol for communication.
    3. The third argument specifies the protoco- In our case, 0. It means that we want
    to use the default protocol for UDP.
    The socket() function returns a file descriptor for the new socket, or -1 if there 
    was an error. If there was an error, we print an error message.
    */ 
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
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
    The array 'data' contains the string "hello" that we want to send to the server.
    The variable 'data_len' holds the length of the data we want to send,
    which is calculated using the sizeof() function.
    */
    char data[] = "hello";
    int data_len = sizeof(data);

    /*
    We use the sendto() function with the following parameters to send the UDP packet to
    the destination server:
    1. The file descriptor for the socket ('sock').
    2. A pointer to the 'data' array.
    3. The desired data length ('data_len').
    4. 0: No other flags.
    5. An address structure pointer to the destination server. To match the expected type
    of the argument in this instance, we cast the address of "sin" to a pointer of type
    "struct sockaddr *."
    6. We use the sizeof() function to determine the address structure's size.
    The function returns the number of bytes sent, or -1 if there was an error.
    If there was an error, we print an error message using the perror() function.
    */
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    /*
    We use the recvfrom() function with the following parameters to receive the UDP packet
    from the destination server:
    1. The file descriptor for the socket ('sock').
    2. A pointer to the 'buffer' array.
    3. The size of the buffer ('sizeof(buffer)').
    4. 0: No other flags.
    5. An address structure pointer to store the sender's address. To match the expected
    type of the argument in this instance, we cast the address of "from" to a pointer of
    type "struct sockaddr *."
    6. A pointer to a variable ('&from_len') containing the size of the address structure. 
    The function will update this variable with the actual size of the sender's address.
    
    The function returns the number of bytes received, or -1 if there was an error.
    If there was an error, we print an error message using the perror() function.
    */
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    // We print the message received from the server to the console.
    cout << "The server sent: " << buffer << endl;

    // Finally, we close the socket, clean up and release the system resources.
    close(sock);

    // We return 0 to indicate that the program ended successfully.
    return 0;
}