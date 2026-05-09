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

    // Here, we set the destination port to 5555. This is the port number on which the
    // server will be listening for incoming UDP packets.
    const int server_port = 5555;

    /* A socket is a communication’s endpoint.
    In lines 34-37, we try to create a socket object called "s" that will use IPv4
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
        perror("error binding to socket");
    }

    /*
    We use the recvfrom() function with the following parameters to receive the UDP packet
    from the client:
    1. The file descriptor for the socket ('sock').
    2. A pointer to the 'buffer' array.
    3. The size of the buffer ('sizeof(buffer)').
    4. 0: No other flags.
    5. An address structure pointer to store the sender's address. To match the expected
    type of the argument in this instance, we cast the address of "from" to a pointer of
    type "struct sockaddr *."
    6. 6. A pointer to a variable ('&from_len') containing the size of the address structure. 
    The function will update this variable with the actual size of the sender's address.
    
    The function returns the number of bytes received, or -1 if there was an error.
    If there was an error, we print an error message using the perror() function.
    */
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);

    // Change: I changed the maximum packet size to 1024 bytes instead of 4096 bytes, which
    // means that the client will only be able to receive UDP packets from the server that are up to
    // 1024 bytes in size.
    char buffer[1024];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    // We print the message received from the client to the console.
    cout << "The client sent: " << buffer << endl;

    /*
    We use the sendto() function with the following parameters to send the UDP packet to
    the destination client:
    1. The file descriptor for the socket ('sock').
    2. A pointer to the 'data' array.
    3. The desired data length ('data_len').
    4. 0: No other flags.
    5. An address structure pointer to the destination client. To match the expected type
    of the argument in this instance, we cast the address of "from" to a pointer of type
    "struct sockaddr *."
    6. We use the sizeof() function to determine the address structure's size.
    The function returns the number of bytes sent, or -1 if there was an error.
    If there was an error, we print an error message using the perror() function.
    */
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    // Finally, we close the socket, clean up and release the system resources.
    close(sock);

    // We return 0 to indicate that the program ended successfully.
    return 0;
}