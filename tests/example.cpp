#include <softloq/whatwg/encoding.hpp>
#include <softloq/whatwg/infra.hpp>
#include <iostream>

#include <thread>

int main()
{
    using namespace softloq::whatwg;
    io_queue_stream<infra_byte> stream{0xB, 0xCE, 0xED};
    stream.restore_items(infra_list<io_queue_item<infra_byte>>{{0x2D}, {0x3E}});
    std::thread thread1([&stream]() {
        std::cout << stream.peek_items(7) << std::endl;
    });
    std::thread thread2([&stream]() {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        stream.push_item({0xFE});
        std::this_thread::sleep_for(std::chrono::seconds(5));
        stream.push_item({0xFF}); 
    });
    thread1.join();
    thread2.join();
    // stream.push_item({0xFE});
    

    // io_queue_immediate<infra_byte> stream;
    // stream.front()
    // io_queue_stream<infra_byte> stream{0xB, 0xCE, 0xED};
    // stream.sort_descending();
    // // if (stream.empty()) std::cout << "Empty" << std::endl;
    // std::cout << "IO: " << stream.read_item() << stream.read_item() << stream.read_item() << stream.read_item() <<  std::endl;

    return 0;
}