#include <stdlib.h>
#include <stdio.h>

struct Node{
    char word [20];
    char theMeanings[100];
    char synonym[20];
    char antonym[20];
    struct Node* left ;
    struct Node* right ;
    int height;
};
struct word{
    char Word[20];
    char Meaning[100];
    char Synonym[20];
    char Antonym[20];
    struct word* Next;
};
struct string{
    char statment[50];
    struct string* next;
};
struct Node* Find( char word[], struct Node* Tree);
struct Node* Insert(char word[],char theMeanings[],char synonym[],char antonym[], struct Node* Tree );
struct Node* Delete(char word[],struct Node* Tree);
struct Node* deleteInTermsOfLetter(char l,struct Node* Tree);
struct word* Find_In_Table(char *name,struct word *Array[],int Z);
int Find_Size(int num);
struct word* Delete_From_Table(char *name,struct word *Array[],int Z);

//to make empty the tree
struct Node* MakeEmpty(struct Node* Tree){
    if(Tree != NULL){
        MakeEmpty(Tree->right);
        MakeEmpty(Tree->left);
        free(Tree);
    }
    return NULL;
}

struct Node* Tree;
struct string* S;
int Number_words = 0;
int main()
{

    //create string linked list
    S = (struct string*)malloc(sizeof(struct string));

    char option[10] = "1";
    while(strcmp(option,"1") == 0  ||strcmp(option,"2") == 0  ||strcmp(option,"3") == 0  ||strcmp(option,"4") == 0  ||strcmp(option,"5") == 0
          ||strcmp(option,"6") == 0  ||strcmp(option,"7") == 0  ||strcmp(option,"8") == 0  || strcmp(option,"9") == 0 ){
        printf("*********************************************************\n");
        printf("welcome in the Dictionary,choose one option below\n");
        printf("1.to read the data of the words from the file.\n");//done
        printf("2.to insert a new word\n");//done
        printf("3.to find a word and update it if you want\n");//done
        printf("4.to list all words in terms of lexicographic order\n");//done
        printf("5.to print a synonym and antonym for a given word\n");//done
        printf("6.to List all words that start with the same first letter\n");//done
        printf("7.to delete a word from the dictionary\n");//done
        printf("8.to delete all words that start with a specific letter\n");
        printf("9.to stored all words to the file \n");
        printf("10.to show the hash menu \n");

        fflush(stdin);
        gets(option);


        if(strcmp(option,"1") == 0){
            FILE* in;
            in =fopen("Words.txt","r");

            if(in == NULL){
                printf("the file does not exist\n");
                exit(0);
            }
            char c[100];

            //read the information from the file and store it in the string linked list
            while(fscanf(in,"%[^:/*\n]%*c",c) != EOF){
                addString(S,c);
            }
            fclose(in);

            char word[20] ;
            char theMeanings[100];
            char synonym[20];
            char antonym[20];

            int counter = 0;
            struct string* p = S;

            //move the information from string linked list to the variables
            //then add Patients contain the information to the patient linked list
            while(p->next != NULL){
                if(counter == 0){
                    strcpy(word,p->next->statment);
                    p = p->next; //let p pointer to the next node
                }
                else if(counter == 1){
                    strcpy(theMeanings,p->next->statment);
                    p = p->next; //let p pointer to the next node
                }
                else if(counter == 2){
                    strcpy(synonym,p->next->statment);
                    p = p->next; //let p pointer to the next node
                }
                else if(counter == 3){
                    strcpy(antonym,p->next->statment);
                    Tree = Insert(word,theMeanings,synonym,antonym,Tree);
                    p = p->next; //let p pointer to the next node
                    counter = -1;
                }
                ++counter;

            }

                deleteStrings(S);//delete the content of the linked list S
                printf("the read operation is success\n");
        }
        else if(strcmp(option,"2") == 0){
            printf("Enter the new word. Example: (old) \n");
            char word[20];
            fflush(stdin);
            gets(word);

            printf("Enter the meanings of this word. Example: (advanced in age, aged, antique)\n");
            char theMeanings[100];
            fflush(stdin);
            gets(theMeanings);

            printf("Enter the synonym of the word. Example: (ancient) \n");
            char synonym[20];
            fflush(stdin);
            gets(synonym);

            printf("Enter the antonym of the word. Example: (new) \n");
            char antonym[20];
            fflush(stdin);
            gets(antonym);

            Tree = Insert(word,theMeanings,synonym,antonym,Tree);

        }
        else if(strcmp(option,"3") == 0){
            printf("Enter the word to check if it exist.\n");
            char word[20];
            fflush(stdin);
            gets(word);

            struct Node* p;
            p = Find(word,Tree);

            if(p == NULL)
                printf("the word does not exist \n");
            else{
                printf("the word is exist \n");
                printf("enter 1 if you want to update the information of the word \n");
                int n;
                scanf("%d",&n);

                if(n == 1){
                    printf("Enter the new meanings of the word. Example: (advanced in age, aged, antique)\n");
                    char theMeanings[100];
                    fflush(stdin);
                    gets(theMeanings);
                    strcpy(p->theMeanings,theMeanings);

                    printf("Enter the new synonym of the word. Example: (ancient) \n");
                    char synonym[20];
                    fflush(stdin);
                    gets(synonym);
                    strcpy(p->synonym,synonym);

                    printf("Enter the new antonym of the word. Example: (new) \n");
                    char antonym[20];
                    fflush(stdin);
                    gets(antonym);
                    strcpy(p->antonym,antonym);
                }
            }

        }
        else if(strcmp(option,"4") == 0){
            PrintInOrder(Tree);
        }
        else if(strcmp(option,"5") == 0){
            printf("Enter the word to print the synonym and antonym for it. Example: (old) \n");
            char word[20];
            fflush(stdin);
            gets(word);

            struct Node* p;
            p = Find(word,Tree);

            if(p == NULL)
                printf("the word does not exist \n");
            else
                printf("The word:%s\tThe synonym:%s\tThe antonym:%s\n",p->word,p->synonym,p->antonym);
        }
        else if(strcmp(option,"6") == 0){
            printf("enter the letter\n");
            char letter[20];
            fflush(stdin);
            gets(letter);
            int k;
            for (k = 0; letter[k] != '\0'; ++k);//count the number of characters in the string

            if(k == 1){
            char l = letter[0];
            printf("The words :\n");
            PrintInTermsOfLetter(Tree,l);
            }
            else
                printf("this is not a letter \n");
        }
        else if(strcmp(option,"7") == 0){
            printf("enter the word which you want to delete it\n");
            char word[20];
            fflush(stdin);
            gets(word);
            if(Find(word,Tree) == NULL)
                printf("the word does not exist \n");

            else if(Tree->left == NULL &&Tree->right == NULL && strcmp(word,Tree->word) == 0){
                Tree = NULL;
                printf("the delete operation is success\n ");
            }
            else{
                struct Node* p;
                p = Delete(word,Tree);

                if(p != NULL)
                    printf("the delete operation is success\n ");
            }
        }
        else if(strcmp(option,"8") == 0){
            printf("enter the letter\n");
            char letter[20];
            fflush(stdin);
            gets(letter);
            char l = letter[0];

            if( Tree->left == NULL && Tree->right == NULL && Tree->word[0] == l){
                printf("the word (%s) is deleted\n ",Tree->word);
                Tree = NULL;
            }
            deleteInTermsOfLetter(l,Tree);

        }
        else if(strcmp(option,"9") == 0){
            FILE* out;
            out = fopen("Dictionary.txt","str");

            writeOnFile(Tree,out,Number_words);

            fclose(out);
            printf("the write on file is success \n");
        }
        else if(strcmp(option,"10") == 0){
        }
        else{
            printf("the option is wrong >> exit \n");
            exit(0);

        }
    }

    ///////////////////////////////////////////////////// read the final result from the file and save it in the linked list
    FILE* in;
    in =fopen("Dictionary.txt","r");

    if(in == NULL){
        printf("the file does not exist\n");
        exit(0);
    }
    char c[200];

    //read the information from the file and store it in the string linked list
    while(fscanf(in,"%[^\n]%*c",c) != EOF){
        addString(S,c);
    }
    fclose(in);
  //////////////////////////////////////////////////////////////////////////////////////////////



    int size1 =Find_Size( Number_words );// Find the number of words
    int s = 0;
    struct word *table1[size1];

    for(int i=0; i<size1 ; i++)
    {
        table1[i] = NULL;
    }


    ////////////////////////  show  List  ////////////////
    char op[10] = "1";
    while(strcmp(op,"1") == 0  ||strcmp(op,"2") == 0  ||strcmp(op,"3") == 0  ||strcmp(op,"4") == 0  ||strcmp(op,"5") == 0
          ||strcmp(op,"6") == 0  ||strcmp(op,"7") == 0  ||strcmp(op,"8") == 0 ){


        printf("*************************************************\n");
        printf("\n Now after creating  Hash Table, choose :\n");
        printf("1)  to print hashed table.\n");
        printf("2)  to print out table size.\n");
        printf("3)  to print out the used hash function.\n");
        printf("4)  to insert a new record into the hash table.\n");
        printf("5)  to search for a specific word.\n");
        printf("6)  to delete a specific record.\n");
        printf("7)  to save hash table back to file.\n");
        printf("8)  to Exit.\n");

        fflush(stdin);
        gets(option);

        if(strcmp(option,"1") == 0){
            print_Hash(table1,size1);
        }
        else if(strcmp(option,"2") == 0){
            printf("size = %d \n",size1);
        }
        else if(strcmp(option,"3") == 0){
            printf("Quadratic hashing h(x) = (function + i^2) % (size)\n");
        }
        else if(strcmp(option,"4") == 0){

            printf("Enter the new word. Example: (old) \n");
            char word[20];
            fflush(stdin);
            gets(word);

            printf("Enter the meanings of this word. Example: (advanced in age, aged, antique)\n");
            char theMeanings[100];
            fflush(stdin);
            gets(theMeanings);

            printf("Enter the synonym of the word. Example: (ancient) \n");
            char synonym[20];
            fflush(stdin);
            gets(synonym);

            printf("Enter the antonym of the word. Example: (new) \n");
            char antonym[20];
            fflush(stdin);
            gets(antonym);



        }
        else if(strcmp(option,"5") == 0){

            struct word *find;

            printf("Enter the word : ");
            char str[50];
            fflush(stdin);
            gets(str);

            find = Find_In_Table(str,table1,size1);

           if( find != NULL){
                printf("Found  %s \n",find->Word);
            }

        }
        else if(strcmp(option,"6") == 0){
            char str[50];
            printf("\tenter the word you want to delete it : ");
            fflush(stdin);
            gets(str);

            Delete_From_Table(str,table1,size1);

        }
        else if(strcmp(option,"7") == 0){

            FILE* output;
            output = fopen("Dictionary.data","str"); // to write on file name Dictionary

            int i=0;
            while( i<size1){
                if(table1[i] != NULL)
                    fprintf(output,"[%d] %s\n",i,table1[i]);
                else
                    fprintf(output,"[%d]\n",i);
                i++;
            }
            fclose(output);//close file

        }

    }
    return 0;
}
//to find any word in the dictionary
struct Node* Find( char word[], struct Node* Tree ){
    if( Tree == NULL){
        return NULL;
    }
    if(strcmp(word,Tree->word) < 0 )
        return Find( word, Tree->left );
    else if(strcmp(word,Tree->word) > 0 )
        return Find( word, Tree->right );
    else
        return Tree;
}
//to find the minimum element
struct Node* FindMin( struct Node* Tree ){
    if( Tree != NULL)
        while( Tree->left != NULL)
            Tree = Tree->left;
    return Tree;
}
//to find the maximum element
struct Node* FindMax( struct Node* Tree ){
    if( Tree != NULL )
        while( Tree->right != NULL )
            Tree = Tree->right;

