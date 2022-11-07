//SPELL CORRECTION USING TERNARY SEARCH TREE
//PROJECT MADE BY
//VAIBHAV KUMAR-       2021MCB1219
//KARAN DEEP DAS-      2021MCB1236
//KANHAIYA KUMAR SAHU- 2021MCB1235

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//the following three array would be used to check if the error letter in spelling is if because of adjacent letter typed 
char keyboard_arr1[10]={'q','w','e','r','t','y','u','i','o','p'};
char keyboard_arr2[9]={'a','s','d','f','g','h','j','k','l'};
char keyboard_arr3[7]={'z','x','c','v','b','n','m'};

// char word arr is an array of strings that will store all the words that match the first few letters of the input word for correction using the function search_similar_word(root,key) 
char word_arr[1000][100];
static int w=0;
#define MAX 50


//the following function copies one string into another given string
void copy_string(char d[],char s[],int n) {
  int c = 0;
   int i=0;
  while (i<n) {
    d[c] = s[c];
    c++;
    i++;
  }
  d[c] = '\0';
}
//the following function copies the rest part of a given string[j,....,length-1] into given another string
void copy_rest(int j,char d[],char s[]) {
  int c = j;
  while (c<strlen(s)) {
    d[c] = s[c];
    c++;
    
  }
  d[c] = '\0';
}

//  Node of a TST(ternary search tree)
struct Node
{
	char value;
	unsigned is_End_of_Word: 1;                  // 1 i.e true if this letter is the last letter of one of the words that are stored in TST
	struct Node *left_pointer, *eq, *right_pointer;
};

// This function is used to create a default Ternary search tree Node with its left_pointer and right_pointer child pointing NULL
struct Node* newNode(char value)
{
	struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
	temp->value=value;
	temp->is_End_of_Word=0;
	temp->left_pointer=temp->eq=temp->right_pointer=NULL;
	return temp;
}

// The following function is used for insertion of words from the dictionary file into TST(ternary search Tree)
void insert(struct Node** root,char *word)
{
	// if Tree is empty
	if (!(*root)){
		*root=newNode(*word);}

	// if present letter of word is smaller than root's letter than insertion happens in left_pointer subtree of root of TST
	if ((*word)<(*root)->value){
		insert(&((*root)->left_pointer),word);}

	// if present letter of word is greater than root's letter then insertion happens in right_pointer subtree of root of TST
	else if ((*word)>(*root)->value){
		insert(&((*root)->right_pointer),word);}

	// if present letter of word is same as root's letter,
	else
	{
		if (*(word+1)){
			insert(&((*root)->eq),word+1);
        }
		// if it is the end letter of word
		else{
			(*root)->is_End_of_Word = 1;
        }
    }
}


// this search function just search if the word given in this function argument is present in TST
int search(struct Node *root, char *word)
{
    if (!root){
        return 0;
        }
    if (*word < (root)->value){
        return search(root->left_pointer, word);
        }
    else if (*word > (root)->value){
        return search(root->right_pointer, word);
        }
    else
    {
        if (*(word+1) == '\0')
            return root->is_End_of_Word;
        return search(root->eq, word+1);
    }
}


// the following function is used for traversing through the TST
void traverseTST2(struct Node* root, char* buffer, int depth,char* subtext)
{   
    
	if (root)
	{   
        
		traverseTST2(root->left_pointer,buffer,depth,subtext);

		buffer[depth]=root->value;
		if (root->is_End_of_Word)
		{
			buffer[depth+1] = '\0';
            int k=strlen(subtext)+strlen(buffer);
            char* summed1=(char*)malloc(sizeof(char)*(k));
            char* summed2=(char*)malloc(sizeof(char)*(strlen(buffer)));
            strcpy(summed1,subtext);
            strcat(summed1,buffer);
            strcpy(word_arr[w],summed1);
            w+=1;
		}
        
        
        
        
		traverseTST2(root->eq, buffer, depth + 1,subtext);
		traverseTST2(root->right_pointer, buffer, depth,subtext);
	}
}


