#ifndef CONTACT_H
#define CONTACT_H
#include <stdbool.h>

typedef struct phone {
  char number[15];
  struct phone *prox;
} Phone;

typedef struct email {
  char mail[50];
  struct email *prox;
} Email;

typedef struct _contact {
  char name[50];
  char cpf[15];
  Phone *phones;
  Email *emails;

  struct _contact *next;
} Contact;
/**
 * Cria instâncias de contato.
 * @param char* Nome do contato
 * @param char* CPF do contato
 * @return Contact*
 */
Contact *Contact_create(const char *, const char *);
/**
 * Tenta inserir um telefone no contato
 * @param Contact* instância de um contato
 * @param Char numero que se deseja inserir no contato
 * @return bool (true em caso de sucesso, false para caso de falha)
 */
bool Phone_insert(Contact *, const char *);

/**
 * Tenta inserir um email no contato
 * @param Contact* instância de um contato
 * @param Char email que se deseja inserir no contato
 * @return bool (true em caso de sucesso, false para caso de falha)
 */
bool Email_insert(Contact *, const char *);

/**
 * Cria instâncias de contato.
 * @param char* Nome do contato
 * @param char* CPF do contato
 * @return Contact*
 */
bool Contact_insert(const char *, const char *);
/**
 * Imprime a lista de Contatos.
 */
void List_print();
/**
 * Tenta sincronizar a lista com um "banco de dados" local
 */
bool List_sync();
#endif