    return Tree;
}
//to return the height of tree
int Height( struct Node* Tree ){
    if( Tree == NULL )
        return -1;
    else
        return Tree->height;
}
//to find the maximum height of the tree
int Max( int Lhs, int Rhs ){
    return Lhs > Rhs ? Lhs : Rhs;
}
//Right Single Rotate
struct Node* RightSingleRotate( struct Node* K2 ){
    struct Node*  K1;

    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    K2->height = Max( Height( K2->left ), Height( K2->right ) ) + 1;
    K1->height = Max( Height( K1->left ), K2->height ) + 1;

    return K1;
}
//Left Single Rotate
struct Node* LeftSingleRotate(struct Node* K1 ){
    struct Node* K2;

    K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;

    K1->height = Max( Height( K1->left ), Height( K1->right ) ) + 1;
    K2->height = Max( Height( K2->right ), K1->height ) + 1;

    return K2;
}
//Left Right Double Rotation
struct Node* LR_DoubleRotation( struct Node* K3 ){
    //Rotate between K1 and K2
    K3->left = LeftSingleRotate( K3->left );

    //Rotate between K3 and K2
    return RightSingleRotate( K3 );
}
//Right left Single Rotation
struct Node* RL_DoubleRotation( struct Node* K1 ){
    // Rotate between K3 and K2
    K1->right = RightSingleRotate( K1->right );

