#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#define total_seats 140
using namespace std;
struct node
{
    int info;
    struct node *next;
};

//Class Declaration
class single_llist
{
public:
    node* create_node(int);
    void insert_begin(int);
    void delete_pos(int,int);
    void display(int);
    
};

struct TrieNode
{
    struct TrieNode *children[26];
    bool isEndOfWord;
    struct node **hall;
}*root;

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
    
    pNode->isEndOfWord = false;
    
    for (int i = 0; i < 26; i++)
        pNode->children[i] = NULL;
    
    return pNode;
}

void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    int index;
    for (int i = 0; i < key.length(); i++)
    {
        index = key[i] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        
        pCrawl = pCrawl->children[index];
    }
    
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    struct node *master = new node[10];
    pCrawl->hall=&master;
}

struct node ** search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
        {
            return NULL;
        }
        
        pCrawl = pCrawl->children[index];
    }
    
    if(pCrawl != NULL && pCrawl->isEndOfWord==true)
        return (pCrawl->hall);
    else
        return NULL;
}

// node declaration for the linked list of seats
// each node stores security code of the seat
void hall(string);
void admin(void);
void customer(string);
void cancel(void);
int search_sec(int);
void searchcinema(void);
void listcinema(void);

single_llist sl;            // class object for the linked list declared


/*parameters for the seating arrangement defined */

#define rows 10
#define columns 14
int dummy;
int row2,col2,z,i,j;
int menu ();
void chart ();
const char FULL = 'B',EMPTY = '.';
char arran[rows][columns];
char now_showing[]="yet to be added",show_time[]="yet to be added ",*housefull []={"filling fast "};
int total = 0,rem = 140,bkd = 0,sta=1;
int price[rows];
int cost,ans;            // IMP: an array of structure pointers declared - meaning an array is declared where
struct node *master[10];
struct node **pointer;//each element is a head node of a single linked list representing that row

int main(int argc, char** argv)
{
    int choice;
    root=getNode();
    char list[20][20]={"SRS","GSC","TGV","PVR","GALAXY"};
    string password;
    int p;
    int n=6;
    insert(root,"SRS");
    insert(root,"GSC");
    insert(root,"TGV");
    insert(root,"PVR");
    insert(root,"GALAXY");
    do
    {
        system("cls");
        cout<<"**************************************\n";
        cout<<"*      MOVIE SEAT BOOKING SYSTEM     *\n";
        cout<<"**************************************\n\n\n";
        cout<<"\nMAIN MENU\n";
        cout<<"\n1) Search for a cinema";
        cout<<"\n2) See list of cinemas";
        cout<<"\n3) Add a cinema(For authorized personnel only)";
        cout<<"\n4) Exit";
        cout<<"\nEnter choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                searchcinema();
                break;
            case 2:
                for(i=0;i<n;i++)
                    cout<<"\n"<<i+1<<") "<<list[i];
                break;
            case 3:
                cout<<"Enter password: ";
                
                for(int i=0;;i++)
                {
                    password[i]=getch();
                    cout<<"*";
                    p=password[i];
                    if(p==13)
                        break;
                }
                password[i]='\0';
                if(password=="hello")
                {
                    char name[20];
                    cout<<"\nAccess Granted\n";
                    cout<<"Enter the name of the cinema: ";
                    cin>>name;
                    toupper(name);
                    insert(root,name);
                    for(i=0;name[i]!='\0';i++)
                        list[n-1][i]=name[i];
                    list[n-1][i]='\0';
                    n++;
                    cout<<"\nNew Cinema Added\n";
                }
                else
                {
                    cout<<"\nAccess Denied\n";
                }
                break;
            case 4:
                cout<<endl<<"..exiting the program ..";
                exit(0);
                break;
            default:
                cout<<"\nerror:wrong input"<<endl<<"\tenter correct value ";
                
        }
        getch();
    }while(choice!=4);
}


