#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

const int PORT = 8080;
const int BUFFER_SIZE = 4096;

int main() {
    // 1. Create a socket file descriptor for the proxy server
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error: Failed to create socket.\n";
        return 1;
    }

    // 2. Set socket options to avoid the "Address already in use" kernel lock error
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error: setsockopt failed.\n";
        close(server_fd);
        return 1;
    }

    // 3. Bind the socket to the port
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all available local interfaces
    address.sin_port = htons(PORT);       // Convert port number to network byte order

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Error: Bind failed.\n";
        close(server_fd);
        return 1;
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 10) < 0) { // 10 is the maximum length of the pending connections queue
        std::cerr << "Error: Listen failed.\n";
        close(server_fd);
        return 1;
    }

    std::cout << "SiphonX Proxy Server listening on port " << PORT << "...\n";

    // 5. Accept connections in an infinite loop
    while (true) {
        sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        
        // accept() blocks until a client (like a browser) attempts to connect
        int client_socket = accept(server_fd, (struct sockaddr*)&client_address, &client_len);
        
        if (client_socket < 0) {
            std::cerr << "Error: Accept failed.\n";
            continue; // Skip to the next iteration to keep the server alive
        }

        std::cout << "Success: Client connected!\n";
        
        // Phase 1 is just accepting the connection, so we immediately close it for now.
        close(client_socket);
    }

    close(server_fd);
    return 0;
}