    // Rotate between K1 and K2
    return LeftSingleRotate( K1 );
}
//to add the word into the dictionary
struct Node* Insert(char word[],char theMeanings[],char synonym[],char antonym[], struct Node* Tree ){
    struct Node* p;
    p = Find(word,Tree);
    if(p != NULL){
        printf("the word (%s) is exist in the dictionary\n",word);
        return Tree;
    }

    if( Tree == NULL ){
        /* Create and return a one-node tree */
        Tree = (struct Node*)malloc( sizeof( struct Node ) );
        if( Tree == NULL){
            printf("Out of space");
        }
        else{
            strcpy(Tree->word,word);
            strcpy(Tree->theMeanings,theMeanings);
            strcpy(Tree->synonym,synonym);
            strcpy(Tree->antonym,antonym);
            Tree->height = 0;
            Tree->left = Tree->right = NULL;
        }
    }
    else if( strcmp(word,Tree->word) < 0 ){
        Tree->left = Insert(word,theMeanings,synonym,antonym, Tree->left );
        if( Height( Tree->left ) - Height( Tree->right ) == 2 ){
            if( strcmp(word,Tree->left->word) < 0 ){
                Tree = RightSingleRotate( Tree );
            }
            else{
                Tree = LR_DoubleRotation( Tree );
            }
        }
    }
    else if( strcmp(word,Tree->word) > 0 ){
        Tree->right = Insert(word,theMeanings,synonym,antonym, Tree->right);
        if( Height( Tree->right ) - Height( Tree->left ) == 2 ){
            if( strcmp(word,Tree->right->word) > 0 ){
                Tree = LeftSingleRotate( Tree );
            }
            else{
                Tree = RL_DoubleRotation( Tree );
            }
        }
    }
    /* Else X is in the tree already; we'll do nothing */