void hall(string c)
{
    int i1,j1;
    //head node of each linked list initialised to NULL
    for(z=0;z<10;z++)
    {
        master[z]=NULL;
    }
    
    //initialising the security codes
    int array_security[total_seats],p=0;
    
    for(i1=1;i1<=10;i1++)
    {
        for(j1=1;j1<=14;j1++)
        {
            array_security[p]=(i1*100)+(j1);
            p++;
        }
        
    }
    
    // for setting the '.' symbol to empty seats
    
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
            arran[i][j] = EMPTY;
    }
    int choose1;
    do
    {
        system("cls");
        cout<<"**************************************\n";
        cout<<"*               WELCOME              *\n";
        cout<<"**************************************\n\n\n";
        
        
        cout<<"\nMAIN MENU\n";
        cout<<"\n1) Log in as Admin";
        cout<<"\n2) Login in as Customer";
        cout<<"\n3) Search for another cinema";
        cout<<"\nEnter choice: ";
        cin>>choose1;
        
        switch(choose1)
        {
            case 1:
                admin();
                break;
                
            case 2:
                customer(c);
                break;
                
            case 3:
                break;
                
            default:
                cout<<"\nerror:wrong input"<<endl<<"\tenter correct value ";
                getch();
        }
        
    }while(choose1!=3);
    
}



//********************function definitions ************************************************************



void admin()
{
    int cho_admin;
    do
    {
        system("cls");
        cout<<"\n---------------------------------------------------------";
        cout<<"\n---------------------------------------------------------";
        cout<<"\nWELCOME ADMINSTRATOR";
        cout<<"\nwarning:be careful with the admin settings";
        cout<<endl<<endl;
        cout<<endl<<"1) Adding/modifying the prices of the seats ";
        cout<<endl<<"2) Display the security codes of the seats ";
        cout<<endl<<"3) Change the movie details displayed to the customer ";
        cout<<endl<<"4) Declaring HOUSEFULL";
        cout<<endl<<"5) Display the number of tickets sold";
        cout<<endl<<"6) Return to the main menu";
        cout<<"\nEnter choice: ";
        cin>>cho_admin;
        switch(cho_admin)
        {
            case 1:
                cout<<endl;
                cout<<"\nSET THE PRICES FOR THE TICKETS\n";
                for (i = 0; i < rows; i++)
                {
                    
                    cout<<"Please enter the price for row "<<(i + 1);
                    if(i<4)
                        cout<<"\nGOLD CLASS ROW  ";
                    else
                        cout<<"\nREGULAR CLASS ROW ";
                    cin>>price [i];
                }
                cout<<"\nPrices Set\n";
                break;
                
            case 2:
                cout<<endl;
                cout<<"\nadministrator priviledge:\n";
                for(row2=0;row2<10;row2++)
                {
                    sl.display(row2);
                }
                break;
                
            case 3:
                cout<<"\nEnter the movie details";
                cout<<endl<<"Designate the movie NOW SHOWING"<<endl;
                cin>>now_showing;
                cout<<endl<<"Enter the show time "<<endl;
                cin>>show_time;
                break;
                
            case 4:
                char yes;
                cout<<"\nDo you want to declare house full?(y/n)";
                cin>>yes;
                if(yes=='y')
                {
                    *housefull="HOUSEFULL:no more tickets available";
                }
                
                break;
                
            case 5:
                cout<<"\nTotal ticket sales: "<<bkd;
                break;
                
            case 6:
                cout<<"...returning to main menu ..."<<endl<<endl;
                break;
                
            default:
                cout<<"\nerror:wrong input"<<endl<<"\tenter correct value ";
                break;
                
        }
        getch();
    }while(cho_admin!=6);
    
}


