#pragma once
#include "net_common.h"
#include "Net_threadSafe_Queue.h"
#include "net_message.h"
#include "net_connection.h"

namespace olc
{
	namespace net
	{
		template <typename T>
		class client_interface
		{
			public:

			client_interface() : m_socket(m_context)
			{
				// Initialise the socket with the io contex, so it can do stuff
			}

			virtual ~client_interface()
			{
				// If the client is destroyed, always try and disconnect from server
				Disconnect(
			}




			// Connect to server with hostname/ip-address and port
			bool Connect(const std::string& host, const uint16_t port)
			{
				try
				{
					// Create the connection 
					m_connection = std::make_unique<connection<T>>(); // TODO

					// Resolve hostname/ip-address into tangible physical adders
					asio::ip::tcp::resolver resolver(m_context);
					m_endpoints = resolver.resolve(host, std::to_string(port));

					// Tell the connection object to connect to server
					m_connection->ConectToServer(m_endpoints);

					// Start context Thread
					thrContext = std::thread([this]() {m_context.run(); });

				}
				catch (const std::exception& e)
				{
					std::cerr << "Client Exception: " << e.what() << "\n";
					return false;
				}


				return true;
			}

			// Disconnect from server
			void Disconnect()
			{
				if (isConnected())
				{
					// ..disconnect from server gracefully
					m_connection->Disconnect();
				}

				// Either way, we're also done with the asio context
				m_context.stop();
				//...and its thread
				if (thrContext.joinable())
					thrContext.join();

				// Destroy the connection object
				m_connection.release();



			}

			// Check if client is actually connected to a server
			bool isConnected()
			{
				if (m_connection)
				{
					return m_connection->IsConnected();
				}
				else
				{
					return false;
				}
			}
			// Retreive queue of messages from server
			tsqueue<owned_message<T>>& Incoming()
			{
				return m_connection;
			}




		protected:
			// asio context handles the data transfer...
			asio::io_context m_context;
			// Context needs thread of its own to execute its work commands
			std::thread thrContext;
			// this is the hardware socket that is connected to the server
			asio::ip::tcp::socket m_socket;
			// The client has a single instance of a "connection" object, which handles data transfer
			std::unique_ptr<connection<T>> m_connection;




		private:
			// this is the thread safe queue of incoming messages from server
			tsqueue<owned_message<T>> m_qMessagesIn;





		};
	}
}