    Tree->height = Max( Height( Tree->left ), Height( Tree->right ) ) + 1;
    return Tree;
}
//add string to the string link list
void addString(struct string* S ,char new_data[]){

    struct string* temp,*p;
    temp = (struct string*)malloc(sizeof(struct string));
    p = (struct string*)malloc(sizeof(struct string));
    p = S;

    //let p pointer on the last patient
    while(p->next != NULL){
        p = p->next;
    }

    strcpy(temp->statment,new_data);

    temp -> next = NULL;
    p -> next = temp;
}
//to delete the list of strings
void deleteStrings(struct string* S){
    struct string* p;
    struct string* temp;

    p = S->next;
    S->next = NULL;

    //to move from node to node and free it
    while (p != NULL){
        temp = p->next;
        free(p);
        p = temp;
    }
}
//to print the words and their meanings,synonym,antonym in order
void PrintInOrder( struct Node* Tree){
    if( Tree != NULL){
        PrintInOrder( Tree->left );
        printf("The word:%s  The meanings:%s  The synonym:%s  The antonym:%s\n", Tree->word,Tree->theMeanings,Tree->synonym,Tree->antonym);
        PrintInOrder( Tree->right );
    }
}
//to print the words and their meanings,synonym,antonym in order
void PrintInTermsOfLetter( struct Node* Tree,char l){
    if( Tree != NULL){
        PrintInTermsOfLetter( Tree->left,l );
        if(Tree->word[0] == l){
            printf("%s\n", Tree->word);
        }
        PrintInTermsOfLetter( Tree->right,l);
    }
}
//to delete word from the tree
struct Node* Delete(char word[],struct Node* Tree){
    if (Tree == NULL)
        return Tree;

    if ( strcmp(word,Tree->word) > 0 )// If the key to be deleted is greater than the Tree's key, then it lies in right subtree
        Tree->right = Delete(word,Tree->right);
    else if( strcmp(word,Tree->word) < 0 )// If the key to be deleted is smaller than the Tree's key, then it lies in left subtree
        Tree->left = Delete(word,Tree->left);
    else{ // if key is same as Tree's key, then This is the node to be deleted
        // node with only one child or no child
        if( (Tree->right == NULL) || (Tree->left == NULL)){
            struct Node *temp = Tree->left ? Tree->left :Tree->right;
            // No child case
            if (temp != NULL){
                *Tree = *temp; // Copy the contents of the non-empty child
            }
            else{ // One child case
                temp = Tree;
                Tree = NULL;
            }

            free(temp);
        }
        else{
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = FindMin(Tree->right);
            // Copy the inorder successor's data to this node
            strcpy(Tree->word,temp->word);
            strcpy(Tree->antonym,temp->antonym);
            strcpy(Tree->synonym,temp->synonym);
            strcpy(Tree->theMeanings,temp->theMeanings);

            // Delete the inorder successor
            Tree->right = Delete(temp->word,Tree->right);
        }
    }