void customer(string c)
{
    
    int cho_customer;
    do
    {
        system("cls");
        cout<<endl<<endl;
        cout<<"\n----------------------------------------------";
        cout<<"\nWelcome to "<<c<<" cinemas: an experience like no other ";
        cout<<"\n----------------------------------------------";
        cout<<"\nMAIN MENU\n";
        cout<<"\n1) Show movie details ";
        cout<<"\n2) Show the ticket prices ";
        cout<<"\n3) Show available seats ";
        cout<<"\n4) Book your seat ";
        cout<<"\n5) Cancel your booking ";
        cout<<"\n6) Return to main menu";
        cout<<"\nEnter choice: ";
        cin>>cho_customer;
        
        
        switch(cho_customer)
        {
            case 1:
                cout<<endl<<"Currently showing movie "<<now_showing;
                cout<<endl<<"The show time is "<<show_time;
                break;
                
            case 2:
                cout<<"\nShow seat prices\n\n";
                
                for (i= 0; i< rows;i++)
                {
                    cout<<"\nThe price for row "<<(i+ 1);
                    if(i<4)
                        cout<<"\nGOLD CLASS ROW";
                    else
                        cout<<"\nREGULAR CLASS ROW ";
                    
                    cout<<"\n"<<price[i];
                }
                break;
                
            case 3:
                cout<<"\nView Available Seats\n\n";
                cout<<"\nSeats Status\n "<<*housefull<<endl<<endl;
                chart();
                break;
                
            case 4:
                cout<<"\n...........................................\n";
                cout<<"\nPURCHASE A TICKET";
                do
                {
                    int input_row,input_column;
                    cout<<"\nPlease select the row you would like to sit in: ";
                    cin>>row2;
                    input_row=row2;
                    
                    cout<<"\nPlease select the seat column you would like to sit in: ";
                    cin>>col2;
                    input_column=col2;
                    
                    row2--;col2--;
                    if (arran[row2][col2] == 'B')
                    {
                        cout<<"\nSeat is sold-out\nPlease select a new seat."<<endl;
                    }
                    else
                    {
                        cost = price [row2] + 0;
                        total = total + cost;
                        cout<<"\nThat ticket costs: "<<cost;
                        cout<<"\nConfirm Purchase? Enter (1 = YES / 0 = NO)"<<endl;
                        cin>>ans;
                        rem=rem-ans;
                        bkd=bkd+ans;
                        
                        
                        
                        if (ans== 1)
                        {
                            cout<<"\nYour ticket purchase has been confirmed."<<endl;
                            arran [row2][col2] = FULL;
                            cout<<endl<<row2;
                            sl.insert_begin(row2);
                        }
                        else if (ans== 0)
                        {
                            cout<<"\nWould you like to look at another seat? (1 = YES / 2 = NO)";
                            cin>>sta;
                        }
                        
                        cout<<"\nWould you like to look at another seat?(1 = YES / 2 = NO)";
                        cin>>sta;
                    }
                }
                while (sta == 1);
                break;
                
            case 5:
                cout<<"\n\n...cancellation of booking selected ...";
                cancel();
                break;
                
            case 6:
                cout<<"\n\n...returning to main menu ...\n\n";
                break;
                
            default:
                cout<<"\nerror:wrong input"<<endl<<"\tenter correct value ";
                break;
        }
        getch();
    }while(cho_customer!=6);
    
}

// search function: for finding the security code (linear search)
int search_sec(int sec)
{
    int array_security[total_seats];
    int state=0,i;
    for(i=0;i<140;i++)
    {
        if(array_security[i]==sec)
            state=1;
    }
    
    if(state==1)
        return 1;
    else
        return 0;
}

void searchcinema()
{
    string c;
    cout<<"Enter the name of the cinema: ";
    cin>>c;
    pointer=search(root,c);
    if(pointer==NULL)
    {
        cout<<"Cinema not found\n";
    }
    else
    {
        for(i=0;i<10;i++)
            master[i]=*(pointer+((sizeof(struct node *))*i));
        hall(c);
    }
}

