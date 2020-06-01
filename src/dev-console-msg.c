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

void InitalizeMessageLinkedListNode(MessageLinkedList **ll)
{
    if(*ll != NULL)
        g_pd->system->error("InitalizeMessageLinkedListNode: passed ll is NOT NULL!");

    MessageLinkedList *newLL = g_pd->system->realloc(NULL, sizeof(MessageLinkedList));
    newLL->m_value = NULL;
    newLL->m_next  = NULL;
    
    *ll = newLL;
}

MessageLinkedList *m_msgLinkedList = NULL;

void DevConsoleMessagesPush(char const *msg, int maxNumMsg)
{
    if(maxNumMsg <= 0)
        g_pd->system->error("DevConsoleMessagesPush: can not pass maxNumMsg <= 0");

    // Traverse to the end of linked list
    int currMsgIdx;
    MessageLinkedList **tailNodeRef;
    for( tailNodeRef  = &m_msgLinkedList, currMsgIdx = 1; 
        *tailNodeRef != NULL; 
         tailNodeRef  = &((*tailNodeRef)->m_next), currMsgIdx++ ) 
    {
        if(currMsgIdx >= maxNumMsg)
        {
            // We need to remove first message in order to make space
            MessageLinkedList *firstMsgNode = m_msgLinkedList;
            m_msgLinkedList = m_msgLinkedList->m_next;

            g_pd->system->realloc(firstMsgNode->m_value, 0);
            g_pd->system->realloc(firstMsgNode, 0);
        }
    }

    // Initalize the tail of linked list
    InitalizeMessageLinkedListNode(tailNodeRef);    // == currentEndNode->m_next

    // Fill up the m_value
    g_pd->system->formatString(&((*tailNodeRef)->m_value), msg);
}

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