    // If the tree had only one node then return
    if (Tree == NULL)
      return Tree;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    Tree->height = Max(Height(Tree->left),Height(Tree->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(Tree);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(Tree->left) >= 0)
        return RightSingleRotate(Tree);

    // Left Right Case
    if (balance > 1 && getBalance(Tree->left) < 0){
        Tree->left =  LeftSingleRotate(Tree->left);
        return RightSingleRotate(Tree);
    }

    // Right Right Case
    if (balance < -1 && getBalance(Tree->right) <= 0)
        return LeftSingleRotate(Tree);

    // Right Left Case
    if (balance < -1 && getBalance(Tree->right) > 0){
        Tree->right = RightSingleRotate(Tree->right);
        return LeftSingleRotate(Tree);
    }

    return Tree;
}
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    int x = Height(N->left) - Height(N->right);
    return x;
}
//to search in terms of the first letter
struct Node* deleteInTermsOfLetter(char l,struct Node* Tree){

    if(Tree != NULL){
       deleteInTermsOfLetter(l,Tree->left);
       if(Tree->word[0] == l){
            printf("the word (%s) is deleted\n ",Tree->word);
            Delete(Tree->word,Tree);
       }
       deleteInTermsOfLetter(l,Tree->right);
    }
}
//write on the file
void writeOnFile(struct Node* Tree,FILE* out , int Number_words){

    if( Tree != NULL){
        writeOnFile( Tree->left,out,Number_words );
        fprintf(out,"The word:%s  The meanings:%s  The synonym:%s  The antonym:%s\n", Tree->word,Tree->theMeanings,Tree->synonym,Tree->antonym);
        Number_words++;
        writeOnFile( Tree->right,out,Number_words );
    }
}
////////////////////////////////
//////////////////////////////////
///////////////////////////////////
//////////////////////////////////////
//quadratic hash

 int hash(char * name,int Z){
    int k = 0;
    for(int i=0; i<strlen(name) ; i++){
        k += name[i];
        k = (k ) % Z;
    }
    return k;
}


void Insert2(struct word *p,struct word *Array[],int Z){
    int index = hash(p->Word,Z);

    int i=0;
    while( i< Z){
        int try = ((i*i)+index)% Z;

        if(Array[try]==NULL){
            Array[try] = p;
            return ;
        }
        i++;
    }
}
//to search for the word in the table
struct word *Find_In_Table(char *name,struct word *Array[],int Z)
{
    int k = hash(name,Z);

    int i=0;
    while( i < Z ){
        int try = ((i*i)+k)% Z;
        if(Array[try] == NULL){
            return ;
        }
        if(Array[try] != NULL && strncmp(Array[try]->Word,name,Z)==0)
                return Array[try];
        i++;
    }
    return NULL;
}
//to delete the word from the table
struct word* Delete_From_Table(char *name,struct word *Array[],int Z){
    int index = hash(name,Z);

    int i=0;
    while( i < Z ){
        int try = ((i*i)+index)% Z;
        if(Array[try] == NULL){
            printf(" not found \n");
            return NULL;
        }
        if( strncmp(Array[try]->Word,name,Z) == 0){
            struct Node* t= Array[try];
            Array[try]=NULL;
            return t;
        }
    i++;
    }
    return NULL;
}
//to print the hash
void print_Hash(struct word *Array[],int Z){
    int i=0;
    while( i < Z ){
        if(Array[i] == NULL)
            printf("[%d]\t\n",i);
        else
            printf("[%d]\t%s\n",i,Array[i]->Word);

        i++;
    }
}
//to find the size
int Find_Size(int number){
    int theFlag = 1;
    int x = number + 1;

    int i = 2;
    while(  i <= x/2 ){
        if ( x%i == 0 ){
            theFlag = 0;
            break;
        }
        i++;
    }

    if(x==2)
        theFlag=1;
    else if( x<=1 )
        theFlag=0;

    if (theFlag != 1)
        Find_Size(x);
    else
        return x;

}
