#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define Max_Digits 20

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

// DONE
void addContact()
{
  struct InfoCard contact;

  fptr = fopen("myPhonebook.bin", "ab");
  if (fptr == NULL)
  {
    printf("Error!");
  }

  printf("Enter first name: ");
  while (getchar() != '\n')
    ;
  char name[20];
  scanf("%[^\n]s", name);
  strcpy(contact.first_name, name);

  printf("Enter last name: ");
  while (getchar() != '\n')
    ;
  char lName[30];
  scanf(" %s", lName);
  strcpy(contact.last_name, lName);

  printf("Enter gender: ");
  while (getchar() != '\n')
    ;
  char sex[8];
  scanf(" %s", sex);
  strcpy(contact.gender, sex);

  printf("Enter phone number: ");
  while (getchar() != '\n')
    ;
  char number[20];
  scanf(" %s", number);
  strcpy(contact.number, number);

  printf("Enter email: ");
  while (getchar() != '\n')
    ;
  char email[100];
  scanf(" %s", email);
  strcpy(contact.email, email);

  // Create unique ID using time
  time_t t = time(NULL);
  contact.id = t;

  fwrite(&contact, sizeof(struct InfoCard), 1, fptr);
  fclose(fptr);

  menu();
}

// DONE
void searchContact()
{
  struct InfoCard contact;
  char name[100];
  int flag = 0;
  fptr = fopen("myPhonebook.bin", "rb");
  if (fptr == NULL)
  {
    printf("\n error in opening\n");
    exit(1);
  }
  printf("\nEnter name of contact to search\n");
  while (getchar() != '\n')
    ;
  scanf("%[^\n]s", name);

  while (fread(&contact, sizeof(contact), 1, fptr) == 1)
  {
    if (strcasecmp(contact.first_name, name) == 0 || strstr(contact.first_name, name) != NULL)
    {
      flag = 1;
      printf("\n\tDetail Information About Contact(s)\n:");
      printf("ID: %ld\nName: %s\nLast Name: %s\nGender: %s\nNumber: %s\nEmail: %s\n", contact.id, contact.first_name,
             contact.last_name, contact.gender, contact.number, contact.email);
    }
  }
  if (flag != 1)
  {
    printf("Contact does not exist.");
  }
  fclose(fptr);
  menu();
}

// DONE
void editContact()
{
  showAll();
  struct InfoCard contact;
  FILE *ftemp;
  int flag = 1;

  fptr = fopen("myPhonebook.bin", "rb");
  if (fptr == NULL)
  {
    printf("\n error in opening\n");
    exit(1);
  }
  ftemp = fopen("temp.bin", "ab+");
  printf("\nEnter the id of contact to edit:\n");
  while (getchar() != '\n')
    ;
  long id;
  scanf(" %ld", &id);

  while (fread(&contact, sizeof(contact), 1, fptr) == 1)
  {
    if (contact.id == id)
    {
      printf("Enter the updated first name: ");
      while (getchar() != '\n')
        ;
      char name[20];
      scanf("%[^\n]s", name);
      strcpy(contact.first_name, name);

      printf("Enter the updated last name: ");
      while (getchar() != '\n')
        ;
      char lName[30];
      scanf(" %s", lName);
      strcpy(contact.last_name, lName);

      printf("Enter the updated gender: ");
      while (getchar() != '\n')
        ;
      char sex[8];
      scanf(" %s", sex);
      strcpy(contact.gender, sex);

      printf("Enter the updated phone number: ");
      while (getchar() != '\n')
        ;
      char number[20];
      scanf(" %s", number);
      strcpy(contact.number, number);

      printf("Enter the updated email: ");
      while (getchar() != '\n')
        ;
      char email[100];
      scanf(" %s", email);
      strcpy(contact.email, email);

      fwrite(&contact, sizeof(struct InfoCard), 1, ftemp);
      flag = 0;
    }
    if (contact.id != id)
    {
      fwrite(&contact, sizeof(contact), 1, ftemp);
    }
  }

  fclose(fptr);
  fclose(ftemp);

  if (flag == 1)
  {
    printf("NO CONTACT FOUND WITH THAT ID.");
    remove("temp.bin");
  }
  else
  {
    remove("myPhonebook.bin");
    rename("temp.bin", "myPhonebook.bin");
    showAll();
    printf("Contact updated successfully");
  }

  menu();
}

// DONE
void deleteContact()
{
  showAll();
  struct InfoCard contact;
  FILE *ftemp;
  int flag = 1;

  fptr = fopen("myPhonebook.bin", "rb");
  if (fptr == NULL)
  {
    printf("\n error in opening\n");
    exit(1);
  }
  ftemp = fopen("temp.bin", "ab+");
  printf("\nEnter the id of contact to delete:\n");
  while (getchar() != '\n')
    ;
  long id;
  scanf(" %ld", &id);

  while (fread(&contact, sizeof(contact), 1, fptr) == 1)
  {
    if (contact.id != id)
    {
      fwrite(&contact, sizeof(contact), 1, ftemp);
      // flag = 1;
    }
    if (contact.id == id)
    {
      flag = 0;
    }
  }

  fclose(fptr);
  fclose(ftemp);

  if (flag == 1)
  {
    printf("NO CONTACT FOUND WITH THAT ID.");
    remove("temp.bin");
  }
  else
  {
    remove("myPhonebook.bin");
    rename("temp.bin", "myPhonebook.bin");
    showAll();
    printf("Contact deleted successfully");
  }

  menu();
}

// DONE
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
    printf("ID: %ld\nName: %s\nLast Name: %s\nGender: %s\nNumber: %s\nEmail: %s\n\n\n", list.id, list.first_name,
           list.last_name, list.gender, list.number, list.email);
  }
  fclose(fptr);
}

// DONE
void menu()
{
  int increment = 1;
  void (*operation)();
  int selection;
  printf("\n\nMENU:\n");
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
  case 6:
    showAll();
    menu();
    break;
  default:
    printf("Please select a number between 1-5");
    break;
  }
}

int main(int arc, char *argv[])
{
  FILE *psswdFile;

  unsigned char digest[SHA256_DIGEST_LENGTH];

  if (access("myPhonebook.bin", F_OK) != -1)
  {
    char pass;
    printf("\nEnter your password: \n");
    scanf(" %s", &pass);

    //HASH PASSWORD ENTERED
    SHA256((unsigned char *)&pass, sizeof(pass), (unsigned char *)&digest);
    char mdString[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
      sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

    //READ HASH FOR EXISTING PASSWORD
    char buffer[SHA256_DIGEST_LENGTH * 2 + 1]; 
    psswdFile = fopen("check.bin", "rb");
    int count = fread(&buffer, sizeof(char), (SHA256_DIGEST_LENGTH * 2 + 1), psswdFile);
    fclose(psswdFile);

    if (strcmp(mdString, buffer) == 0){
      printf("Correct password.\n\n");
      menu();
    } else {
      printf("Incorrect password\n\n");
    }
  }
  else
  {
    char pass;
    printf("\nWelcome to your personal phonebook.\n");
    printf("\nCreate a password to secure your contacts. Do not forget it, it will be asked next time you want to access it.\n");
    printf("\nEnter your password: \n");
    scanf(" %s", &pass);
    SHA256((unsigned char *)&pass, sizeof(pass), (unsigned char *)&digest);
    char mdString[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
      sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

    psswdFile = fopen("check.bin", "wb");


    fwrite(mdString, sizeof(struct InfoCard), 1, psswdFile);
    fclose(psswdFile);

    menu();
  }
  return 0;
}