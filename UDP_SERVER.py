#!/usr/bin/env python3
from socket import *

def udp():
    quit = False

    s = socket(AF_INET, SOCK_DGRAM)
    s.bind(('127.0.0.1', 4444))
    print('Server STARTED!!!')

    while not quit:
        msg, addr = recvfrom(1024)
        if msg.decode() == 'exit':
            quit = 1
        print(f'RECEIVED {len(msg)} BYTES:  {msg.decode()}    FROM: {addr}')
        s.sendto(b'RECEBIDO!', addr)

udp()
