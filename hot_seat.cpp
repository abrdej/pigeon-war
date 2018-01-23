#include <boost/process.hpp>

using namespace boost::process;

int main() {

    ipstream pipe_stream;
    child server("./pigeonwar_server 5555");
    child client("./pigeonwar_client 127.0.0.1 5555");

    server.wait();
    client.wait();

    return 0;
}

