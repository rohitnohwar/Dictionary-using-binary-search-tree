#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
  struct node *left;
  struct node *right;
  char word[50];
  char meaning[256];
}*root=NULL;




int alphabeticalorder(char a[],char b[]){
     int i,j,k;
     for(i=0,j=0 ; a[i]!='\0'&&b[j]!='\0' ; i++,j++){
       if(a[i]>b[j])
       {
         k=1;
         break;
       }
        else if(b[j]>a[i]
        ){
          k=-1;
          break;
        }
      else{
         k=0;
      }
     }
     if(k==1)
     {
       return 1;
     }
      else if(k==-1)
      {
        return -1;
      }
      else
      {
        return 0;
      }
}

void searchword(char w[]){
  int found=0;
  struct node *ptr;
  ptr=root;
  while(ptr!=NULL && found==0){
    if(alphabeticalorder(w,ptr->word)==1)
    {
       ptr=ptr->right;
    }
    else if(alphabeticalorder(w,ptr->word)== -1)
    {
          ptr=ptr->left;
    }
    else if(alphabeticalorder(w,ptr->word)==0)
    {
       found=1;
       printf("\n%s",ptr->meaning);
    }
    }
    if(found==0)
    {
      printf("\nWord not found");
    }
}

void insertword(struct node *temp){
  int found=0;
  struct node *ptr,*par;
  ptr=root;

  if(root==NULL)
  {
     root=temp;
  }
  else{
     while(ptr!=NULL )
     {
       if(alphabeticalorder(temp->word,ptr->word)== 1){
         par=ptr;
         ptr=ptr->right;
       }

       else if(alphabeticalorder(temp->word,ptr->word)== -1)
     {
       par=ptr;
       ptr=ptr->left;
     }
       else if(alphabeticalorder(temp->word,ptr->word)==0)
       {
          found=1;
            printf("\nWord exists!!");
          break;
       }

   }
       if(found==0 && ptr==NULL){

         if(alphabeticalorder(par->word,temp->word)==1)
         {
            par->left=temp;
         }
         else if(alphabeticalorder(par->word,temp->word)==-1)
         {
            par->right=temp;
         }
       }

     }

}


void deleteword(char w[])
{
    struct node *par, *ptr, *ptr1, *ptr2;
    ptr=root;
    int found=0; 
    while(ptr!=NULL && found==0){
    if(alphabeticalorder(w,ptr->word)== 1)
    {
        par=ptr;
       ptr=ptr->right;
    }   
    else if(alphabeticalorder(w,ptr->word)== -1)
    {
        par=ptr;
          ptr=ptr->left;
    }
    else if(alphabeticalorder(w,ptr->word)==0)
    {
       found=1;
       printf("\n%s",ptr->meaning);
    }

    }
    if(found==0)
    {
      printf("\nWord not found");
    }
    else if(found==1)
    {
      if(ptr!=root)
      {
      if(ptr->right==NULL && ptr->left==NULL)
        {
            if(ptr==par->left)
            {
                par->left=NULL;
                free(ptr);
            }
            else if(ptr==par->right)
            {
                par->right=NULL;
                free(ptr);
            }
        }
        else if(ptr->right!=NULL && ptr->left==NULL)
        {
            if(ptr==par->left)
            {
                par->left=ptr->right;
                free(ptr);
            }
            else if(ptr==par->right)
            {
                par->right=ptr->right;
                free(ptr);
            }
        }
        else if(ptr->right==NULL && ptr->left!=NULL)
        {
            if(ptr==par->left)
            {
                par->left=ptr->left;
                free(ptr);
            }
            else if(ptr==par->right)
            {
                par->right=ptr->left;
                free(ptr);
            }
        }
        else if(ptr->left!=NULL && ptr->right!=NULL)
        {
            ptr2=ptr->right;
            if(ptr2->left==NULL)
            {
              strcpy(ptr->word, ptr2->word);
              strcpy(ptr->meaning, ptr2->meaning);
              ptr->right=ptr2->right;
              ptr2->right=NULL;
              free(ptr2);
            }

            else{
            while(ptr2->left!=NULL)
            {
                ptr1=ptr2;
                ptr2=ptr2->left;
            }
            strcpy(ptr->word, ptr2->word);
            strcpy(ptr->meaning, ptr2->meaning);
            ptr1->left=ptr2->right;
            ptr2->right=NULL;
            free(ptr2);
            }
        }
      }
      else if(ptr==root)
      {
        if(ptr->left==NULL && ptr->right==NULL)
        {
          root=NULL;
        }
        else if(ptr->left!=NULL && ptr->right==NULL)
        {
          ptr=ptr->left;
          strcpy(root->word, ptr->word);
          strcpy(root->meaning, ptr->meaning);
          root->left=ptr->left;
          root->right=ptr->right;
          free(ptr);
        }
        else if(ptr->left==NULL && ptr->right!=NULL)
        {
          ptr=ptr->right;
          strcpy(root->word, ptr->word);
          strcpy(root->meaning, ptr->meaning);
          root->left=ptr->left;
          root->right=ptr->right;
          free(ptr);
        }
        else if(ptr->left!=NULL && ptr->right!=NULL)
        {
          ptr=ptr->right;
          if(ptr->left==NULL)
          {
            strcpy(root->word, ptr->word);
            strcpy(root->meaning, ptr->meaning);
            root->right=ptr->right;
            ptr->right=NULL;
            free(ptr);
          }
          else
          {
            while(ptr->left!=NULL)
            {
              ptr2=ptr;
              ptr=ptr->left;
            }
            strcpy(root->word, ptr->word);
            strcpy(root->meaning, ptr->meaning);
            ptr2->left=ptr->right;
            ptr->right=NULL;
            free(ptr);
          }
        }
      }
      }
}





void inorderview(struct node *ptr){
  if(root==NULL)
  {
    printf("\nEmpty dictionary\n");
  }

  else if(ptr !=NULL)
  {
   inorderview(ptr->left);

   printf("\n%s :- %s\n",ptr->word, ptr->meaning);

   inorderview(ptr->right);
  }

}

int main(int argc, char const *argv[]) {
  int ch;
  char w[56];
  struct node *temp;
  while(ch!=5){
    printf("\n1.Search  2.Insert  3.View  4.Delete  5.Exit  Enter your choice\n");
    scanf("%d",&ch);
    switch (ch) {
      case 1:
      printf("\nEnter word");
      scanf("%s",w);
      searchword(w);
      break;
      case 2:
      temp=(struct node*)malloc(sizeof(struct node));
      temp->left=NULL;
      temp->right=NULL;
      printf("\nInsert word:\n");
      scanf("%s",temp->word);
      printf("\nInsert meaning:\n");
      scanf("%s",temp->meaning);
       insertword(temp);
      break;
      case 3:
      inorderview(root);
      break;
      case 4: printf("\nEnter the word to be deleted");
      scanf("%s", w);
      deleteword(w);
      break;

      case 5:exit(0);
    }
  }
  return 0;
}