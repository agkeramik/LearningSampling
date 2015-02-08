#include "MContext.h"
#include <vector>

using namespace std;

class Sampler{
public:
    MContext* context;

    Sampler(MContext* context);

    void sample(Furniture* f);

    bool accept(Furniture* f){

    }

};
