# Through this line of code, we import from the socket module the socket class
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

# Here, we set the destination IP address to be '127.0.0.1', which means that the client
# will communicate with a server that is running on the same machine.
dst_ip = '127.0.0.1'
# Here, we set the destination port to 12345. This is the port number on which the
# server will be listening for incoming UDP packets.

# Change: We change the destination port to 11111, which means that the client will be sending
# UDP packets to the server on port 11111 instead of 12345.
dst_port = 11111

# In this line, we send a UDP packet containing the message 'Hello' to the server.
s.sendto(b'Hello', (dst_ip,dst_port))

# This line means that we are waiting to receive a UDP packet from the server.
# A packet's size can be up to 2048 bytes in size.
# When a packet is received, the data will be stored in the variable which is called "data",
# and the sender's information (IP address and port) will be stored in the variable
# "sender_info". 

# Change: I changed the maximum packet size to 1024 bytes instead of 2048 bytes,
# which means that the client will only be able to receive UDP packets from the server that are up to
# 1024 bytes in size.
data, sender_info = s.recvfrom(1024)
# In this line, we decode the data we received from the server using UTF-8 encoding
# and then we print it to the console.
print(data.decode('utf-8'))
# In this line, we print the sender's information, which is a tuple containing the
# sender's IP address and port number.
print(sender_info)

# Finally, we close the socket, clean up and release the system resources.
s.close()
