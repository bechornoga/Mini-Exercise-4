from socket import socket, AF_INET, SOCK_DGRAM

s = socket(AF_INET, SOCK_DGRAM)

src_ip = ''
src_port = 12345
s.bind((src_ip, src_port))

while True:
    data, sender_info = s.recvfrom(2048)
    print(data.decode('utf-8'))
    print(sender_info)

    s.sendto(data.upper(), sender_info)