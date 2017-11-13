#ifndef NODE_INC
#define NODE_INC

#include <cassert>

#ifdef __cplusplus
extern "C" {
#endif

#define INET_FREELIST_HEAD(name, size)                                         \
	struct name {                                                                  \
	unsigned m_Size;                                                       \
	unsigned m_Count;                                                      \
	void*    m_Nodes[size];                                                \
	}

#define INET_FREELIST_INIT(head, size)                                         \
	do {                                                                           \
	(head)->m_Size = size; (head)->m_Count = 0;                            \
	} while (0)

#define INET_FREELIST_PUSH(head, node)                                         \
	((head)->m_Count == (head)->m_Size ? 0 :                               \
	((head)->m_Nodes[(head)->m_Count++] = node))

#define INET_FREELIST_POP(head)                                                \
	((head)->m_Count == 0 ? NULL : (head)->m_Nodes[--(head)->m_Count])

#define INET_FREELIST_EMPTY(head) ((head)->m_Count == 0)

	/**
	* Single List Define
	*/

#define INET_LIST_HEAD(name, type)                                             \
	struct name {                                                                  \
	struct type *m_First;    /* first element */                               \
	void* m_UsrPtr;          /* reversed for user */                           \
	}

#define INET_LIST_ENTRY(type)                                                  \
	struct {                                                                       \
	struct type *m_Next;     /* next element */                                \
	}

#define	INET_LIST_FIRST(head) ((head)->m_First)
#define	INET_LIST_END(head) NULL
#define	INET_LIST_EMPTY(head) (INET_LIST_FIRST(head) == INET_LIST_END(head))
#define	INET_LIST_NEXT(elm, field) ((elm)->field.m_Next)

#define	INET_LIST_FOREACH(var, head, field)                                    \
	for((var) = INET_LIST_FIRST(head);  (var) != INET_LIST_END(head);          \
	(var) = INET_LIST_NEXT(var, field))

#define	INET_LIST_INIT(head) {                                                 \
	INET_LIST_FIRST(head) = INET_LIST_END(head);                               \
	(head)->m_UsrPtr = NULL;                                                   \
}

#define	INET_LIST_INSERT_AFTER(slistelm, elm, field) do {                      \
	(elm)->field.m_Next = (slistelm)->field.m_Next;                            \
	(slistelm)->field.m_Next = (elm);                                         \
} while (0)

#define	INET_LIST_INSERT_HEAD(head, elm, field) do {                           \
	(elm)->field.m_Next = (head)->m_First;                                     \
	(head)->m_First = (elm);                                                   \
} while (0)

#define	INET_LIST_REMOVE_HEAD(head, field) do {                                \
	(head)->m_First = (head)->m_First->field.m_Next;                           \
} while (0)

	/**
	* Double List Define
	*/

#define INET_DLIST_HEAD(name, type)                                            \
	struct name {                                                                  \
	struct type *m_First;    /* first element */                               \
	struct type **m_Last;    /* address of last next element */                \
	}

#define INET_DLIST_ENTRY(type)                                                 \
	struct {                                                                       \
	struct type *m_Next;     /* next element */                                 \
	struct type **m_Prev;    /* address of previous next element */             \
	}

#define	INET_DLIST_FIRST(head) ((head)->m_First)
#define	INET_DLIST_END(head) NULL
#define	INET_DLIST_NEXT(elm, field) ((elm)->field.m_Next)
#define INET_DLIST_LAST(head, headname)                                        \
	(*(((struct headname *)((head)->m_Last))->m_Last))
#define INET_DLIST_PREV(elm, headname, field)                                  \
	(*(((struct headname *)((elm)->field.m_Prev))->m_Last))
#define	INET_DLIST_EMPTY(head)                                                 \
	(INET_DLIST_FIRST(head) == INET_DLIST_END(head))

#define INET_DLIST_FOREACH(var, head, field)                                   \
	for((var) = INET_DLIST_FIRST(head); (var) != INET_DLIST_END(head);         \
	(var) = INET_DLIST_NEXT(var, field))

#define	INET_DLIST_INIT(head) do {                                             \
	(head)->m_First = NULL;                                                    \
	(head)->m_Last = &(head)->m_First;                                         \
} while (0)

#define INET_DLIST_INSERT_HEAD(head, elm, field) do {                          \
	if (((elm)->field.m_Next = (head)->m_First) != NULL)                        \
	(head)->m_First->field.m_Prev = &(elm)->field.m_Next;                  \
	else                                                                       \
	(head)->m_Last = &(elm)->field.m_Next;                                 \
	(head)->m_First = (elm);                                                   \
	(elm)->field.m_Prev = &(head)->m_First;                                    \
} while (0)

#define INET_DLIST_INSERT_TAIL(head, elm, field) do {                          \
	(elm)->field.m_Next = NULL;                                                \
	(elm)->field.m_Prev = (head)->m_Last;                                      \
	*(head)->m_Last = (elm);                                                   \
	(head)->m_Last = &(elm)->field.m_Next;                                     \
} while (0)

#define INET_DLIST_INSERT_AFTER(head, listelm, elm, field) do {                \
	if (((elm)->field.m_Next = (listelm)->field.m_Next) != NULL)               \
	(elm)->field.m_Next->field.m_Prev = &(elm)->field.m_Next;              \
	else                                                                       \
	(head)->m_Last = &(elm)->field.m_Next;                                 \
	(listelm)->field.m_Next = (elm);                                           \
	(elm)->field.m_Prev = &(listelm)->field.m_Next;                            \
} while (0)

#define	INET_DLIST_INSERT_BEFORE(listelm, elm, field) do {                     \
	(elm)->field.m_Prev = (listelm)->field.m_Prev;                             \
	(elm)->field.m_Next = (listelm);                                           \
	*(listelm)->field.m_Prev = (elm);                                          \
	(listelm)->field.m_Prev = &(elm)->field.m_Next;                            \
} while (0)

#define INET_DLIST_REMOVE(head, elm, field) do {                               \
	if (((elm)->field.m_Next) != NULL)                                         \
	(elm)->field.m_Next->field.m_Prev = (elm)->field.m_Prev;               \
	else                                                                       \
	(head)->m_Last = (elm)->field.m_Prev;                                  \
	*(elm)->field.m_Prev = (elm)->field.m_Next;                                \
} while (0)


#ifdef __cplusplus
}
#endif


#endif