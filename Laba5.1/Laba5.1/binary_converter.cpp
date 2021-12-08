#include "Header.hpp"

std::string TXT_FILE_NAME = "myinfofile.txt";
std::string BINARY_FILE_NAME = "myinfofile.bin";

template<class T>
char* as_bytes(T& i)
{
    void* addr = &i;
    return static_cast<char*>(addr);
}

void convert_to_bin()
{
    std::ifstream ifs(TXT_FILE_NAME); 
    char S[1024] = {};
    ifs.read(S, sizeof(S));
    ifs.close();

    std::ofstream ofs(BINARY_FILE_NAME.c_str(), std::ios_base::binary);
    ofs << as_bytes(S);
    ofs.close();
}
std::string convert_from_bin()
{
    std::ifstream ifs(BINARY_FILE_NAME.c_str(), std::ios_base::binary);
    char content[1024] = {};
    ifs.read(as_bytes(content), sizeof(content));
    ifs.close();

    return std::string(content);
}