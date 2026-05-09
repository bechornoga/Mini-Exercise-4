# In this line of code, we import from the socket module the socket class
# and the constants AF_INET and SOCK_DGRAM.
# We will use them to:
# The socket class- create a socket object.
# AF_INET- use IPv4 addresses.
# SOCK_DGRAM- use the UDP protocol.
from socket import socket, AF_INET, SOCK_DGRAM

# In this line, we create a socket object called "s".
# A socket is a communication’s endpoint.
# This socket will use IPv4 addresses and the UDP protocol for communication.
s = socket(AF_INET, SOCK_DGRAM)

# Here, we set the source IP address to '', which means that the server will listen
# on all available network interfaces.
src_ip = ''
# Here, we set the source port to 12345. This is the port number on which the
# server will be listening for incoming UDP packets.

# Change: We change the source port to 11111, which means that the server will be listening
# for incoming UDP packets on port 11111 instead of 12345.
src_port = 11111
# A UDP socket is identified by (Src IP, Src port). In this line, we bind our socket
# to src_ip and src_port.
s.bind((src_ip, src_port))

# This line indicates that the server will be running forever, constantly waiting for 
# incoming UDP packets from clients.
while True:
    # This line means that we are waiting to receive a UDP packet from the client.
    # A packet's size can be up to 2048 bytes in size.
    # When a packet is received, the data will be stored in the variable which is
    # called "data", and the client's information (IP address and port) will be stored
    # in the variable "sender_info". 

    # Change: I changed the maximum packet size to 1024 bytes instead of 2048 bytes,
    # which means that the server will only be able to receive UDP packets from the client that are
    # up to 1024 bytes in size.
    data, sender_info = s.recvfrom(1024)
    # In this line, we decode the data we received from the client using UTF-8 encoding,
    # and then we print it to the console.
    print(data.decode('utf-8'))
    # In this line, we print the sender's information, which is a tuple containing the
    # sender's IP address and port number.
    print(sender_info)

    # In this line, we change the data we received from the client to be all uppercase
    # letters, and then we send it back to the client who matches the sender_info.

    # Change: We change the data we send back to the client to be the lowercase version of the
    # data we received from the client instead of sending back the same data.
    s.sendto(data.lower(), sender_info)