
#ifndef PSEUDO_RANDOM_H_
#define PSEUDO_RANDOM_H_
/*
 * c++11 pseudo random
 *
*/

namespace buf
{

struct PRandom
{
    void init_seed(int seed);
    int operator()();
    int operator()(int max);
    int operator()(int min, int max);
    //int rand_between(int s, int e);
};

} // namespace buf

#endif // RANDOM_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */
