#include <fstream>
#include <string>

class CyStream {
    private:
        std::fstream f;
        bool isOpen;

    public:
        void open(const std::string &filename, std::ios_base::openmode mode = std::ios_base::in|std::ios_base::out);
        void close();
        ~CyStream();
};
