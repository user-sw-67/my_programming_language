#include "../include/addition/program_manager.hpp"

#include <iostream>


int main(int argc, char const *argv[]){
    try{
        ProgramManager manager(argc, argv);
        manager.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    std::cout << std::endl;
    return 0;
}
