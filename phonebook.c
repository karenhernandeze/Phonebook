#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>
#include <time.h>

struct InfoCard
{
  long id;
  char first_name[20];
  char last_name[30];
  char gender[8];
  char number[20];
  char email[100];
};

void addContact();
void searchContact();
void editContacts();
void deleteContact();
void showAll();
void menu();
FILE *fptr;

void addContact()
{
  struct InfoCard contact;

  fptr = fopen("myPhonebook.bin", "ab");
  if (fptr == NULL)
  {
    printf("Error!");
  }

  printf("Enter first name: ");
  while (getchar() != '\n');
  char name[20];
  scanf(" %s", name);
  strcpy(contact.first_name, name);

  printf("Enter last name: ");
  while (getchar() != '\n');
  char lName[30];
  scanf(" %s", lName);
  strcpy(contact.last_name, lName);
  
  printf("Enter gender: ");
  while (getchar() != '\n');
  char sex[8];
  scanf(" %s", sex);
  strcpy(contact.gender, sex);

  printf("Enter phone number: ");
  while (getchar() != '\n');
  char number[20];
  scanf(" %s", number);
  strcpy(contact.number, number);

  printf("Enter email: ");
  while (getchar() != '\n');
  char email[100];
  scanf(" %s", email);
  strcpy(contact.email, email);

  //Create unique ID using time
  time_t t = time(NULL);
  contact.id = t;

  fwrite(&contact, sizeof(struct InfoCard), 1, fptr);
  fclose(fptr);

  menu();
}

void searchContact()
{
  showAll();
  // struct InfoCard inp;
  // fptr = fopen("myPhonebook.bin", "r");
  // if (fptr == NULL)
  // {
  //   fprintf(stderr, "\nError to open the file\n");
  //   // exit (1);
  // }
  // while (fread(&inp, sizeof(struct InfoCard), 1, fptr))
  //   printf("roll_no = %d name = %s\n", inp.id, inp.first_name);
  // fclose(fptr);

  // // InfoCard input;
  // // while (fread(&input, sizeof(InfoCard), 1, fptr))
  // //   printf("id = %d name = %s %s\n", input.email);
  // printf("Search");
}

void editContact()
{
  printf("Edit");
}

void deleteContact()
{
  printf("Delete");
}

void showAll()
{
  struct InfoCard list;
  fptr = fopen("myPhonebook.bin", "rb");
  if (fptr == NULL)
  {
    fprintf(stderr, "\nError to open the file\n");
  }

  while (fread(&list, sizeof(list), 1, fptr) == 1)
  {
    printf("ID: %d\nName: %s\nLast Name: %s\nGender: %s\nNumber: %s\nEmail: %s\n", list.id, list.first_name,
           list.last_name, list.gender, list.number, list.email);

  }
  fclose(fptr);
  menu();
  
}

void menu()
{
  int increment = 1;
  void (*operation)();
  int selection;
  printf("\nMENU\n");
  printf("\n\t1.Add New Contact  \t2.Search Contact  \t3.Edit Contact \n\t4.Delete Contact \t5.Exit Program\n\n");
  // while (getchar() != '\n');
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

  // if (access("myPhonebook.bin", F_OK) != -1)
  // {
  //   printf("\nEnter your password: \n");
  //   scanf(" %c", &pass);
  //   // TO DO - HASH ENTERED PASSWORD COMPARE WITH PAST PASSWD
  //   //  IF INCORRECT EXIT PROGRAM ELSE CONTINUE
  //   menu();
  // }
  // else
  // {
  //   printf("\nWelcome to your personal phonebook.\n");
  //   printf("\nCreate a password to secure your contacts. Do not forget it, it will be asked next time you want to access it.\n");
  //   printf("\nEnter your password: \n");
  //   scanf(" %c", &pass);
  //   // TO DO - HASH PASS'
  //   fptr = fopen("myPhonebook.bin", "a+");
  menu();
  // }
  // printf("Welcome to your phonebook");
  return 0;
}