#include "Contact.h"
#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *List_create() {
  List *new_list = (List *)malloc(sizeof(List));
  if (new_list != NULL)
    new_list->first_contact = NULL;
  return new_list;
};

Contact *Contact_create(const char *name, const char *cpf) {
  Contact *new_contact = (Contact *)malloc(sizeof(Contact));
  if (new_contact != NULL) {
    strncpy(new_contact->name, name, MAX_NAME_LENGTH - 1);
    new_contact->name[MAX_NAME_LENGTH - 1] = '\0';

    strncpy(new_contact->cpf, cpf, MAX_CPF_LENGTH - 1);
    new_contact->cpf[MAX_CPF_LENGTH - 1] = '\0';

    new_contact->phones = NULL;
    new_contact->emails = NULL;
    new_contact->prox = NULL;
  }
  return new_contact;
}

bool Contact_edit_name(Contact *contact, const char *name) {
  if (contact == NULL) {
    printf("\nContato nao encontrado\n");
    return false;
  }
  if (strcmp(contact->name, name) == 0) {
    printf("\nA informacao a ser substituida converge com a informacao "
           "substituta");
    return false;
  }

  strcpy(contact->name, name);
  return true;
}

bool Contact_edit_cpf(Contact *contact, const char *cpf) {
  if (contact == NULL) {
    printf("\nContato nao encontrado\n");
    return false;
  }
  if (strcmp(contact->cpf, cpf) == 0) {
    printf("\nA informacao a ser substituida converge com a informacao "
           "substituta");
    return false;
  }

  strcpy(contact->cpf, cpf);
  return true;
}

bool Phone_insert(Contact *contact, const char *phone) {
  Phone *new_phone = (Phone *)malloc(sizeof(Phone));
  if (new_phone == NULL) {
    return false;
  }
  strncpy(new_phone->number, phone, MAX_PHONE_LENGTH - 1);
  new_phone->number[MAX_PHONE_LENGTH - 1] = '\0';
  new_phone->prox = NULL;
  if (contact->phones == NULL) {
    contact->phones = new_phone;
    contact->phones->qty++;
    return true;
  }
  Phone *auxiliar = contact->phones;
  while (auxiliar->prox != NULL)
    auxiliar = auxiliar->prox;

  auxiliar->prox = new_phone;
  contact->phones->qty++;
  return true;
}

bool Phone_remove(Contact *contact, const char *phone) {
  if (contact == NULL)
    return false;
  // Checa se o primeiro telefone a lista é o telefone a ser removido
  if (strcmp(contact->phones->number, phone) == 0) {
    Phone *phone_temp = contact->phones;
    contact->phones = phone_temp->prox;
    contact->phones->qty--;
    free(phone_temp);
    return true;
  }

  // Procura o telefone a ser removido da lista
  Phone *prev = contact->phones;
  Phone *current = prev->prox;
  while (current != NULL) {
    if (strcmp(current->number, phone) == 0) {
      prev->prox = current->prox;
      contact->phones->qty--;
      free(current);
      return true;
    }
    prev = current;
    current = current->prox;
  }

  printf("Numero nao encontrado");
  return false;
};

Phone *Phone_find(Contact *contact, const char *phone_number) {
  if (contact == NULL)
    return NULL;
  if (strcmp(contact->phones->number, phone_number) == 0) {
    return contact->phones;
  }
  Phone *prev = contact->phones;
  Phone *current = prev->prox;
  while (current != NULL) {
    if (strcmp(current->number, phone_number) == 0) {
      return current;
    }
    prev = current;
    current = current->prox;
  }
  printf("Numero nao encontrado");
  return NULL;
}

bool Phone_edit(Phone *phone_to_edit, const char *new_number) {
  if (phone_to_edit == NULL) {
    return false;
  }
  strcpy(phone_to_edit->number, new_number);
  return true;
}

bool Email_insert(Contact *contact, const char *mailaddress) {
  Email *new_mail = (Email *)malloc(sizeof(Email));
  if (new_mail == NULL)
    return false;

  strncpy(new_mail->mail, mailaddress, MAX_MAIL_LENGTH - 1);
  new_mail->mail[MAX_MAIL_LENGTH - 1] = '\0';
  new_mail->prox = NULL;

  if (contact->emails == NULL) {
    contact->emails = new_mail;
    contact->emails->qty++;
    return true;
  }

  Email *auxiliar = contact->emails;
  while (auxiliar->prox != NULL)
    auxiliar = auxiliar->prox;
  contact->emails->qty++;
  auxiliar->prox = new_mail;
  return true;
}

