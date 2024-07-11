#include "server.h"
#include "client_handler.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>

Server::Server(int port) : port(port) {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket\n";
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed\n";
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        std::cerr << "Listen failed\n";
        close(server_socket);
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    close(server_socket);
}

void Server::start() {
    std::cout << "Server started, waiting for connections...\n";
    std::thread(&Server::accept_clients, this).detach();
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Server::accept_clients() {
    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket < 0) {
            std::cerr << "Accept failed\n";
            continue;
        }

        std::cout << "New client connected\n";
        clients_mutex.lock();
        clients.push_back(client_socket);
        clients_mutex.unlock();

        std::thread(handle_client, client_socket, std::ref(clients), std::ref(clients_mutex)).detach();
    }
}

void Server::broadcast(const char* message, int sender_socket) {
    clients_mutex.lock();
    for (int client : clients) {
        if (client != sender_socket) {
            send(client, message, strlen(message), 0);
        }
    }
    clients_mutex.unlock();
}
