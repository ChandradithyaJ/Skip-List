#include <iostream>
#include <cstdlib>
#include <limits.h>
using namespace std;

struct node{
    int val;
    struct node** next;
    int nps; // number of pointers in next
};

struct node* createNode(int num)
{
    struct node* n;
    n = malloc(sizeof(struct node));
    n->val = num;
    n->next = calloc(1, sizeof(struct node*));
    n->nps = 1;
    return n;
}

int h = 0;
struct node *ninf = createNode(INT_MIN); // - infinity
struct node *pinf = createNode(INT_MAX); // + infinity

void createSkipList()
{
    ninf->next[0] = pinf;
}

void insertElement(int num, int lvl, struct node* m)
{
    struct node* p = ninf;

    if(lvl > 0)
    {
        double y = ((1.0)*rand())/RAND_MAX;
        if(y <= 0.5) return;
    }

    if(lvl > h)
    {
        h++;
        ninf->next = realloc(ninf->next, ++ninf->nps);
        ninf->next[lvl] = pinf;
    }

    while(p->next[lvl]->val <= num){
        p = p->next[lvl];
    }
    if(!lvl) m = createNode(num);
    else
    {
        m->next = realloc(m->next, ++m->nps);
    }
    m->next[lvl] = p->next[lvl];
    p->next[lvl] = m;
    insertElement(num, lvl+1, m);
}

struct node* searchElement(int num)
{
    struct node *p = ninf;
    int k = p->nps - 1;

    while(k >= 0){
        while(p->next[k]->val <= num){
            p = p->next[k];
        }
        k--;
    }
    return p;
}

void deleteElement(int num)
{
    struct node* deleteNode = searchElement(num);
    if(deleteNode->val != num){
        cout << "Number entered doesn't exist in the skip list\n";
        return;
    }

    for(int lvl = 0; lvl <= h; lvl++){
        struct node* temp = ninf;
        while(temp->next[lvl] != deleteNode && temp->next[lvl] != pinf){
            temp = temp->next[lvl];
        }
        if(temp->next[lvl] == pinf) break;
        temp->next[lvl] = deleteNode->next[lvl];
        if(temp == ninf && temp->next[lvl] == pinf){
            if(lvl > 0){
                ninf->next = realloc(ninf->next, lvl-1);
                h = lvl-1;
            }
            else{
                ninf->next = realloc(ninf->next, lvl);
                h = lvl;
            }
        }
    }
    free(deleteNode);
}

void display()
{
    cout << "Skip List:\n";
    for(int i = 0; i <= h; i++){
        struct node* n;
        n = ninf->next[i];
        cout << "Level " << i << ": ";
        while(n->next[i] != NULL){
            cout << n->val << " ";
            n = n->next[i];
        }
        cout << endl;
    }
}

int main()
{
    const initial = 0;
    createSkipList();
    insertElement(3, initial, NULL);
    insertElement(2, initial, NULL);
    insertElement(0, initial, NULL);
    insertElement(-9, initial, NULL);
    insertElement(6, initial, NULL);
    insertElement(7, initial, NULL);
    insertElement(3, initial, NULL);
    insertElement(4, initial, NULL);
    insertElement(100, initial, NULL);
    insertElement(-59, initial, NULL);

    display();
    cout << endl;

    int x;
    cout << "Search for: ";
    cin >> x;
    if(searchElement(x)->val == x) cout << "Exists in the skip list\n\n";
    else cout << "Not in the skip list\n\n";
    display();

    cout << "\nDelete: ";
    cin >> x;
    deleteElement(x);
    display();

    return 0;
}
