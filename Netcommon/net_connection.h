#pragma once
#include "net_common.h"
#include "Net_threadSafe_Queue.h"
#include "net_message.h"


namespace olc
{
	namespace net
	{

		template<typename T>
		class connection : public std::enable_shared_from_this<connection<T>>
		{
		public:
			connection(){ }

			virtual ~connection(){}



		public:
			// Only by Client 
			bool ConnectToServer();
			// Only called by server and client
			bool Disconnect();
			
			bool IsConnected() const;
			bool sent(const message<T>& msg);

		protected:
			// Each connection has a unique socket to a remote
			asio::ip::tcp::socket m_socket;

			// This context is shared with the whole asio instance
			asio::io_context& m_asioContext;

			// This queue holds all messages to be sent to the remote side of this connection
			tsqueue<message<T>> m_qMessagesOut;

			/* This queue holds all messages that have been received from the remote side of this 
			connection. Nte it is a reference as the "owner" of this connection is expected to provide a queue*/
			tsqueue<owned_message>& m_qMessagesIn;



		};


		template<typename T>
		inline bool connection<T>::ConnectToServer()
		{
			return false;
		}

		template<typename T>
		inline bool connection<T>::Disconnect()
		{
			return false;
		}

		template<typename T>
		inline bool connection<T>::IsConnected() const
		{
			return false;
		}

		template<typename T>
		inline bool connection<T>::sent(const message<T>& msg)
		{
			return false;
		}

	}
}