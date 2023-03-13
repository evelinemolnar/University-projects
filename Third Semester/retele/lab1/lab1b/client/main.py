import socket

HOST= "127.0.0.1"
PORT=1234

with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
    s.connect((HOST,PORT))
    s1=input("s1: ").encode();
    s.sendall(s1);
    s2 = input("s2: ").encode();
    s.sendall(s2);

    