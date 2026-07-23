# SiphonX

### High-Performance Multithreaded HTTP Proxy Server

**SiphonX** is a custom-built, multithreaded HTTP proxy server engineered in C++. Designed to handle concurrent client connections efficiently, it transparently forwards requests between clients and web servers while optimizing repeated requests through a custom caching mechanism. 

This project demonstrates core systems programming principles, bypassing high-level web frameworks to directly manipulate POSIX sockets, manage memory, and handle multithreaded synchronization.

---

## 🚀 Features

* **Custom POSIX Socket Pipeline:** Built from scratch using native Linux networking libraries (`sys/socket.h`, `netinet/in.h`) for deep, low-level control over TCP/IP connections.
* **Concurrency & Thread Pooling:** Engineered a synchronized thread pool utilizing task queues and condition variables (`std::mutex`, `std::condition_variable`). This allows the server to scale under concurrent workloads while minimizing thread creation overhead.
* **O(1) LRU Caching:** Integrates a thread-safe Least Recently Used (LRU) cache using a Hash Map (`std::unordered_map`) and a Doubly Linked List (`std::list`) to store HTTP responses, drastically reducing response latency for repeated requests.
* **Modular HTTP Parsing:** Custom string processing to extract hostnames, methods, and routing information from raw HTTP headers.

---

## 🛠️ Technology Stack

* **Language:** C++ 
* **Environment:** Linux / WSL (Ubuntu)
* **Core Concepts:** TCP/IP Networking, Concurrency, Multithreading, Data Structures, System Calls

---

## ⚙️ Build and Run Instructions

### Prerequisites
* A Linux environment (or Windows Subsystem for Linux - WSL).
* `g++` compiler installed.

### Compilation
Navigate to the root directory of the project and compile the source code:

```bash
g++ src/server.cpp -o server

```
# Execution
 Run the compiled binary to start the server. By default, it will listen on port 8080.
 
```
 ./server
```
# Testing the Proxy
Once the server is running, you can test it by opening a new terminal tab and using curl:

```
curl http://localhost:8080

```