#include <iostream>

#ifdef  _WIN32
#define _WIN32_WINNT 0x0A00
#endif //  _WIN32

#define ASIO_STANDALONE
#include <asio.hpp> // <== its handle Networking and I/O
#include <asio/ts/buffer.hpp> // <== Handles the memory transfer
#include <asio/ts/internet.hpp>

int main()
{




	return 0;
}
