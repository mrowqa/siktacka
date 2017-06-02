#include "Client.hpp"

#include <iostream>


static constexpr auto server_default_port = 12345;
static constexpr auto gui_default_hostname = "localhost";
static constexpr auto gui_default_port = 12346;


Client::Client(int argc, char **argv) noexcept {
    parseArguments(argc, argv);
}

void Client::parseArguments(int argc, char **argv) noexcept {
    if (argc < 3 || 4 < argc) {
        std::cerr << "Usage: ./siktacka-client player_name game_server_host[:port] "
                "[ui_server_host[:port]]\n";
        exit(1);
    }

    auto with_default_port = [](std::string hostname, unsigned short port) {
        return hostname.find(':') == std::string::npos
               ? hostname + ':' + std::to_string(port) : hostname;
    };

    // TODO validate player_name!
    player_name = argv[1];
    try {
        server_address = std::make_unique<HostAddress>(with_default_port(argv[2], server_default_port));
        gui_address = std::make_unique<HostAddress>(
                with_default_port(argc == 4 ? argv[3] : gui_default_hostname, gui_default_port));
    }
    catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        exit(1);
    }
}
