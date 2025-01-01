#include <softloq/whatwg/encoding.hpp>
#include <softloq/whatwg/infra.hpp>
#include <iostream>
int main()
{
    using namespace softloq::whatwg;
    io_queue_immediate<infra_byte> stream{0xB, 0xCE, 0xED};

    std::cout << "IO: " << stream << std::endl;

    return 0;
}