#include "MemBlockPool.h"

MemBlockPool::MemBlockPool(size_t size)
    :m_Size(size),m_pBlockList(NULL)
{
}

MemBlockPool::~MemBlockPool()
{
    while(m_pBlockList != NULL)
    {
        MemBlock* ptr = m_pBlockList;
        m_pBlockList = m_pBlockList->next;
        free(ptr);
    }
}

void* MemBlockPool::Alloc()
{
    void* ret = NULL;
    m_Mutex.lock();
    if(m_pBlockList != NULL)
    {
        ret = &m_pBlockList->data;
        m_pBlockList = m_pBlockList->next;
    }
    m_Mutex.unlock();
    if(ret == NULL)
    {
        MemBlock* block = (MemBlock*)malloc(sizeof(MemBlock) + m_Size);
        if(block != NULL)
        {
            ret = &block->data;
        }
    }
    return ret;
}

void MemBlockPool::Free(void* ptr)
{
    if(ptr == NULL) return;

    const static size_t DATA_OFFSET = (char*)(&((MemBlock*)1)->data) - (char*)(1);
    MemBlock* block = (MemBlock*)((char*)ptr - DATA_OFFSET);
    m_Mutex.lock();
    block->next = m_pBlockList;
    m_pBlockList = block;
    m_Mutex.unlock();
}


