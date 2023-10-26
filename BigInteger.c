// #include<stdio.h>
// #include<stdlib.h>

// struct BigInteger{
//     char sign;
//     int length;
//     struct node *head;
// };

// struct node{
//     int digit;
//     struct node *next;
// };

// struct BigInteger initialize(char *);
// struct BigInteger add(struct BigInteger,struct BigInteger);
// struct BigInteger sub(struct BigInteger ,struct BigInteger);
// struct BigInteger mul(struct BigInteger,struct BigInteger);
// struct BigInteger div1(struct BigInteger,struct BigInteger);
// struct BigInteger mod(struct BigInteger,struct BigInteger);

// int  zero(struct BigInteger,struct node *);
// void trav(struct node *);
// void display(struct BigInteger);

// // int main(){

//     struct BigInteger a,b,c;
//     a=initialize("31");
//     b=initialize("15");

//     display(a);
//     printf("\nlen=%d\n\n",a.length);
//     display(b);
//     printf("\nlen=%d\n\n",b.length);

//     c=mod(a,b);
//     display(c);
//     printf("\nlen=%d\n\n",c.length);

//     display(a);
//     printf("\n");
//     display(b);
//     printf("\n");

//     return 0;
// }



#include "BigInteger.h"

struct BigInteger initialize(char *c){
    int i=0;
    struct BigInteger new ;
    new.head=NULL;
    new.sign='+';
    new.length=0;
    if(c[0]=='\0'){
        // node *temp=(node *)malloc(sizeof(node));
        // temp->digit=0;
        // temp->next=new->head;
        // new->head=temp;

        return new;
    }
    if(c[0]=='-'){
        new.sign='-';;
        i++;
    }
    if(c[0]=='+')
        i++;
    while(c[i]=='0')
        i++;
    for(;c[i]!='\0';i++)
    {
        if((c[i]<'0')&&(c[i]>9)){
            return new;
        }
        struct node *temp=(struct node *)malloc(sizeof(struct node));
        temp->digit=c[i]-'0';
        temp->next=new.head;
        new.head=temp;
        new.length++;
    }
    if(!new.head){
        struct node *temp=(struct node *)malloc(sizeof(struct node));
        temp->digit=0;
        temp->next=new.head;
        new.head=temp;
        new.length++;
    }
    return new;
}
void display(struct BigInteger num)
{
    if(num.head  && num.sign=='-')
        printf("-");
    if(num.head)
        trav(num.head);
    //   else
        //   printf(":");
}
void trav(struct node * head){
    if(head->next)
        trav(head->next);
    printf("%d",head->digit);
}

int zero(struct BigInteger num,struct node *n){
    if(!n)
        return 0;
    if(zero(num,n->next))
        return 1;
    else{
        if(n->next)
            free(n->next);
        n->next=NULL;
        return n->digit;
    }

}