bool Email_remove(Contact *contact, const char *mail) {
  if (contact == NULL)
    return false;

  // Checa se o primeiro email da lista é o email a ser removido
  if (strcmp(contact->emails->mail, mail) == 0) {
    Email *email_temp = contact->emails;
    contact->emails = email_temp->prox;
    contact->emails->qty--;
    free(email_temp);
    return true;
  }

  // Procura o email a ser removido da lista
  Email *prev = contact->emails;
  Email *current = contact->emails->prox;
  while (current != NULL) {
    if (strcmp(current->mail, mail) == 0) {
      prev->prox = current->prox;
      contact->emails->qty--;
      free(current);
      return true;
    }
    prev = current;
    current = current->prox;
  }

  printf("\nEmail nao encontrado\n");
  return false;
}

Email *Email_find(Contact *contact, const char *mailaddress) {
  if (contact == NULL)
    return NULL;
  if (strcmp(contact->emails->mail, mailaddress) == 0) {
    return contact->emails;
  }
  Email *prev = contact->emails;
  Email *current = prev->prox;
  while (current != NULL) {
    if (strcmp(current->mail, mailaddress) == 0) {
      return current;
    }
    prev = current;
    current = current->prox;
  }

  printf("\nEmail nao encontrado\n");
  return NULL;
}

bool Email_edit(Email *email_to_edit, const char *new_mail) {
  if (email_to_edit == NULL)
    return false;
  strcpy(email_to_edit->mail, new_mail);
  return true;
}

bool List_insert(List *list, const char *name, const char *cpf) {
  Contact new_contact = Contact_create(name, cpf);
  if(new_contact == NULL) {
    printf("\nFalha em criar o contato\n");
    return false;
  }
  if(strcmp(list->first_contact->cpf, cpf) == 0) {
    printf("\nO CPF deste contato ja esta inserido na lista\n");
    free(new_contact);
    return false;
  }
  

  if (list->first_contact == NULL) {
    list->first_contact = new_contact;
    return true;
  }
  Contact *auxiliar = list->first_contact;
  while (auxiliar->prox != NULL)
    if(strcmp(auxiliar->prox->cpf, new_contact->cpf) == 0) {
      printf("\nO CPF deste contato ja esta inserido na lista\n");
      free(new_contact);
      return false;
    }
    auxiliar = auxiliar->prox;
  auxiliar->prox = new_contact;
  return true;
}

bool List_remove(List *list, const char *cpf) {
  if (list->first_contact == NULL)
    return false;

  // Verifica se o primeiro contato da lista é o contato a ser removido
  if (strcmp(list->first_contact->cpf, cpf) == 0) {
    Contact *temp = list->first_contact;
    list->first_contact = list->first_contact->prox;
    free(temp);
    return true;
  }

  // Procura o contato a ser removido na lista
  Contact *prev = list->first_contact;
  Contact *current = list->first_contact->prox;
  while (current != NULL) {
    if (strcmp(current->cpf, cpf) == 0) {
      prev->prox = current->prox;
      free(current);
      return true;
    }
    prev = current;
    current = current->prox;
  }

  // O contato não foi encontrado na lista
  printf("\nContato não encontrado\n");
  return false;
}

Contact *Contact_find_by_cpf(List *list, const char *cpf) {
  if (list->first_contact == NULL) {
    printf("\nA lista esta vazia\n");
    return NULL;
  }
  if (!validateCPF(cpf)) {
    printf("\nO formato do cpf esta invalido\n");
  }
  if (strcmp(list->first_contact->cpf, cpf) == 0) {
    return list->first_contact;
  }
  Contact *aux = list->first_contact;
  while (aux != NULL) {
    if (strcmp(aux->cpf, cpf) == 0) {
      return aux;
    }
    aux = aux->prox;
  }

  printf("\n Nenhum contato encontrado \n");
  return NULL;
}

Contact *Contact_find_by_name(List *list, const char *name) {
  if (list->first_contact == NULL) {
    printf("\nA lista esta vazia\n");
    return NULL;
  }
  if (strcmp(list->first_contact->name, name) == 0) {
    return list->first_contact;
  }
  Contact *aux = list->first_contact;
  while (aux != NULL) {
    if (strcmp(aux->name, name) == 0) {
      return aux;
    }
    aux = aux->prox;
  }
  printf("\n Nenhum contato encontrado \n");
  return NULL;
}

