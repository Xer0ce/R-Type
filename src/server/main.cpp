#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <arpa/inet.h>
#include <unistd.h>

void handle_tcp_client(int client_socket) {
    try {
        char buffer[1024];
        while (true) {
            // Receive data from the client
            int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) {
                std::cout << "Client disconnected or error occurred.\n";
                break;
            }

            // Parse and print the message
            std::cout << "TCP Message received: ";
            for (int i = 0; i < bytes_received; ++i) {
                std::cout << "0x" << std::hex << (int)buffer[i] << " ";
            }
            std::cout << std::dec << std::endl;

            // Echo the message back to the client
            send(client_socket, buffer, bytes_received, 0);
        }
    } catch (const std::exception &e) {
        std::cerr << "TCP Error: " << e.what() << std::endl;
    }

    close(client_socket);
}

void udp_listener(int udp_socket) {
    try {
        char buffer[1024];
        sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        while (true) {
            // Receive UDP packets
            int bytes_received = recvfrom(udp_socket, buffer, sizeof(buffer), 0, (sockaddr *)&client_addr, &addr_len);
            if (bytes_received < 0) {
                std::cerr << "UDP receive error.\n";
                break;
            }

            // Print the message
            std::cout << "UDP Message received: ";
            for (int i = 0; i < bytes_received; ++i) {
                std::cout << "0x" << std::hex << (int)buffer[i] << " ";
            }
            std::cout << std::dec << std::endl;

            // Optionally, send a response (uncomment to enable)
            // sendto(udp_socket, buffer, bytes_received, 0, (sockaddr*)&client_addr, addr_len);
        }
    } catch (const std::exception &e) {
        std::cerr << "UDP Error: " << e.what() << std::endl;
    }
}

int main() {
    const int tcp_port = 12345; // TCP port for Connect/Disconnect
    const int udp_port = 12346; // UDP port for Move/Shoot

    try {
        // TCP Server Setup
        int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (tcp_socket < 0) throw std::runtime_error("Failed to create TCP socket.");

        sockaddr_in tcp_addr{};
        tcp_addr.sin_family = AF_INET;
        tcp_addr.sin_port = htons(tcp_port);
        tcp_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(tcp_socket, (sockaddr *)&tcp_addr, sizeof(tcp_addr)) < 0) {
            throw std::runtime_error("Failed to bind TCP socket.");
        }

        if (listen(tcp_socket, 5) < 0) {
            throw std::runtime_error("Failed to listen on TCP socket.");
        }

        std::cout << "TCP Server listening on port " << tcp_port << std::endl;

        // UDP Server Setup
        int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (udp_socket < 0) throw std::runtime_error("Failed to create UDP socket.");

        sockaddr_in udp_addr{};
        udp_addr.sin_family = AF_INET;
        udp_addr.sin_port = htons(udp_port);
        udp_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(udp_socket, (sockaddr *)&udp_addr, sizeof(udp_addr)) < 0) {
            throw std::runtime_error("Failed to bind UDP socket.");
        }

        std::cout << "UDP Server listening on port " << udp_port << std::endl;

        // Threads for handling TCP and UDP
        std::thread udp_thread(udp_listener, udp_socket);

        while (true) {
            // Accept TCP clients
            sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_socket = accept(tcp_socket, (sockaddr *)&client_addr, &client_len);
            if (client_socket < 0) {
                std::cerr << "Failed to accept client.\n";
                continue;
            }

            std::cout << "Client connected.\n";
            std::thread tcp_thread(handle_tcp_client, client_socket);
            tcp_thread.detach();
        }

        // Clean up
        udp_thread.join();
        close(tcp_socket);
        close(udp_socket);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
