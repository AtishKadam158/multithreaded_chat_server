#include "client_handler.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>

void handle_client(int client_socket, std::vector<int>& clients, std::mutex& clients_mutex) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            std::cerr << "Client disconnected\n";
            close(client_socket);
            clients_mutex.lock();
            clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
            clients_mutex.unlock();
            break;
        }

        clients_mutex.lock();
        for (int client : clients) {
            if (client != client_socket) {
                send(client, buffer, bytes_received, 0);
            }
        }
        clients_mutex.unlock();
    }
}
