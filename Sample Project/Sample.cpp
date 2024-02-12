#include <chrono>
#include <iostream>

#ifdef  _WIN32
#define _WIN32_WINNT 0x0A00
#endif //  _WIN32

#define ASIO_STANDALONE
#include <asio.hpp> // <== its handle Networking and I/O
#include <asio/ts/buffer.hpp> // <== Handles the memory transfer
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket)
{
	//socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()));
	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
	[&](std::error_code ec, std::size_t lenght)
		{
			if (!ec)
			{
				std::cout << "\n\nRead " << lenght << "bytes\n\n";

				for (int i = 0; i < lenght; i++)
				{
					std::cout << vBuffer[i];
				}
				GrabSomeData(socket);
			}
		}
	);
}



int main()
{

	asio::error_code ec;

	// Create a "context" - essentially the platform specific interface
	asio::io_context context;

	// give some fake tasks to asio so the context dosent finish
	asio::io_context::work idleWork(context);

	// start the context
	std::thread thrContext = std::thread([&]() {context.run(); });


	// Get the address of somewhere we wish to connect
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);

	// Create a socket, that context will deliver the implementation
	asio::ip::tcp::socket socket(context);

	// Tell socket to try and connect
	socket.connect(endpoint, ec);

	if (!ec)
	{
		std::cout << "Connected" << "\n";
	}
	else
	{
		std::cout << "Failed to connect to address: \n" << ec.message() << "\n";
	}

	if (socket.is_open())
	{
		GrabSomeData(socket);

		std::string sRequest = "GET /index.html HTTP/1.1\r\r" "HOST: example.com\r\n" "Connection: close\r\n\r\n";
		
		// .write_some means try to send this much data
		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
		
		
		// Program dose something else, while also handles data transfer in background
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(2000ms);

	}

	system("pause");

	return 0;
}
