#include "../include/addition/program_manager.hpp"

#include <iostream>


int main(int argc, char const *argv[]){
    try{
        ProgramManager manager(argc, argv);
        manager.run();
    } catch(const std::exception& e) {
        std::cerr << "\033[31m" << "КРИТИЧЕСКАЯ ОШИБКА STD: " 
            << e.what() << "\033[0m" << "\n";
        return 1;
    }
    std::cout << std::endl;
    return 0;
}