void List_print(List *list) {
  if (list->first_contact == NULL) {
    printf("\n Nenhum contato registrado\n");
    return;
  }
  Contact *auxiliar = list->first_contact;
  while (auxiliar != NULL) {
    printf("Nome: %s\n", auxiliar->name);
    printf("CPF: %s\n", auxiliar->cpf);

    Phone *phone_aux = auxiliar->phones;
    while (phone_aux != NULL) {
      printf("Telefone: %s\n", phone_aux->number);
      phone_aux = phone_aux->prox;
    }

    Email *email_aux = auxiliar->emails;
    while (email_aux != NULL) {
      printf("Email: %s\n", email_aux->mail);
      email_aux = email_aux->prox;
    }

    printf("------------------------\n");

    auxiliar = auxiliar->prox;
  }
}

void Contact_print(Contact *contato) {
  if (contato == NULL) {
    printf("\nO contato nao foi encontrado\n");
    return;
  }
  printf("------------------------\n");
  printf("Nome: %s\n", contato->name);
  printf("CPF: %s\n", contato->cpf);

  Phone *phone_aux = contato->phones;
  while (phone_aux != NULL) {
    printf("Telefone: %s\n", phone_aux->number);
    phone_aux = phone_aux->prox;
  }

  Email *email_aux = contato->emails;
  while (email_aux != NULL) {
    printf("Email: %s\n", email_aux->mail);
    email_aux = email_aux->prox;
  }

  printf("------------------------\n");
}

bool List_sync_todb(List *list) {
  if (list->first_contact == NULL) {
    printf("\n Nenhum contato registrado\n");
    return false;
  }
  FILE *file;
  file = fopen("db.txt", "w");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return false;
  }

  Contact *auxiliar = list->first_contact;
  while (auxiliar != NULL) {
    fprintf(file, "C\n");
    fprintf(file, "%s\n", auxiliar->name);
    fprintf(file, "%s\n", auxiliar->cpf);

    Phone *phone_aux = auxiliar->phones;
    fprintf(file, "P\n");
    fprintf(file, "%d\n", auxiliar->phones->qty);
    while (phone_aux != NULL) {
      fprintf(file, "%s\n", phone_aux->number);
      phone_aux = phone_aux->prox;
    }

    Email *email_aux = auxiliar->emails;
    fprintf(file, "M\n");
    fprintf(file, "%d\n", auxiliar->emails->qty);
    while (email_aux != NULL) {
      fprintf(file, "%s\n", email_aux->mail);
      email_aux = email_aux->prox;
    }

    auxiliar = auxiliar->prox;
  }
  fclose(file);
  return true;
}

List *List_load_fromdb() {
  char *buff;
  char line[MAX_MAIL_LENGTH];
  int readingPhones = 0, readingEmails = 0;
  FILE *file;
  file = fopen("db.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }

  List *list = List_create();
  Contact *current_contact = NULL;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (line[0] == 'C') {
      char name[MAX_NAME_LENGTH], cpf[MAX_CPF_LENGTH];
      buff = fgets(name, sizeof(name), file);
      buff = fgets(cpf, sizeof(cpf), file);
      name[strcspn(name, "\n")] = '\0';
      cpf[strcspn(cpf, "\n")] = '\0';

      List_insert(list, name, cpf);
      current_contact = Contact_find_by_cpf(cpf);
    } else if (line[0] == 'P') {
      int num_phones;
      fscanf(file, "%d", &num_phones);
      fgetc(file);
      char phone[MAX_PHONE_LENGTH];
      for (int i = 0; i < num_phones; i++) {
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0;
        strcpy(phone, line);
        Phone_insert(current_contact, phone);
      }
    } else if (line[0] == 'M') {
      int num_emails;
      fscanf(file, "%d", &num_emails);
      fgetc(file);
      char email[MAX_MAIL_LENGTH];
      for (int i = 0; i < num_emails; i++) {
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0;
        strcpy(email, line);
        Email_insert(current_contact, email);
      }
    }
  }

  fclose(file);
  return list;
}

bool List_insert_by_file(List *list) {
  char *buff;
  char line[MAX_MAIL_LENGTH];
  FILE *file;
  file = fopen("novos-contatos.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return false;
  }
  Contact *new_contact;
  while (fgets(line, sizeof(line), file) != NULL) {
    if (line[0] == 'C') {
      char name[MAX_NAME_LENGTH], cpf[MAX_CPF_LENGTH];
      buff = fgets(name, sizeof(name), file);
      buff = fgets(cpf, sizeof(cpf), file);
      name[strcspn(name, "\n")] = '\0';
      cpf[strcspn(cpf, "\n")] = '\0';
      List_insert(list, name, cpf);
      new_contact = Contact_find_by_cpf(cpf);
    } else if (line[0] == 'P') {
      int num_phones;
      fscanf(file, "%d", &num_phones);
      fgetc(file);
      char phone[MAX_PHONE_LENGTH];
      for (int i = 0; i < num_phones; i++) {
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0;
        strcpy(phone, line);
        Phone_insert(new_contact, phone);
      }
    } else if (line[0] == 'M') {
      int num_emails;
      fscanf(file, "%d", &num_emails);
      fgetc(file);
      char email[MAX_MAIL_LENGTH];
      for (int i = 0; i < num_emails; i++) {
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0;
        strcpy(email, line);
        Email_insert(new_contact, email);
      }
    }
  }

  fclose(file);
  return true;
}