void freell(struct node * head)
{
    if(head->next)
        freell(head->next);
    free(head);
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    

    int carry = 0, s;
     
    struct BigInteger sum;
    sum.head = NULL;
    sum.length=0;
    sum.sign='+';
    if(!a.head || !b.head)
        return sum;

    if((a.sign!='-')&&(b.sign=='-')){
        b.sign='+';
        sum = sub(a,b);
        b.sign='-';
        return sum;
    }
    if((a.sign=='-')&&(b.sign!='-')){
        a.sign='+';
        sum = sub(b,a);
        a.sign='-';
        return sum;
    }

    
    
    struct node * itr1 = a.head, * itr2 = b.head, * itr3 = NULL ;

    while (itr1 || itr2 || carry) {
        struct node * temp = (struct node*)malloc(sizeof(struct node));
        s = carry;

        if(itr1){
            s += itr1->digit;
            itr1 = itr1->next;
        }
        if(itr2){
            s += itr2->digit;
            itr2 = itr2->next;
        }

        carry = s / 10;
        temp->digit = s % 10;
        temp->next = NULL;

        if (!sum.head) {
            sum.head = temp;
            itr3 = temp;
        }else{
            itr3->next = temp;
            itr3 = temp;
        }
    }
    if((a.sign=='-')&&(b.sign=='-'))
        sum.sign='-';

    zero(sum,sum.head);
    
    struct node  * itr4=sum.head;
    while(itr4){
        sum.length++;
        itr4=itr4->next;
    }

    // if(!zero(sum,sum->head)){
    //     free(sum->head);
    //     sum->head=NULL;
    // }
    return sum;
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
    int borrow=0,d;

    struct BigInteger dif;
    dif.head=NULL;
    dif.length=0;
    dif.sign='+';
    if(!a.head || !b.head)
        return dif;

    if((a.sign!='-')&&(b.sign=='-')){
        b.sign='+';
        dif=add(a,b);
        b.sign='-';
        return dif;
    }
    if((a.sign=='-')&&(b.sign!='-')){
        b.sign='-';
        dif=add(a,b);
        b.sign='+';
        return dif;
    }
    if((a.sign=='-')&&(b.sign=='-')){
        b.sign='+';
        a.sign='+';
        dif=sub(a,b);
        b.sign='-';
        a.sign='-';
        return dif;
    }

    
    struct node * itr1 = a.head, *itr2 = b.head, *itr3 = NULL;

    while (itr1) {
        struct node * temp = (struct node *)malloc(sizeof(struct node ));
        d = itr1->digit-borrow;
        itr1 = itr1->next;
        if (itr2) {
            d -= itr2->digit;
            itr2 = itr2->next;
        }
        if(d<0){
            borrow=1;
            d+=10;
        }
        else
            borrow=0;
        temp->digit = d;
        temp->next = NULL;

        if (!dif.head) {
            dif.head = temp;
            itr3 = temp;
        }else{
            itr3->next = temp;
            itr3 = temp;
        }
    }
    if(itr2||borrow){
        dif=sub(b,a);
        dif.sign='-';
    }

    zero(dif,dif.head);
    struct node  * itr4=dif.head;
    while(itr4){
        dif.length++;
        itr4=itr4->next;
    }

    // if(!zero(dif,dif->head)){
    //     free(dif->head);
    //     dif->head=NULL;
    // }
    return dif;
}


struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    
    struct BigInteger pro;
    pro.head = NULL;
    pro.sign='+';
    pro.length=0;

    if(!a.head || !b.head)
        return pro;

    struct BigInteger temp ;
    temp.head = NULL;
    temp.length=0;
    temp.sign='+';

    int shift = 0;
    struct node * itr1 = a.head;

    while (itr1) {

        

        temp.head = NULL;
        struct node * itr2 = b.head;
        int carry = 0;
        struct node * last = temp.head;

        while (itr2 || carry) {
            int product = carry;

            if (itr2) {
                product += itr1->digit * itr2->digit;
                itr2 = itr2->next;
            }

            carry = product / 10;
            product %= 10;

            struct node * tempnode=(struct node *)malloc(sizeof(struct node ));
            tempnode->digit=product;
            tempnode->next=NULL;

            if(!temp.head)
                temp.head=tempnode;
            else 
                last->next=tempnode;
            last=tempnode;
        }

        for (int i=0;i<shift;i++) {
            struct node * tempnode=(struct node *)malloc(sizeof(struct node ));
            tempnode->digit=0;
            tempnode->next=temp.head;
            temp.head=tempnode;
        }

        if(pro.head)
            pro=add(pro,temp);
        else 
            pro=temp;    
        shift++;

        itr1=itr1->next;
    }
    if((a.sign=='-')^(b.sign=='-'))
        pro.sign='-';
    
    zero(pro,pro.head);

    pro.length=0;
    struct node  * itr4=pro.head;
    while(itr4){
        pro.length++;
        itr4=itr4->next;
    }
    
    // if(!zero(pro,pro->head)){
    //     free(pro->head);
    //     pro->head=NULL;
    // }
    return pro;

}





