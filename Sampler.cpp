#include "Sampler.h"
#include "Scene.h"

Sampler::Sampler(MContext* context){
    this->context = context;
}

void Sampler::sample(Furniture* f){
    while (!accept(f)){

    }
}
