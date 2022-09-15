#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _InfoCard
{
  int id;
  char *name;
  char *last_name;
  char *gender;
  unsigned long number;
  char *email;
} InfoCard;

  FILE *fptr;


void addContact()
{
        fptr =fopen("project","ab+");

  printf("Add");
}

void searchContact()
{
  printf("Search");
}

void editContact()
{
  printf("Edit");
}

void deleteContact()
{
  printf("Delete");
}

void menu()
{
  void (*operation)();
  int selection;
  printf("\nMENU\n");
  printf("\n\t1.Add New Contact  \t2.Search Contact  \t3.Edit Contact \n\t4.Delete Contact \t5.Exit Program\n\n");
  while(getchar()!='\n');
  scanf(" %d", &selection);

  switch (selection)
  {
  case 1:
    operation = addContact;
    (*operation)();
    break;
  case 2:
    operation = searchContact;
    (*operation)();
    break;
  case 3:
    operation = editContact;
    (*operation)();
    break;
  case 4:
    operation = deleteContact;
    (*operation)();
    break;
  case 5:
    exit(0);
    break;
  default:
    printf("Please select a number between 1-5");
    break;
  }

}

int main(int arc, char *argv[])
{
  // FILE *fptr;
  char pass;

  if (access("myPhonebook.bin", F_OK) != -1)
  {
    printf("\nEnter your password: \n");
    scanf(" %c", &pass);
    // TO DO - HASH ENTERED PASSWORD COMPARE WITH PAST PASSWD
    //  IF INCORRECT EXIT PROGRAM ELSE CONTINUE
    menu();
  }
  else
  {
    printf("\nWelcome to your personal phonebook.\n");
    printf("\nCreate a password to secure your contacts. Do not forget it, it will be asked next time you want to access it.\n");
    printf("\nEnter your password: \n");
    scanf(" %c", &pass);
    // TO DO - HASH PASS'
    fptr = fopen("myPhonebook.bin", "ab+");
    menu();
  }
  // printf("Welcome to your phonebook");
  return 0;
}