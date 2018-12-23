#include <ws2tcpip.h>
#include <cinttypes>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace rvi
{
    typedef std::function<void(tcp_connection)> connection_callback_t;

    addrinfo get_socket_hints(bool will_bind);

    bool init_wsa(WSADATA* wsadata);

    bool fill_addrinfo(uint16_t port, const std::string host_addr, addrinfo* result);

    bool create_socket(addrinfo* ainfo, SOCKET* result);

    bool bind_socket(SOCKET sock, addrinfo* ainfo);
}