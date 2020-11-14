#include <stdio.h>

#define RECURSIVE

/*
 * struct for list nodes
 * DO NOT MODIFY
 */
typedef struct node {
   const int value;
   struct node *next;
} node;


/*
 * If the linked list starting at the node pointed to by 'head' has a cycle,
 * remove the link that closes the cycle.  All nodes must remain reachable
 * from the head node.  Return value is a pointer to the head node, which
 * should not change.
 */
node* break_cycle(node *head)
{
   // TODO
  if (head == NULL)
    return head;

  node* p1 = head;
  node* p2 = head;
  node* p3 = head;
  int counter = 0;

  do {
    if (p1->next == NULL || p1->next->next == NULL)
      break;
    p1 = p1->next->next;
    p2 = p2->next;
    counter++;
  } while(p1 != p2);

  while (p3->next != p1)
    p3 = p3->next;
  p3 = NULL;

  return head;
}

/*
 * Given a pointer to the head node of an acyclic list, change the
 * next links such that the nodes are linked in reverse order.
 * Allocating new nodes or copying values from one node to another
 * is not allowed, but you may use additional pointer variables.
 * Return value is a pointer to the new head node.
 */
node* reverse(node *head)
{
   // TODO
  if (head == NULL || head->next == NULL)
    return head;

  node* p = head;
  node* p1 = head;
  node* p2 = head;
  node* p3 = p;

  while (p != NULL || p->next != NULL) {
    p2 = p->next;
    p1 = p->next->next;
    p->next->next = p;
    p->next = p1;
    p = p2;
  }

  head = p;
    

  /*int len = 1;
  while (p->next != NULL) {
    p = p->next;
    len++;
  }

  int arr[len];
  int i = 0;
  while (p1 != NULL) {
    arr[i] = p1->value;
    p1 = p1->next;
    i++;
  }

  for (int j = i; j >= 0; j--) {
    p2->value = arr[j];
    p2 = p2->next;
    }*/

  return head;
}

/*
 * Given a pointer to the head node of an acyclic list,
 * print the values stored in the nodes.
 * DO NOT MODIFY!
 */
void print_list(node *head)
{
   while( head )
   {
      printf( "%d%s", head->value, (head->next ? "->" : "") );
      head = head->next;
   }
   printf( "\n" );
   return;
}

/*
 * Main function with testcases for break_cycle() and reverse().
 * DO NOT MODIFY!
 */
/* do not modify this function */
int main(void) {
   node* head;
   node nodes[24] = { { 0,NULL}, { 1,NULL}, { 2,NULL}, { 3,NULL},
                      { 4,NULL}, { 5,NULL}, { 6,NULL}, { 7,NULL},
                      { 8,NULL}, { 9,NULL}, {10,NULL}, {11,NULL},
                      {12,NULL}, {13,NULL}, {14,NULL}, {15,NULL},
                      {16,NULL}, {17,NULL}, {18,NULL}, {19,NULL},
                      {20,NULL}, {21,NULL}, {22,NULL}, {23,NULL} }; //enough to run our tests

   nodes[0].next = &nodes[1];
   nodes[1].next = &nodes[2];
   nodes[2].next = &nodes[3];
   printf("reverse: ");
   print_list( head = reverse(break_cycle(&nodes[0])) );
   printf("reverse reverse: ");
   print_list( reverse(head) );

   nodes[4].next = &nodes[5];
   nodes[5].next = &nodes[6];
   nodes[6].next = &nodes[7];
   nodes[7].next = &nodes[8];
   nodes[8].next = &nodes[9];
   nodes[9].next = &nodes[10];
   nodes[10].next = &nodes[4];
   printf("reverse: ");
   print_list( head = reverse(break_cycle(&nodes[4])) );
   printf("reverse reverse: ");
   print_list( reverse(head) );

   nodes[11].next = &nodes[12];
   nodes[12].next = &nodes[13];
   nodes[13].next = &nodes[14];
   nodes[14].next = &nodes[15];
   nodes[15].next = &nodes[16];
   nodes[16].next = &nodes[17];
   nodes[17].next = &nodes[14];
   printf("reverse: ");
   print_list( head = reverse(break_cycle(&nodes[11])) );
   printf("reverse reverse: ");
   print_list( reverse(head) );

   nodes[18].next = &nodes[18];
   printf("reverse: ");
   print_list( head = reverse(break_cycle(&nodes[18])) );
   printf("reverse reverse: ");
   print_list( reverse(head) );

   nodes[19].next = &nodes[20];
   nodes[20].next = &nodes[21];
   nodes[21].next = &nodes[22];
   nodes[22].next = &nodes[23];
   printf("reverse: ");
   print_list( head = reverse(break_cycle(&nodes[19])) );
   printf("reverse reverse: ");
   print_list( reverse(head) );

   printf("reverse: ");
   print_list( head = reverse(break_cycle(NULL)) );
   printf("reverse reverse: ");
   print_list( reverse(head) );

   return 0;
}