bool List_remove_by_file(List *list) {
  char line[MAX_CPF_LENGTH];
  FILE *file;
  file = fopen("excluir-contatos.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return false;
  }

  int num_cpfs;
  fscanf(file, "%d", &num_cpfs);
  fgetc(file); // Consumir o caractere de nova linha após o número

  for (int i = 0; i < num_cpfs; i++) {
    fgets(line, sizeof(line), file);
    fgetc(file);
    line[strcspn(line, "\n")] = '\0';

    if (validateCPF(line)) {
      if (List_remove(list, line)) {
        printf("%s removido com sucesso\n", line);
      } else {
        printf("Falha ao remover %s\n", line);
      }
    } else {
      printf("CPF (%s) possui formato inválido\n", line);
    }
  }

  fclose(file);
  return true;
}

List *List_query_by_file(List *list) {
  char line[MAX_CPF_LENGTH];
  FILE *file;
  fopen("busca-contatos.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }
  List *aux = List_create();
  while (fgets(line, sizeof(line), file)) {
    int num_cpfs;
    fscanf(file, "%d", &num_cpfs);
    fgetc(file);
    char cpf[MAX_CPF_LENGTH];
    for (int i = 0; i < num_cpfs; i++) {
      fgets(line, sizeof(line), file);
      line[strcspn(line, "\n")] = 0;
      strcpy(cpf, line);
      if (validateCPF(cpf)) {
        Contact *aux_contact = Contact_find_by_cpf(list, cpf);
        List_insert(aux, aux_contact->name,  aux_contact->cpf);
      } else {
        printf("\nFormato de cpf invalido");
      }
    }
  }
  return aux;
}

// Validação de entrada

bool validateCPF(const char *cpf) {
  // Verificar se a string tem o tamanho correto
  if (strlen(cpf) != 14) {
    return false;
  }
  // Verificar se os caracteres nos índices esperados são dígitos e se os
  // separadores estão corretos
  for (int i = 0; i < 14; i++) {
    if (i == 3 || i == 7 || i == 11) {
      if (cpf[i] != '-') {
        return false;
      }
    } else {
      if (!isdigit(cpf[i])) {
        return false;
      }
    }
  }
  return true;
}

bool validatePhoneNumber(const char *phoneNumber) {
  regex_t regex;
  int reti;

  // Expressão regular para o padrão "+55 99 99999-9999"
  char *pattern = "^\\+55[0-9]{2}[0-9]{5}-[0-9]{4}$";

  // Compilar a expressão regular
  reti = regcomp(&regex, pattern, REG_EXTENDED);
  if (reti != 0) {
    printf("Falha ao compilar a expressão regular\n");
    return false;
  }

  // Executar a correspondência da expressão regular
  reti = regexec(&regex, phoneNumber, 0, NULL, 0);
  if (reti == 0) {
    // Correspondeu ao padrão
    regfree(&regex);
    return true;
  } else {
    // Não correspondeu ao padrão
    regfree(&regex);
    return false;
  }
}

bool validateEmail(const char *email) {
  // Verificar se a string tem pelo menos 3 caracteres
  if (strlen(email) < 3) {
    return false;
  }
  // Verificar se há um único símbolo '@'
  int atSymbolCount = 0;
  for (int i = 0; i < strlen(email); i++) {
    if (email[i] == '@') {
      atSymbolCount++;
    }
  }
  if (atSymbolCount != 1) {
    return false;
  }
  // Verificar se o primeiro e último caracteres não são '@'
  if (email[0] == '@' || email[strlen(email) - 1] == '@') {
    return false;
  }
  // Verificar se há um único ponto após o '@'
  int dotAfterAtSymbolCount = 0;
  for (int i = 0; i < strlen(email); i++) {
    if (email[i] == '.' && i > 0 && i < strlen(email) - 1 &&
        email[i - 1] != '@' && email[i + 1] != '@') {
      dotAfterAtSymbolCount++;
    }
  }
  if (dotAfterAtSymbolCount != 1) {
    return false;
  }
  return true;
}