#ifndef DATA_INTERFACE
#define DATA_INTERFACE

#include <functional>

struct DataInterface {
    std::function<void(void*)> mDestroy;

    DataInterface(){}

    DataInterface(std::function<void(void*)> destroy){
        mDestroy = destroy;
    }
};

#endif
