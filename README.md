Asio Networking 

This project provides a basic example of using the Asio library for asynchronous networking in C++. It demonstrates how to establish a TCP connection to a remote server, send an HTTP request, and asynchronously receive data.

Prerequisites

* C++ compiler with support for C++17 or later.
* Asio library (included as a submodule).
* A target machine with an internet connection for testing the connection.


Getting Started

1. Clone the repository:

* git clone https://github.com/yourusername/asio-networking-example.git


2. Initialize and update the submodule:

* cd asio-networking-example
* git submodule update –init


3. Build the project using your preferred C++ build system (e.g., CMake, Makefile).

* mkdir build
* cd build
* cmake ..
* make


Usage

1. Run the compiled executable:

./asio-networking-example

2. The program will attempt to establish a connection to the specified IP address and port (in this example, "51.38.81.49" and port 80). The connection status will be displayed.

3. If the connection is successful, an HTTP request will be sent to the server ("example.com"). The received data will be printed to the console.

4. The program will run for a specified period (in this example, 2000 milliseconds) to demonstrate asynchronous data handling.


Customization

* You can modify the IP address, port, and HTTP request in the main function of main.cpp to suit your requirements.

License
* This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgements

* Asio Library

Feel free to modify and extend this example for your specific use case. If you encounter any issues or have suggestions for improvement, please open an issue or submit a pull request.
