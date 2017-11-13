#include "PseudoRandom.h"
#include <random>
#include <iostream>
#include <algorithm>
#include "time.h"

namespace buf
{

static int random_fd = -1;
static bool random_inited = false;
using rand_engine = std::mt19937;

int rand_between(int s, int e);

void PRandom::init_seed(int seed)
{
    random_fd = seed;
    random_inited = true;
}

int PRandom::operator()()
{
    return rand_between(0, 0x7FFFFFFF);
}

int PRandom::operator()(int max)
{
    return rand_between(0, max);
}

int PRandom::operator()(int min, int max)
{
    return rand_between(min, max);
}

int rand_between(int s, int e)
{
    if (!random_inited)
    {
        int value = 0;
        
        if (random_fd < 0)
        {
            std::random_device rdivce;
            random_fd = rdivce() + time(NULL);
        }
        
        random_inited = true;
    }

    std::uniform_int_distribution<> dis{std::min(s, e),std::max(s,e)};
    rand_engine gen(random_fd); 
    return dis(gen); 
}

}
/*
int main()
{
    int idx = 0;
    buf::PRandom rd;
    std::random_device rdivce;
    std::cout << "fitst random fanwei  is " << rd() << " !" << std::endl;
    while(1)
    {
        if (idx >= 5)
            break;
        rd.init_seed(10);
        std::cout << "random fanwei  is " << rd() << " !" << std::endl;
        idx++;
    }

    return 1;
}
*/