void cancel()
{
    int can,sec,can2,can3;
    char canc2='n';
    
    do
    {
        cout<<endl<<"..Please enter the row of your seat.. ";
        cin>>can;
        cout<<endl<<"Please enter the security code "<<"\n which you received during the booking of your seat ";
        cin>>sec;
        
        can2=sec-(can*100);
        
        can--;can2--;
        
        if(search_sec(sec)==1)
        {
            cout<<endl<<"...security code matched..... "<<endl;
            cout<<endl<<"..... cancellation in progress ...."<<endl;
            arran [can][can2] = EMPTY;
            
            sl.delete_pos(can,sec);
        }
        else
            cout<<endl<<"no such security code found "<<endl<<"recheck the code entered ";
        cout<<endl;
        cout<<"Do you want to cancel another seat ?(y/n)"<<endl;
        cin>>canc2;
    }while(canc2=='y');
    
    
}


void chart ()
{
    
    cout<<"\n\tSeats";
    cout<<"\n\t    1    2    3    4    5    6    7    8    9    10   11   12   13   14 \n";
    int i,j;
    for (i= 0;i< 10;i++)
    {
        printf("\nRow %d\t",i+1);
        for (j= 0;j< 14;j++)
        {
            printf("    %c",arran[i][j]);
        }
    }
    printf("\n\n--------------------------------------------------------------------------------");
    printf("\n\t\t                      screen this way ");
}




//****************************
//linked list function defined
int choice, nodes, element, position;


//Creating Node

node *single_llist::create_node(int value)
{
    struct node *temp, *s;
    temp = new(struct node);
    if (temp == NULL)
    {
        cout<<"Memory not allocated "<<endl;
        return 0;
    }
    else
    {
        temp->info = value;
        temp->next = NULL;
        return temp;
    }
}

/*
 * Inserting element in beginning
 */
void single_llist::insert_begin(int)
{
    
    int val;
    val=((row2+1)*100+(col2+1));            //generates security code
    struct node *temp, *p;
    
    temp = create_node(val);
    if (master[row2] == NULL)
    {
        master[row2] = temp;
        master[row2]->next = NULL;
    }
    else
    {
        p = master[row2];
        master[row2] = temp;
        master[row2]->next = p;
    }
    
    cout<<"\n...ticket booking in process ....\n"<<endl<<endl;
    cout<<"your security code for the booked ticket is "<<endl<<val<<"\nplease remember it for future reference ";
    
    //sorting the linked list : to allow the row order to be maintained in linked list
    
    struct node *ptr, *s;
    if (master[row2] == NULL)
    {
        cout<<"NO BOOKINGS MADE YET"<<endl;
        return;
    }
    
    ptr = master[row2];
    while (ptr != NULL)
    {
        for (s = ptr->next;s !=NULL;s = s->next)
        {
            if (ptr->info > s->info)
            {
                val = ptr->info;
                ptr->info = s->info;
                s->info = val;
            }
        }
        ptr = ptr->next;
    }
}


//deleting a seat code
void single_llist::delete_pos(int can,int can2)
{
    int i, counter = 0;
    if (master[can] == NULL)
    {
        cout<<"NO BOOKINGS MADE YET"<<endl;
        return;
    }
    
    struct node *s, *ptr,*del;
    
    s = master[can];
    /*if (can2 == 1)
     {
     master[can] = s->next;
     }
     else
     {*/
    do
    {
        
        counter++;
        if(s->info==can2)
        {
            del=s;
            break;
        }
        s = s->next;
        
        
    }while (s != NULL);
    
    
    s = master[can];
    if(counter==1)
    {
        master[can]=s->next;
    }
    else
    {
        for (i = 1;i < counter;i++)
        {
            ptr = s;
            s = s->next;
        }
        ptr->next = s->next;
        
    }
    free(s);
    cout<<"cancellation successful"<<endl;
    
}

//displaying the security code in each node of linked list

void single_llist::display(int)
{
    struct node *temp;
    if (master[row2] == NULL)
    {
        cout<<"NO BOOKINGS MADE YET"<<endl;
        return;
    }
    temp = master[row2];
    cout<<"GENERATED SECURITY CODES: "<<endl;
    while (temp != NULL)
    {
        cout<<temp->info<<"->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}
