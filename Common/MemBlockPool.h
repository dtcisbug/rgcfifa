#ifndef _MEMBLOCK_POOL_H_
#define _MEMBLOCK_POOL_H_

#include <memory.h>
#include "Mutex.h"

/**
 *@brief 空闲块队列
 */
class MemBlockPool
{
    /**
     *@brief 内存块
     */
    struct MemBlock
    {
        MemBlock* next;   //下一个内存块
        char   data[1];   //用户数据区
    };

public:
    explicit MemBlockPool(size_t size);
    ~MemBlockPool();

    void* Alloc();
    void Free(void* ptr);

private:
    //每块大小
    const size_t  m_Size;
    //内存块链表
    MemBlock* m_pBlockList;
    //互斥锁
    FastMutex m_Mutex;
};


#endif

