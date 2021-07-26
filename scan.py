#!/usr/bin/env python3
from socket import *
from sys import argv
from random import shuffle

if len(argv) == 1:
    print(f'Digite o seu host assim: {argv[0]} <IP/website_ip>')
    exit(1)

ports = [x for x in range(1,200)]
shuffle(ports)

def scan(host):
    for port in ports:
        s = socket(AF_INET, SOCK_STREAM)
        s.settimeout(.01)
        result_code = s.connect_ex((host, port))
        if result_code == 0:
            print(f'Porta: {port} ABERTA !!!')

scan(argv[1])