struct BigInteger div1(struct BigInteger a,struct BigInteger b)
{

    struct BigInteger quo,dif;
    quo.head   = NULL;
    quo.sign   = '+';
    quo.length = 0;

    if(!a.head || ! b.head)
        return quo;

    if((b.length==1)&&(b.head->digit==0))
        return quo;

    if(((a.length==1)&&(a.head->digit==0)) || (a.length<b.length)){
        quo.head   = (struct node * )malloc(sizeof(struct node));
        quo.head->digit=0;
        quo.head->next=NULL;
        quo.length = 1;
        return quo;
    }
    int i=0,d,q=0;
    struct node *temp=NULL,*stop=b.head;
    d = a.length - b.length;

    while(i<d){
        temp=(struct node *)malloc(sizeof(struct node ));
        temp->digit  = 0 ;
        temp->next = b.head;
        b.head = temp;
        i++;
    }
    

    char asign=a.sign,bsign=b.sign;
    a.sign=b.sign='+';


    while(1){
        
        dif=sub(a,b);

        if(dif.sign =='-'){
            struct node  *t;
            if(b.head!=stop){
                t = b.head;
                b.head=b.head->next;
                free(t);
                d--;
                
                t=(struct node *)malloc(sizeof(struct node ));
                t->digit = q;
                t->next = quo.head;
                quo.head = t;
                quo.length++;
                q=0;
                
            }
            else{
                t=(struct node *)malloc(sizeof(struct node ));
                t->digit = q;
                t->next = quo.head;
                quo.head = t;
                quo.length++;
                q=0;
                
                a.sign=asign;
                b.sign=bsign;

                if((a.sign=='-')^(b.sign=='-'))
                    quo.sign='-';
                
                zero(quo,quo.head);

                quo.length=0;
                struct node  * itr4=quo.head;
                while(itr4){
                    quo.length++;
                    itr4=itr4->next;
                }


              
                return quo;
            }
        }
        else{
            q++;
            a=dif;

        }
    }    
}


struct BigInteger mod(struct BigInteger a,struct BigInteger b)
{
    
    struct BigInteger quo,dif;
    quo.head   = NULL;
    quo.sign   = '+';
    quo.length = 0;

    if(!a.head || ! b.head)
        return quo;

    if((b.length==1)&&(b.head->digit==0))
        return quo;

    if(((a.length==1)&&(a.head->digit==0)) ){
        quo.head   = (struct node * )malloc(sizeof(struct node));
        quo.head->digit=0;
        quo.head->next=NULL;
        quo.length = 1;
        return quo;
    }
    int i=0,d,q=0;
    struct node *temp=NULL,*stop=b.head;
    d = a.length - b.length;

    while(i<d){
        temp=(struct node *)malloc(sizeof(struct node ));
        temp->digit  = 0 ;
        temp->next = b.head;
        b.head = temp;
        i++;
    }
    

    char asign=a.sign,bsign=b.sign;
    a.sign=b.sign='+';


    while(1){
        
        dif=sub(a,b);

        if(dif.sign =='-'){
            struct node  *t;
            if(b.head!=stop){
                t = b.head;
                b.head=b.head->next;
                free(t);
                d--;
                
                t=(struct node *)malloc(sizeof(struct node ));
                t->digit = q;
                t->next = quo.head;
                quo.head = t;
                quo.length++;
                q=0;
                
            }
            else{
                t=(struct node *)malloc(sizeof(struct node ));
                t->digit = q;
                t->next = quo.head;
                quo.head = t;
                quo.length++;
                q=0;
                

                if(asign==bsign)
                    dif=add(dif,b);
                
                dif.sign=bsign;
                
                a.sign=asign;
                b.sign=bsign;     


                zero(dif,dif.head);
                dif.length=0;
                struct node  * itr4=dif.head;
                while(itr4){
                    dif.length++;
                    itr4=itr4->next;
                }


              
                return dif;
            }
        }
        else{
            q++;
            a=dif;

        }
    } 
}