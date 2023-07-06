#include "Contact.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void invalid_input() { printf("\nEscolha uma entrada valida\n"); }

void manual_insert(List *list) {
  char name[MAX_NAME_LENGTH], cpf[MAX_CPF_LENGTH], phone[MAX_PHONE_LENGTH],
      email[MAX_MAIL_LENGTH];
  int n = 1, e = 1;

  printf("\nDigite o nome do contato: ");
  scanf("%s", name);
  printf("\nDigite o cpf do contato: ");
  scanf("%s", cpf);
  while (!validateCPF(cpf)) {
    printf("\n CPF invalido, tente novamente \n");
    printf("\nDigite o cpf do contato: ");
    scanf("%s", cpf);
  }
  if(!List_insert(list, name, cpf)) {
    printf("\nFalha ao criar contato\n");
    return;
  } 
  Contact *created_contact = Contact_find_by_cpf(cpf);
  while (n == 1) {
    printf("\nDigte o numero do contato: ");
    scanf("%s", phone);
    while (!validatePhoneNumber(phone)) {
      printf("\nNumero de telefone invalido, tente novamente: ");
      scanf("%s", phone);
    }
    Phone_insert(created_contact, phone);
    printf("\nDeseja inserir mais numeros de telefone?");
    printf("\n1 - Sim");
    printf("\n2 - Nao\n");
    scanf("%d", &n);
    if (n != 1 && n != 2) {
      invalid_input();
    }

    printf("\nDigte o email do contato: ");
    scanf("%s", email);
    if (!validateEmail(email)) {
      printf("\nEmail invalido, tente novamente\n");
      printf("\nDigte o email do contato: ");
      scanf("%s", email);
    }
    Email_insert(created_contact, email);
    printf("\nDeseja inserir mais emails?");
    printf("\n1 - Sim");
    printf("\n2 - Nao\n");
    scanf("%d", &e);
    if (e != 1 && e != 2) {
      invalid_input();
    }
  }
}

void insert_by_file(List *list) { List_insert_by_file(list); }

void manual_remove(List *list) {
  char cpf[MAX_CPF_LENGTH];
  printf("\nInforme o CPF do contato que deseja remover: ");
  scanf("%s", cpf);
  while (!validateCPF(cpf)) {
    printf("\nInforme um CPF valido\n");
    scanf("%s", cpf);
  }
  List_remove(list, cpf);
}

void remove_by_file(List *list) { List_remove_by_file(list); };

void manual_query(List *list) {
  int option, n = 1;
  char cpf[MAX_CPF_LENGTH], name[MAX_NAME_LENGTH];
  printf("\nComo deseja buscar o contato?");
  printf("\n1 - CPF");
  printf("\n2 - Nome");
  scanf("%d", &option);
  switch (option) {
  case 1: {
    while (n == 1) {
      printf("\n Insira o CPF do contato: ");
      scanf("%s", cpf);
      if (!validateCPF(cpf)) {
        printf("\nFormato de cpf invalido");
        return;
      }
      Contact *aux = Contact_find_by_cpf(list, cpf);
      Contact_print(aux);

      printf("\n Deseja buscar mais algum contato?");
      printf("\n1 - Sim");
      printf("\n2 - Nao\n");
      scanf("%d", &n);
      if (n != 1 && n != 2) {
        invalid_input();
        break;
      }
    }
  }
  case 2: {
    while (n == 1) {
      printf("\n Insira o nome do contato: ");
      scanf("%s", name);
      Contact *aux = Contact_find_by_name(list, name);
      Contact_print(aux);

      printf("\n Deseja buscar mais algum contato?");
      printf("\n1 - Sim");
      printf("\n2 - Nao\n");
      scanf("%d", &n);
      if (n != 1 && n != 2) {
        invalid_input();
        break;
      }
    }
  }
  default: {
    invalid_input();
    manual_query(list);
    break;
  }
  }
}

void query_by_file(List *list) {
  List *aux = List_query_by_file(list);
  if (aux != NULL)
    List_print(aux);
}

