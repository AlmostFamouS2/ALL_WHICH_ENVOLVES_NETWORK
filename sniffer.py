#!/usr/bin/env python3
import socket
from os import name
from subprocess import getoutput

iii = getoutput('hostname -I |cut -d " " -f1')
print(iii)

def main():
    if name == 'nt':
        sockproto = socket.IPPROTO_IP
    else:
        sockproto = socket.IPPROTO_ICMP

    sniffer = socket.socket(socket.AF_INET, socket.SOCK_RAW, sockproto)
    sniffer.bind((iii, 0))
    sniffer.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)

    if name == 'nt':
        sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)
        print(sniffer.recvfrom(65565))
        sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_OFF)
    else:
        print(sniffer.recvfrom(65565))

if __name__ == '__main__':
    main()