// function to search for the dictionary word with similar letters of input word that could make up dictionary word
int search_similar(struct Node *root, char *word,char*key)
{   static char* subtext;
    static int i=0;
    static int depth=0;
    char buffer[MAX];
	if (!root){
		return -1;
    }
	if (*word < (root)->value){   
		return search_similar(root->left_pointer,word,key);
    }
	else if (*word > (root)->value){
        return search_similar(root->right_pointer, word,key);
    }

	else
	{   i+=1;
		if (*(word+1) == '\0'){
			return root->is_End_of_Word;
        }
        else if (search_similar(root->eq, word+1,key)==-1){
            
            //printf("the value of i is %d \n",i);
            subtext=(char*)malloc(sizeof(char)*(i));
            //char subtext[1000];
            //printf("is the word changing %s\n",key);
            copy_string(subtext,key,i);
            //printf("subtxt made is %s\n",subtext);

            // if the max similar letter that could make dictionary word are finally reached then it traverses all the possible words with those similar letter
            traverseTST2(root->eq, buffer,0,subtext);
            return 1;
            
        }
	}
}



//the following function just simply replaces every letter with adjacent character in keyboard and then checks from search function if the the replaced word is in TST if yes then returns that word immediately

int replace(struct Node *root,char* word,char c,int uptill){
    
    int flag=0;
    for (int i=0;i<10;i++){
        if(keyboard_arr1[i]==c){
            char new_left[1000];
            char new_right[1000];
            copy_string(new_left,word,uptill);
            copy_string(new_right,word,uptill);
            
            if(i>0 && i<9){
            char replacebyleft=keyboard_arr1[i-1];
            char replacebyright=keyboard_arr1[i+1];
            
            strcat(new_left,&replacebyleft);
            strcat(new_right,&replacebyright);
            copy_rest(uptill+1,new_left,word);
            copy_rest(uptill+1,new_right,word);
            
            
                if(search(root,new_left)==1){
                    printf("corrected form of %s should be %s\n ",word,new_left);
                    return 1;
                }
                else if(search(root,new_right)==1){
                    printf("corrected form of %s should be %s\n ",word,new_right);
                    return 1;
                }
            
            }
            else if (i==9){
            char replacebyleft=keyboard_arr1[i-1];
            
            strcat(new_left,&replacebyleft);
            copy_rest(uptill+1,new_left,word);
            
            
                if(search(root,new_left)==1){
                    printf("corrected form of %s should be %s\n ",word,new_left);
                    return 1;
                }
            
            }

            else if (i==0){
            char replacebyright=keyboard_arr1[i+1];
            
            strcat(new_right,&replacebyright);
            copy_rest(uptill+1,new_right,word);
            
            
                if(search(root,new_right)==1){
                    printf("corrected form of %s should be %s\n ",word,new_right);
                    return 1;
                }
            
            }

            }

        }
    for (int i=0;i<9;i++){
        if(keyboard_arr2[i]==c){
            char new_left[1000];
            char new_right[1000];
            copy_string(new_left,word,uptill);
            copy_string(new_right,word,uptill);
           
            if(i>0 && i<8){
            char replacebyleft=keyboard_arr2[i-1];
            char replacebyright=keyboard_arr2[i+1];
            
            strcat(new_left,&replacebyleft);
            strcat(new_right,&replacebyright);
            copy_rest(uptill+1,new_left,word);
            copy_rest(uptill+1,new_right,word);
            
            
                if(search(root,new_left)==1){
                    printf("corrected form of %s should be %s\n ",word,new_left);
                    return 1;
                }
                else if(search(root,new_right)==1){
                    printf("corrected form of %s should be %s\n ",word,new_right);
                    return 1;
                }
            
            }
            else if (i==8){
            char replacebyleft=keyboard_arr2[i-1];
            
            strcat(new_left,&replacebyleft);
            copy_rest(uptill+1,new_left,word);
            
            
                if(search(root,new_left)==1){
                    printf("corrected form of %s should be %s\n ",word,new_left);
                    return 1;
                }
            
            }

            else if (i==0){
            char replacebyright=keyboard_arr2[i+1];
            
            strcat(new_right,&replacebyright);
            copy_rest(uptill+1,new_right,word);
            
            
                if(search(root,new_right)==1){
                    printf("corrected form of %s should be %s\n ",word,new_right);
                    return 1;
                }
            
            }

            }

        }

        for (int i=0;i<7;i++){
        if(keyboard_arr3[i]==c){
            char new_left[1000];
            char new_right[1000];
            copy_string(new_left,word,uptill);
            copy_string(new_right,word,uptill);
            
            if(i>0 && i<6){
            char replacebyleft=keyboard_arr3[i-1];
            char replacebyright=keyboard_arr3[i+1];
            
            strcat(new_left,&replacebyleft);
            strcat(new_right,&replacebyright);
            copy_rest(uptill+1,new_left,word);
            copy_rest(uptill+1,new_right,word);
            
            
                if(search(root,new_left)==1){
                    printf("corrected form of %s should be %s\n ",word,new_left);
                    return 1;
                }
                else if(search(root,new_right)==1){
                    printf("corrected form of %s should be %s\n ",word,new_right);
                    return 1;
                }
            
            }
            else if (i==6){
            char replacebyleft=keyboard_arr3[i-1];
            
            strcat(new_left,&replacebyleft);
            copy_rest(uptill+1,new_left,word);
            
            
                if(search(root,new_left)==1){
                    printf("corrected form of %s should be %s\n ",word,new_left);
                    return 1;
                }
            
            }

            else if (i==0){
            char replacebyright=keyboard_arr3[i+1];
            
            strcat(new_right,&replacebyright);
            copy_rest(uptill+1,new_right,word);
            
            
                if(search(root,new_right)==1){
                    printf("corrected form of %s should be %s\n ",word,new_right);
                    return 1;
                }
            
            }

            }

        }

    return 0;
    
    
}



