#include "GenericDFS.h"
#include <stdlib.h>

/**
 * Documentation in header file
 */
pNode getBest(pNode head, getNodeChildrenFunc getChildren,
              getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)
{
    if(head == NULL)
    {
        return NULL;
    }

    //todo: recover to best
    if(getVal(head) == best)
    {
        return head;
    }

    /* head */
    pNode* childs;
    int num_of_childs = getChildren(head, &childs);
    /* node */
    pNode node = NULL;
    unsigned int node_val;
    /* best */
    pNode* bestNode = NULL;
    unsigned int best_p_node_val = 0;

    int i;
    for( i = 0; i < num_of_childs; i++)
    {
        node = getBest(childs[i], getChildren, getVal, freeNode, copy, best);
        node_val = node ? getVal(node) : 0;

        if(node_val == best)
        {
            bestNode = node;
            i++;
            break;
        }
        else if(node_val > best_p_node_val)
        {
            freeNode(bestNode);
            bestNode = node;
            best_p_node_val = node_val;
        }
        else
        {
            freeNode(node);
        }
    }

    // free rest of children if broke mid-way
    for (; i < num_of_childs ; ++i)
    {
        freeNode(childs[i]);
    }
    free(childs);

    return bestNode;
}