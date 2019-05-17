#!/usr/bin/env python2
# -*- coding: utf-8 -*-

# Author: David Manouchehri <manouchehri@protonmail.com>
# This script will always echo back data on the UDP port of your choice.
# Useful if you want nmap to report a UDP port as "open" instead of "open|filtered" on a standard scan.
# Works with both Python 2 & 3.

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = '0.0.0.0'
server_port = 1337

server = (server_address, server_port)
sock.bind(server)
print("Listening on " + server_address + ":" + str(server_port))

clients = []

while True:
    payload, client_address = sock.recvfrom(1000)
    if client_address not in clients:
        clients.append(client_address)

    for client in clients:
        print("Echoing data back to " + str(client) + "payload : " + payload)
        sent = sock.sendto(payload, client)

