# We import the socket module.
import socket

# In this line, we create a socket object called "server".
# A socket is a communication’s endpoint.
# AF_INET- the address family for IPv4 addresses.
# SOCK_STREAM- the TCP protocol.
# This socket will use IPv4 addresses and the TCP protocol for communication.
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Here, we set the server IP address to '', which means that the server will listen
# on all available network interfaces.
server_ip = ''
# Here, we set the server port to 12345. This is the port number on which the
# server will be listening for incoming TCP connections.
server_port = 12345
# In this line, we bind our server socket to the local IP address and port number. 
# This tells the operating system to route all incoming TCP traffic on this 
# port to our Python program.
server.bind((server_ip, server_port))
# In this line, we tell the server to start listening for incoming connections. The maximum number
# of queued connections is 5.
server.listen(5)

# This line indicates that the server will be running forever, constantly waiting for 
# incoming TCP connections from clients.
while True:
    # In this line, we accept a connection from a client. This function will not return until a
    # client connects to the server. When a client connects, the function returns a new socket object
    # that is used to communicate with the client, and the client's address (IP address and
    # port number).
    client_socket, client_address = server.accept()
    # We print the client's address to the console.
    print('Connection from: ', client_address)
    # This line means that we are reading data from the TCP stream sent by the server.
    # The argument 1024 specifies the maximum number of bytes to receive at once.
    # The received byte string will be stored in the variable called "data".
    data = client_socket.recv(1024)
    # We use a while loop to keep receiving data from the client until the client disconnects.
    while not data.decode('utf-8') == '':
        # In this line, we decode the data we received from the server using UTF-8 encoding
        # and then we print it to the console.
        print('Received: ', data.decode('utf-8'))
        # In this line, we change the data we received from the client to be all uppercase
        # letters, and then we send it back to the client using client_socket.
        client_socket.send(data.upper())
        # This line means that we are reading data from the TCP stream sent by the server.
        # The argument 1024 specifies the maximum number of bytes to receive at once.
        # The received byte string will be stored in the variable called "data".
        data = client_socket.recv(1024)

    # When the client disconnects, we print the following message to the console: "Client disconnected".
    print('Client disconnected')
    # Finally, we close the client socket, clean up and release the system resources.
    client_socket.close()