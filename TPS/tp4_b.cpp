#include <iostream>
#include "Mutex.h"

Mutex::Mutex(){
    pthread_mutex_init(posixId, nullptr);
}

Mutex::~Mutex(){
     pthread_mutex_destroy(posixId);
}

void Mutex::lock(){

}

bool Mutex::lock(double timeout_ms){

}

bool Mutex::trylock(){

}

void Mutex::unlock(){

}