//the following is the main algorith that usese all the above function to finally give you all the possible cases to correct a given input of incorrect word
void algorithm(struct Node *root,char* key,int length){

        int flag=0;

        if(search(root,key)==1){                                         //cas0: when the word is already correct that is present in TST dictionary
            printf("word %s is already correct\n");
            return;
        }

        
        for(int j=0;j<strlen(key);j++){                                 //case1: when the error is because of one letter of the input word misplaced with adjacent letter
            if(replace(root,key,key[j],j)==1){
                flag=1;
                break;
            }

        }
        if(flag==1){
            return;
        }

        
        for(int j=97;j<123;j++){                                        //case2: when one letter at the end of the input word is missing
            char new_word[1000];
            char add_letter=(char)j;
            copy_string(new_word,key,length);
            
            strncat(new_word,&add_letter,1);


            
            if(search(root,new_word)==1){
                printf("corrected form of %s should be %s\n",key,new_word);
                flag=1;
                break;
            }
            else{
                strcpy(new_word,key);
            }
        }
        if(flag==1){
            return;
        }
    

        char new_word_case3[1000];                                         //case3: when one extra letter is typed by mistake at the end of the given input word
        copy_string(new_word_case3,key,length-1);
        
        if(search(root,new_word_case3)==1){
            printf("correct form of %s should be %s\n",key,new_word_case3);
            flag==1;
            return;
        }
        
        
        printf("correct form of %s might be %s\n",key,word_arr[0]);                              //case4: else case it just gives the min length word of the maximum similar letter input word that could be present in dictionary
        return;


    
}


int main()
{

    //the following code will first read a words.txt file store all the dictionary word of 10,000 words into our TST
    FILE* ptr;
	  char ch[2000];

    struct Node *root = NULL;
    
	ptr = fopen("words.txt", "r");
    char key[2000];
	printf("enter word for correction in small case: ");
	gets(key);
	int key_length=strlen(key);
	

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}
    
	
    int count=0;
    while(fscanf(ptr,"%s ",ch)==1){
        insert(&root, ch);
        
        count+=1;
    }

	search_similar(root, key,key);
	/*for(int i=0;i<w;i++){                                 //comment out this part to get all the possible corrections for checking
        printf("%s\n",word_arr[i]);
    }*/

    //search(root, key)? printf("Found\n"): printf("Not Found\n");
    algorithm(root,key,strlen(key));
    
	return 0;
}
