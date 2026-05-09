# We import the socket module.
import socket

# In this line, we create a socket object called "s".
# A socket is a communication’s endpoint.
# AF_INET- the address family for IPv4 addresses.
# SOCK_STREAM- the TCP protocol.
# This socket will use IPv4 addresses and the TCP protocol for communication.
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Here, we set the destination IP address to be '127.0.0.1', which means that the client
# will communicate with a server that is running on the same machine.
dest_ip = '127.0.0.1'
# Here, we set the destination port to 12345. This is the port number on which the
# server will be listening for incoming TCP connections.
dest_port = 12345
# In this line, we connect our socket to the server's address, which is a tuple containing the
# destination IP address and port.
s.connect((dest_ip, dest_port))

# Here, we ask the client to input a message to send to the server.
msg = input("Message to send: ")
# We use a while loop to keep sending messages to the server until the user types 'quit'.
# Change: I changed the condition of the while loop to be: "while not msg == 'exit':", 
# which means that the client socket will keep sending messages to the server until the user types 'exit'.
while not msg == 'exit':
    # We send the message to the server, after converting the message to bytes using UTF-8 encoding.
    s.send(bytes(msg, 'utf-8'))
    # This line means that we are reading data from the TCP stream sent by the server.
    # The argument 4096 specifies the maximum number of bytes to receive at once.
    # The received byte string will be stored in the variable called "data".
    data = s.recv(4096)
    # In this line, we decode the data we received from the server using UTF-8 encoding
    # and then we print it to the console.
    print("Server sent: ", data.decode('utf-8'))
    # We ask the client to input another message to send to the server.
    msg = input("Message to send: ")

# Finally, we close the socket, clean up and release the system resources.
s.close()