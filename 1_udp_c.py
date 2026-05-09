from socket import socket, AF_INET, SOCK_DGRAM

s = socket(AF_INET, SOCK_DGRAM)

dst_ip = '127.0.0.1'
dst_port = 12345

s.sendto(b'Hello', (dst_ip,dst_port))

data, sender_info = s.recvfrom(2048)
print(data.decode('utf-8'))
print(sender_info)

s.close()
