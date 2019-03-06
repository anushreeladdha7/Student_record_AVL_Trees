#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct avl_tree
{
	int rno;
	char *name;
	char sub_code[6];
	int marks;
	char dept[3];
	int sem;
	struct avl_tree *left;
	struct avl_tree *right;
	int height;
}node;

typedef struct avl_node 
{
	node *n;
	struct avl_node *next;
}avl_nodes;

typedef struct topper_tag
{
	int rno;
	char *name;
	int total_marks;
	char *dept;
	int sem;
	struct topper_tag *next;
	
}topper_node;

node* newNode(int rno,char *name,char sub_code[],int marks,char dept[],int sem)
{
    node* n = (node*)malloc(sizeof(node));
    n->rno=rno;
    n->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(n->name,name);
    strcpy(n->sub_code,sub_code);
    n->marks=marks;
    strcpy(n->dept,dept);
    n->sem=sem;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;         // new node is initially added at leaf
    return(n);
}

int height(node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

node *rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 

node *leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}


node* insert(node *root,int rno,char *name,char sub_code[],int marks,char dept[],int sem)
{
	/* 1.  Perform the normal BST insertion */
    if (root == NULL)
        return(newNode(rno,name,sub_code,marks,dept,sem));
 
    if (rno < root->rno)
        root->left  = insert(root->left, rno,name,sub_code,marks,dept,sem);
    else if (rno > root->rno)
        root->right = insert(root->right,rno,name,sub_code,marks,dept,sem);
    else // Equal keys are not allowed in BST
       {
       	if(strcmp(sub_code,root->sub_code)<0)
       		root->left  = insert(root->left,rno,name,sub_code,marks,dept,sem);
		else if(strcmp(sub_code,root->sub_code)>0)
			root->right = insert(root->right,rno,name,sub_code,marks,dept,sem);
		else
		{
			root->rno=rno;
       		root->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
       		strcpy(root->name,name);
       		strcpy(root->sub_code,sub_code);
       		root->marks=marks;
       		strcpy(root->dept,dept);
       		root->sem=sem;
       		return root;
		}
       	
	   } 
 
    /* 2. Update height of this ancestor node */
    root->height = 1 + max(height(root->left), height(root->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && rno < root->left->rno)
        return rightRotate(root);
 
    // Right Right Case
    if (balance < -1 && rno > root->right->rno)
        return leftRotate(root);
 
    // Left Right Case
    if (balance > 1 && rno > root->left->rno)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Left Case
    if (balance < -1 && rno < root->right->rno)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    /* return the (unchanged) node pointer */
    return root;	
}

node* insert_sub(node *root,int rno,char *name,char sub_code[],int marks,char dept[],int sem)
{
	/* 1.  Perform the normal BST insertion */
    if (root == NULL)
        return(newNode(rno,name,sub_code,marks,dept,sem));
 
    if(strcmp(sub_code,root->sub_code)<0)
        root->left  = insert_sub(root->left, rno,name,sub_code,marks,dept,sem);
  
    else if(strcmp(sub_code,root->sub_code)>0)
        root->right =insert_sub(root->right,rno,name,sub_code,marks,dept,sem);
    else 
       {
       	if (rno < root->rno)
       		root->left  = insert_sub(root->left,rno,name,sub_code,marks,dept,sem);
		else if (rno > root->rno)
			root->right =insert_sub(root->right,rno,name,sub_code,marks,dept,sem);
		else
		{
			root->rno=rno;
       		root->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
       		strcpy(root->name,name);
       		strcpy(root->sub_code,sub_code);
       		root->marks=marks;
       		strcpy(root->dept,dept);
       		root->sem=sem;
       		return root;
		}
       	
	   } 
 
    /* 2. Update height of this ancestor node */
    root->height = 1 + max(height(root->left),height(root->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && (strcmp(sub_code,root->left->sub_code)<0))
        return rightRotate(root);
 
    // Right Right Case
    if (balance < -1 && (strcmp(sub_code,root->right->sub_code)>0))
        return leftRotate(root);
 
    // Left Right Case
    if (balance > 1 && (strcmp(sub_code,root->left->sub_code)>0))
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Left Case
    if (balance < -1 && (strcmp(sub_code,root->right->sub_code)<0))
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    /* return the (unchanged) node pointer */
    return root;	
}

node* delete_root(node* root)
{
	node *r,*q,*tmp;
	r=NULL;
	for(q=root->left;q->right!=NULL; )
	{
		r=q;
		q=q->right;
	}
	if(r==NULL)
	{
		q=root->left;
		q->right=root->right;
	}
	else
	{
		r->right=q->left;
	 	q->left=root->left;
		q->right=root->right;
	}
	
	tmp=root;
	root=q;
	free(tmp);
	return root;
}
node* deleteNode(node* root, int rno,char *sub_code)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    if ( rno < root->rno )
        root->left = deleteNode(root->left, rno, sub_code);
 
    else if( rno > root->rno )
        root->right = deleteNode(root->right, rno,sub_code);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
    	if(strcmp(sub_code,root->sub_code)<0)
    		root->left = deleteNode(root->left, rno, sub_code);
    		
    	else if(strcmp(sub_code,root->sub_code)>0)
    		root->right = deleteNode(root->right, rno,sub_code);
        // node with only one child or no child
        else
        {
		
        if( (root->left == NULL) || (root->right == NULL) )
        {
            node *temp = root->left ? root->left :root->right;     //root node to be deleted
 			node *tmp;
            // No child case
            if (temp == NULL)
            {
                tmp = root;
                root = NULL;
            }
            else // One child case
            {
            	tmp=root;
				root=temp;	
            }
            free(tmp);
        }
        else
        {
            root=delete_root(root);
        }
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

node* deleteNode_sub(node* root, int rno,char *sub_code)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    
    if(strcmp(sub_code,root->sub_code)<0)
        root->left = deleteNode_sub(root->left, rno, sub_code);
 
    
    else if(strcmp(sub_code,root->sub_code)>0)
        root->right = deleteNode_sub(root->right, rno,sub_code);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
    	if ( rno < root->rno )
    		root->left = deleteNode_sub(root->left, rno, sub_code);
    		
    	else if( rno > root->rno )
    		root->right = deleteNode_sub(root->right, rno,sub_code);
        // node with only one child or no child
        else
        {
		
        if( (root->left == NULL) || (root->right == NULL) )
        {
            node *temp = root->left ? root->left :root->right;     //root node to be deleted
 			node *tmp;
            // No child case
            if (temp == NULL)
            {
                tmp = root;
                root = NULL;
            }
            else // One child case
            {
            	tmp=root;
				root=temp;	
            }
            free(tmp);
        }
        else
        {
            root=delete_root(root);
        }
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
int getrecord(node *root)
{
	if(root==NULL)
		return 0;
	else
		return(1+getrecord(root->left)+getrecord(root->right));
}
void visit(node *root)
{
	printf("\n\n");
	printf("\n\tRoll No.:%d",root->rno);
	printf("\n\tName:%s",root->name);
	printf("\n\tSubject Code:%s",root->sub_code);
	printf("\n\tMarks:%d",root->marks);
	printf("\n\tDeptartment:%s",root->dept);
	printf("\n\tSemester:%d",root->sem);
	printf("\n\tHeight:%d",root->height);
}

void search(node* root,int rno,char *sub_code)
{
	if (root == NULL)
        return ;
 
    if ( rno < root->rno )
        search(root->left, rno, sub_code);
 
    else if( rno > root->rno )
        search(root->right, rno,sub_code);
 
    else
    {
    	if(strcmp(sub_code,root->sub_code)<0)
    		search(root->left, rno, sub_code);
    		
    	else if(strcmp(sub_code,root->sub_code)>0)
    		search(root->right, rno,sub_code);
        // node with only one child or no child
        else
		{
			visit(root);
		}	
    }
}

void rangesearch(node *root,int a,int b)
{
	if(root==NULL)
		return ;
	if(a<root->rno)
		rangesearch(root->left,a,b);
	if(a<=root->rno && root->rno<=b)
		visit(root);
	if(b>root->rno)
		rangesearch(root->right,a,b);
}


void inOrder(node *root)
{
    if(root != NULL)
    {    
        visit(root);
        inOrder(root->left);
        inOrder(root->right);
    }
}


void getmax(node *root,char *sub_code,int *max,avl_nodes **head)
{
	if(root==NULL)
		return ;
		
	if(strcmp(sub_code,root->sub_code)<0)
		getmax(root->left,sub_code,max,head);
    else if(strcmp(sub_code,root->sub_code)>0)
    	getmax(root->right,sub_code,max,head);
    else
    {
    	avl_nodes *ptr;
    	if(*max==root->marks)
    	{
    		ptr=(avl_nodes*)malloc(sizeof(avl_nodes));
    		ptr->n=root;
    		ptr->next=*head;
    		*head=ptr;
    	}
    	else if(*max<root->marks)
    	{
    		ptr=*head;
    		avl_nodes *prev=NULL;
    		while(ptr!=NULL)
    		{
    			prev=ptr;
    			ptr=ptr->next;
    			free(prev);
			}
			ptr=(avl_nodes*)malloc(sizeof(avl_nodes));
    		ptr->n=root;
    		ptr->next=NULL;
    		*head=ptr;
    		*max=root->marks;
		}
		getmax(root->left,sub_code,max,head);
		getmax(root->right,sub_code,max,head);
	}
}

void print_avl_list(avl_nodes *head)
{
	avl_nodes *ptr=head;
	while(ptr!=NULL)
	{
		visit(ptr->n);
		ptr=ptr->next;
	}
		
}

void list_failure(node *root,char *sub_code,int marks)
{
	if(root==NULL)
		return ;
		
	if(strcmp(sub_code,root->sub_code)<0)
		list_failure(root->left,sub_code,marks);
	else if(strcmp(sub_code,root->sub_code)>0)
		list_failure(root->right,sub_code,marks);
	else
	{
		if(root->marks<marks)
			visit(root);
	}
}
void insert_in_list(node *root,avl_nodes **head)
{
	avl_nodes *ptr,*p,*prev;
	ptr=(avl_nodes*)malloc(sizeof(avl_nodes));
	ptr->n=root;
	ptr->next=NULL;
	if(*head==NULL)
	{
		*head=ptr;
		return ;
	}
	p=*head;prev=NULL;
	while(p->n->marks>=root->marks)
	{
		prev=p;
		p=p->next;
	}
	if(prev==NULL)
	{
		ptr->next=p;
		*head=ptr;
	}
	else
	{
		prev->next=ptr;
		ptr->next=p;
	}
}
void make_kth_pop_list(node *root,char *sub_code,avl_nodes **head)
{
	if(root==NULL)
		return ;
	if(strcmp(sub_code,root->sub_code)<0)
		make_kth_pop_list(root->left,sub_code,head);
	else if(strcmp(sub_code,root->sub_code)>0)
		make_kth_pop_list(root->right,sub_code,head);
	else
	{
		insert_in_list(root,head);
		make_kth_pop_list(root->left,sub_code,head);
		make_kth_pop_list(root->right,sub_code,head);
	}
		
}

void print_kth_pop_stud(avl_nodes *head,int k)
{
	
	int l=0;
	int pop_marks=head->n->marks;
	l++;
	avl_nodes *p=head;
	while(p!=NULL && l<k)
	{
		while(p!=NULL && p->n->marks==pop_marks)
		{
			p=p->next;
		}
		if(p==NULL)
			break;
		pop_marks=p->n->marks;
		l++;
	}
	if(p==NULL)
	{
		printf("\n\n\t\t\tNo kth popular student...");
	}
	else
	{
		while(p!=NULL && p->n->marks==pop_marks)
		{
			visit(p->n);
			p=p->next;
		}
	}
}

void print_topper(topper_node *ptr)
{
	printf("\n\n");
	printf("\n\tRoll No.:%d",ptr->rno);
	printf("\n\tName:%s",ptr->name);
	printf("\n\tTotal Marks:%d",ptr->total_marks);
	printf("\n\tDeptartment:%s",ptr->dept);
	printf("\n\tSemester:%d",ptr->sem);
}


void insert_topper_list(node *root,topper_node **head)
{

	topper_node *p;
	p=(topper_node*)malloc(sizeof(topper_node));
	p->rno=root->rno;
	p->name=(char*)malloc(sizeof(char)*(strlen(root->name)+1));
	strcpy(p->name,root->name);
	p->dept=(char*)malloc(sizeof(char)*(strlen(root->dept)+1));
	strcpy(p->dept,root->dept);
	p->sem=root->sem;
	p->total_marks=root->marks;
	p->next=NULL;
	if(*head==NULL)
	{
		p->next=*head;
		*head=p;
		return ;
	}
	if(root->rno==(*head)->rno)
	{
		((*head)->total_marks)+=root->marks;
		free(p);
	}
	else
	{
		p->next=*head;
		*head=p;
	}
}

void make_topper_list(node *root,topper_node **head)
{
	if(root==NULL)
		return ;
	make_topper_list(root->left,head);
	insert_topper_list(root,head);
	make_topper_list(root->right,head);
}


void find_topper(topper_node *hdr)
{
	topper_node *ptr=hdr;
	int max=0;
	while(ptr!=NULL)
	{
		if((ptr->total_marks)>max)
			max=ptr->total_marks;
		ptr=ptr->next;
	}
	ptr=hdr;
	while(ptr!=NULL)
	{
		if((ptr->total_marks)==max)
			print_topper(ptr);
		ptr=ptr->next;
	}
}
int main()
{
	node *root,*root_sub;
	root=NULL;root_sub=NULL;
	int ans=1,choice;
	while(ans)
	{
		system("cls");
		printf("\n\t\t\tSTUDENT DATABASE!!!\n");
		printf("1.Insert in tree\n");
		printf("2.Delete record from tree\n");
		printf("3.Traverse tree\n");
		printf("4.Search in tree\n");
		printf("5.Number of nodes in tree\n");
		printf("6.Height of tree\n");
		printf("7.Range search in tree\n");
		printf("8.Topper in subjet\n");
		printf("9.Failure student in a subject\n");
		printf("10.Kth popular student\n");
		printf("11.Topper student\n");
		printf("Enter any of the above choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				{
					int rno,marks,sem;
					char name[15],sub_code[6],dept[3];
					printf("\nEnter the roll no:");
					scanf("%d",&rno);
					printf("\nEnter the student's name:");
					scanf("%s",name);
					printf("\nEnter subject code:");
					scanf("%s",sub_code);
					printf("\nEnter marks:");
					scanf("%d",&marks);
					printf("\nEnter department:");
					scanf("%s",dept);
					printf("\nEnter Semester:");
					scanf("%d",&sem);
					root=insert(root,rno,name,sub_code,marks,dept,sem);
					root_sub=insert_sub(root_sub,rno,name,sub_code,marks,dept,sem);
					break;
				}
			case 2:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!!Cannot delete from this..\n");
						break;
					}
					int rno;
					char sub_code[6];
					printf("Enter rno. and sub_code of person to be deleted");
					scanf("%d %s",&rno,sub_code);
					root=deleteNode(root,rno,sub_code);
					root_sub=deleteNode_sub(root_sub,rno,sub_code);
					break;
				}
			case 3:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!!Cannot read from this!!\n");
						break;
					}
					inOrder(root);
					//inOrder(root_sub);
					break;
				}
			case 4:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!!Cannot search in empty tree..\n");
						break;
					}
					int rno;
					char sub_code[6];
					printf("Enter rno. and sub_code of person to be searched");
					scanf("%d %s",&rno,sub_code);
					search(root,rno,sub_code);
					break;
				}
			case 5:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!! Therefore,Count=0\n");
						break;
					}
					int count=getrecord(root);
						printf("\n\n\t\t\tNo. of records in tree:%d",count);
					break;
				}
			case 6:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty Tree!! Height is zero..");
						break;
					}
					printf("\n\n\t\t\tHeight of Tree:%d",root->height);
					break;
				}
			case 7:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty Tree!! Range search cannot be done..");
						break;
					}
					int a,b;
					printf("Enter the range of roll no. in which you wish to print the records:");
					scanf("%d %d",&a,&b);
					rangesearch(root,a,b);
					break;
				}
			case 8:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!! No topper");
						break;
					}
					node *ptr;
					char sub[6]; int max=0; avl_nodes *head=NULL;
					printf("\n\n\t\tEnter the subcode whose topper u wish to see");
					scanf("%s",sub);
					getmax(root_sub,sub,&max,&head);
					print_avl_list(head);				
					break;
				}
			case 9:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!! No failure...");
						break;
					}	
					char sub_code[6]; int marks;
					printf("Enter the subject code and passing marks:");
					scanf("%s %d",sub_code,&marks);
					list_failure(root_sub,sub_code,marks);
					break;
				}
			case 10:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!! No kth popular student...");
						break;
					}
					char sub_code[6]; int k;
					avl_nodes *head=NULL;
					printf("Enter the sub_code and k value:");
					scanf("%s %d",sub_code,&k);
					make_kth_pop_list(root_sub,sub_code,&head);
					if(head==NULL)
					{
						printf("\n\n\t\t\tNo nodes found with this subject code");
						break;
					}
				//	print_avl_list(head);
					print_kth_pop_stud(head,k);
					break;
				}
			case 11:
				{
					if(root==NULL)
					{
						printf("\n\n\t\t\tEmpty tree!! No topper...");
						break;
					}
					topper_node *hdr=NULL;
					make_topper_list(root,&hdr);
					find_topper(hdr);
					break;
					
				}
			default:
				{
					printf("\n\n\t\t\tSorry wrong choice!!");
				}
		}
		printf("\n\n\t\t\tWantto perform more opertion:(0/1)");
		scanf("%d",&ans);
	}
	return 0;
}
