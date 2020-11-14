#include <stdio.h>

typedef struct node {
   int value;
   struct node *next;
} node;

int cycle_length(node *head) {
   /* add your code here */
  if (head == NULL)
    return 0;

  node* p1 = head;
  node* p2 = head;
  int counter = 0;

  do {
    if (p1->next == NULL || p1->next->next == NULL)
      return 0;
    p1 = p1->next->next;
    p2 = p2->next;
    counter++;
  } while(p1 != p2);

   return counter;
}


/* do not modify this function */
int main(void) {
   int i;
   node nodes[25]; //enough to run our tests
   for(i=0; i < sizeof(nodes)/sizeof(node); i++) {
      nodes[i].value = 0;
      nodes[i].next = NULL;
   }
   nodes[0].next = &nodes[1];
   nodes[1].next = &nodes[2];
   nodes[2].next = &nodes[3];
   printf("Cycle_length: %d\n", cycle_length(&nodes[0]));

   nodes[4].next = &nodes[5];
   nodes[5].next = &nodes[6];
   nodes[6].next = &nodes[7];
   nodes[7].next = &nodes[8];
   nodes[8].next = &nodes[9];
   nodes[9].next = &nodes[10];
   nodes[10].next = &nodes[4];
   printf("Cycle_length: %d\n", cycle_length(&nodes[4]));

   nodes[11].next = &nodes[12];
   nodes[12].next = &nodes[13];
   nodes[13].next = &nodes[14];
   nodes[14].next = &nodes[15];
   nodes[15].next = &nodes[16];
   nodes[16].next = &nodes[17];
   nodes[17].next = &nodes[14];
   printf("Cycle_length: %d\n", cycle_length(&nodes[11]));

   nodes[18].next = &nodes[18];
   printf("Cycle_length: %d\n", cycle_length(&nodes[18]));

   nodes[19].next = &nodes[20];
   nodes[20].next = &nodes[21];
   nodes[21].next = &nodes[22];
   nodes[22].next = &nodes[23];
   printf("Cycle_length: %d\n", cycle_length(&nodes[19]));

   printf("Cycle_length: %d\n", cycle_length(NULL));
   return 0;
}

