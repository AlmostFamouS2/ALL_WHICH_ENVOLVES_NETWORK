#!/usr/bin/env python3
from socket import *

def main():
    with socket(AF_INET, SOCK_STREAM) as sock:     #  IPv4 and TCP
        sock.bind(('0.0.0.0', 443))
        sock.listen(1)

        conn, addr = sock.accept()
        with conn:
            print(f'Connected by: {addr}')

            # while 1:
            data = conn.recv(512)

            if len(data) == 0:
                print('O cliente nao enviou nada')

            else:
                data = data.decode()   # Decodificar Antes
                print(f'\x1b[32mO CLIENTE ENVIOU: {data}')
                print('Enviando de volta, porem com hexadecimal\x1b[0m')

                aux = ''

                for n in data:
                    aux += hex(ord(n))[2:] + ' '

                data = aux
                data = data.encode()

                conn.sendall(data)

if __name__ == '__main__':
    main()