void contact_edit(List *list) {
  char cpf[MAX_CPF_LENGTH];
  int option;
  printf("\n Primeiro, insira o cpf do contato que deseja editar: ");
  scanf("%s", cpf);
  if (!validateCPF(cpf)) {
    printf("\n Formato de cpf invalido");
    contact_edit(list);
  }

  Contact *contact_to_edit = Contact_find_by_cpf(list, cpf);

  printf("\n Contato encontrado, confirme se este é o contato que deseja "
         "editar\n");
  Contact_print(contact_to_edit);
  printf("\n1 - Sim, este é o contato que desejo editar");
  printf("\n2 - Nao, buscar novamente\n");
  scanf("%d", &option);
  switch (option) {
  case 1: {
    int case1_option;
    printf("\n O que deseja editar no Contato? ");
    printf("\n 1 - Nome");
    printf("\n 2 - CPF");
    printf("\n 3 - Telefone(s)");
    printf("\n 4 - Email(s)\n");
    scanf("%d", &case1_option);
    switch (case1_option) {
    case 1: {
      char name[MAX_NAME_LENGTH];
      printf("\n Insira o novo nome do contato: ");
      scanf("%s", name);
      if (Contact_edit_name(contact_to_edit, name)) {
        int edit_again_opt;
        Contact_print(contact_to_edit);
        printf("\n Deseja editar um contato novamente? ");
        printf("\n 1 - Sim");
        printf("\n 2 - Nao");
        scanf("%d", &edit_again_opt);
        if (edit_again_opt == 1) {
          contact_edit(list);
        }
        if (edit_again_opt != 1 && edit_again_opt != 2) {
          invalid_input();
          break;
        }
        break;
      }
      break;
    }
    case 2: {
      char cpf[MAX_CPF_LENGTH];
      printf("\n Insira o novo cpf do contato: ");
      scanf("%s", cpf);
      while (!validateCPF(cpf)) {
        printf("\n Formato de CPF invalido, insira novamente: ");
        scanf("%s", cpf);
      }
      if (Contact_edit_cpf(contact_to_edit, cpf)) {
        int edit_again_opt;
        Contact_print(contact_to_edit);
        printf("\n Deseja editar um contato novamente? ");
        printf("\n 1 - Sim");
        printf("\n 2 - Nao");
        scanf("%d", &edit_again_opt);
        if (edit_again_opt == 1) {
          contact_edit(list);
        }
        if (edit_again_opt != 1 && edit_again_opt != 2) {
          invalid_input();
          break;
        }
        break;
      }
      break;
    }
    case 3: {
      int n = 1;
      char phone_to_edit[MAX_PHONE_LENGTH], new_number[MAX_PHONE_LENGTH];
      while (n == 1) {
        printf("\n Insira o Telefone que deseja editar: ");
        scanf("%s", phone_to_edit);
        while (!validatePhoneNumber(phone_to_edit)) {
          printf("\n Formato de telefone invalido, insira novamente: ");
          scanf("%s", phone_to_edit);
        }
        printf("\n%s\n", phone_to_edit);
        Phone *aux = Phone_find(contact_to_edit, phone_to_edit);
        if (aux == NULL)
          break;
        printf("\n Insira o novo Telefone: ");
        scanf("%s", new_number);
        while (!validatePhoneNumber(new_number)) {
          printf("\n Formato de telefone invalido, insira novamente: ");
          scanf("%s", new_number);
        }
        Phone_edit(aux, new_number);
        printf("\n Deseja editar outro telefone deste contato?");
        printf("\n 1 - Sim");
        printf("\n 2 - Nao\n");
        scanf("%d", &n);
        if (n != 1 && n != 2) {
          invalid_input();
        }
      }
      break;
    }
    case 4: {
      int n = 1;
      char email_to_edit[MAX_MAIL_LENGTH], new_mail[MAX_MAIL_LENGTH];
      while (n == 1) {
        printf("\n Insira o Email que deseja editar: ");
        scanf("%s", email_to_edit);
        while (!validateEmail(email_to_edit)) {
          printf("\n Formato de email invalido, insira novamente: ");
          scanf("%s", email_to_edit);
        }
        Email *aux = Email_find(contact_to_edit, email_to_edit);
        if (aux == NULL) {
          break;
        }
        printf("\n Insira o novo Email: ");
        scanf("%s", new_mail);
        while (!validateEmail(new_mail)) {
          printf("\n Formato de email invalido, insira novamente: ");
          scanf("%s", new_mail);
        }
        Email_edit(aux, new_mail);
        printf("\n Deseja editar outro email deste contato?");
        printf("\n 1 - Sim");
        printf("\n 2 - Nao\n");
        scanf("%d", &n);
        if (n != 1 && n != 2) {
          invalid_input();
        }
      }
      break;
    }
    default: {
      invalid_input();
      contact_edit(list);
      break;
    }
    }
    break;
  }
  case 2: {
    contact_edit(list);
    break;
  }
  default: {
    invalid_input();
    contact_edit(list);
    break;
  }
  }
}

int main(void) {
  int option, n = 1;
  List *agenda = List_create();
  agenda = List_load_fromdb();
  while (n == 1) {
    printf("\n\nAgenda\n");
    printf("\nMenu\n");
    printf("1 - Adicionar Contato\n");
    printf("2 - Remover Contato\n");
    printf("3 - Selecionar Contato(s)\n");
    printf("4 - Editar Contatos\n");
    printf("5 - Imprimir Lista Completa\n");
    printf("6 - Sair \n");

    scanf("%d", &option);
    switch (option) {
    case 1: {
      int case1_option;
      printf("\nComo deseja adicionar Contatos?\n");
      printf("1 - Adicionar manualmente\n");
      printf("2 - Adicionar por arquivo\n");
      scanf("%d", &case1_option);
      switch (case1_option) {
      case 1: {
        manual_insert(agenda);
        break;
      }
      case 2: {
        insert_by_file(agenda);
        List_print(agenda);
        break;
      }
      default: {
        invalid_input();
        break;
      }
      }
      break;
    }
    case 2: {
      int case2_option;
      printf("\nComo deseja remover Contatos?\n");
      printf("1 - Remover manualmente\n");
      printf("2 - Remover por arquivo\n");
      scanf("%d", &case2_option);
      switch (case2_option) {
      case 1: {
        manual_remove(agenda);
        break;
      }
      case 2: {
        remove_by_file(agenda);
        break;
      }
      default: {
        invalid_input();
        break;
      }
      }
      break;
    }
    case 3: {
      int case3_option;
      printf("\nComo deseja buscar por Contatos?");
      printf("\n1 - Buscar manualmente");
      printf("\n2 - Buscar por arquivo\n");
      scanf("%d", &case3_option);
      switch (case3_option) {
      case 1: {
        manual_query(agenda);
        break;
      }
      case 2: {
        query_by_file(agenda);
        break;
      }
      default: {
        invalid_input();
        break;
      }
      }
      break;
    }
    case 4: {
      contact_edit(agenda);
      break;
    }
    case 5: {
      List_print(agenda);
      break;
    }
    case 6: {
      n = 2;
      break;
    }
    default: {
      invalid_input();
      break;
    }
    }
  }
  List_sync_todb(agenda);
  printf("\nFechando programa...\n");
  return 0;
}