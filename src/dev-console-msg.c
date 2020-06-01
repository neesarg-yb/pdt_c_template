#include "dev-console-msg.h"
#include "game-resources.h"

struct MessageLinkedList
{
    // data
    char *m_value;

    // next
    struct MessageLinkedList *m_next;
}; 
typedef struct MessageLinkedList MessageLinkedList;

void InitalizeMessageLinkedList(MessageLinkedList **ll)
{
    MessageLinkedList *newLL = g_pd->system->realloc(NULL, sizeof(MessageLinkedList));
    newLL->m_value = NULL;
    newLL->m_next  = NULL;
    
    *ll = newLL;
}

void InitalizeMessageLinkedListNode(MessageLinkedList *ll, char const *msg)
{
    if(ll == NULL)
        return;

    // Traverse to the end of linked list
    MessageLinkedList *currNode;
    for(currNode = ll; currNode->m_next != NULL; currNode = currNode->m_next) 
    {}

    // Set value
    g_pd->system->formatString(&(currNode->m_value), msg);

    // Set next
    {
        // Create a new node with valid data
        MessageLinkedList *newNode = g_pd->system->realloc(NULL, sizeof(MessageLinkedList));
        newNode->m_value = NULL;
        newNode->m_next  = NULL;

        currNode->m_next = newNode;
    }
}

MessageLinkedList *m_msgLinkedList = NULL;

void DevConsoleMessagesClearAll(void)
{
    MessageLinkedList *ll = m_msgLinkedList;
    while(ll != NULL)
    {
        MessageLinkedList *nextNode = ll->m_next;

        g_pd->system->realloc(ll->m_value, 0);
        g_pd->system->realloc(ll, 0);

        ll = nextNode;
    }
}

void DevConsoleMessagesPush(char const *msg)
{
    if(m_msgLinkedList == NULL)
        InitalizeMessageLinkedList(&m_msgLinkedList);
    
    InitalizeMessageLinkedListNode(m_msgLinkedList, msg);
}

int GetDevConsoleMessagesCount(void)
{
    int i = 0;
    MessageLinkedList *ll;
    for(ll = m_msgLinkedList; ll != NULL; ll = ll->m_next)
    {
        if(ll->m_value != NULL)
            i++;
        // Otherwise we never used this node
    }

    return i;
}

char const* GetDevConsoleMessage(int idx)
{
    int i;
    MessageLinkedList *ll;
    for(ll = m_msgLinkedList, i = 0; ll != NULL; ll = ll->m_next, i++)
    {
        if(i == idx)
        {
            if(ll->m_value != NULL)
                return ll->m_value;
            else
                g_pd->system->error("GetDevConsoleMessage: NULL at index %d", idx);
        }
    }

    return "ConsoleMessage NOT FOUND";
}