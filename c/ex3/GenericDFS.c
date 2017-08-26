/*
 * implement with DFS
 */
pNode getBest(pNode head, getNodeChildrenFunc getChildren, \
             getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)
{
    /* head */
    pNode* childs;
    unsigned num_of_childs = getChildren(head, childs);
    /* node */
    pNode node = NULL;
    unsigned int node_val;
    /* best */
    pNode* best = NULL;
    unsigned int best_p_node_val = 0;

    int i;
    for( i = 0; i < num_of_childs; i++)
    {
        node = getBest(head[i], getChildren, getVal, freeNode, copy, best);
        node_val = node ? getVal(node) : 0;

        if(node_val == best)
        {
            best = node;
            i++;
            break;
        }
        else if(node_val > best_p_node_val)
        {
            freeNode(best);
            best = node;
            best_p_node_val = node_val;
        }
        else
        {
            freeNode(node);
        }
    }

    if(getVal(head) == best)
    {
        freeNode(best);
        best = head;
    }

    // free rest of children if broke mid-way
    for (; i < num_of_childs ; ++i)
    {
        freeNode(childs[i]);
    }
    free(childs);

    return best;
}