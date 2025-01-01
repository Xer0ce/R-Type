#ifndef CONNEXION_HPP
#define CONNEXION_HPP

#include <memory>
#include <string>
#include "../network/tcp/Tcp.hpp"
#include "../network/udp/Udp.hpp"
#include "../network/IProtocol.hpp"

class Connexion {
public:
  Connexion(const std::string &ip_udp, int port_udp,
            const std::string &ip_tcp, int port_tcp);
  ~Connexion();

  void listen(std::unique_ptr<IProtocol> &protocol);

private:
  std::unique_ptr<Tcp> _tcp;
  std::unique_ptr<UDP> _udp;
};

#endif // CONNEXION_HPP