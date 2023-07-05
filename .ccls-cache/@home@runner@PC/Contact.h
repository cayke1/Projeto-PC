#ifndef CONTACT_H
#define CONTACT_H
#define MAX_NAME_LENGTH 100
#define MAX_CPF_LENGTH 15
#define MAX_PHONE_LENGTH 20
#define MAX_MAIL_LENGTH 100
#include <stdbool.h>
#include <stdio.h>

typedef struct Phone {
  char number[MAX_PHONE_LENGTH];
  struct Phone *prox;
  unsigned int qty;
} Phone;

typedef struct Email {
  char mail[MAX_MAIL_LENGTH];
  struct Email *prox;
  unsigned int qty;
} Email;

typedef struct Contact {
  char name[MAX_NAME_LENGTH];
  char cpf[MAX_CPF_LENGTH];
  Phone *phones;
  Email *emails;
  struct Contact *prox;
} Contact;

typedef struct _list {
  Contact *first_contact;
} List;

List *List_create();

/**
 * Cria instâncias de contato.
 * @param name Nome do contato
 * @param cpf CPF do contato
 * @return Ponteiro para a instância de contato criada
 */
Contact *Contact_create(const char *name, const char *cpf);

/**
 * Tenta editar nome de um contato.
 * @param Contact contato a ser editado.
 * @param name Nome a ser inserido
 @return true caso a edição aconteça, false caso contrário.
*/
bool Contact_edit_name(Contact *, const char *name);

/**
 * Tenta editar cpf de um contato.
 * @param Contact contato a ser editado.
 * @param cpf CPF a ser inserido
 @return true caso a edição aconteça, false caso contrário.
*/
bool Contact_edit_cpf(Contact *, const char *cpf);

/**
 * Tenta inserir um telefone no contato.
 * @param contact Ponteiro para a instância de contato
 * @param phone Número de telefone a ser inserido
 * @return true se o telefone foi inserido com sucesso, false caso contrário
 */
bool Phone_insert(Contact *, const char *phone);

/**
 * Tenta remover um telefone do contato.
 * @param contact Ponteiro para a instância de contato
 * @param phone Número de telefone a ser removido
 * @return true se o telefone foi removido com sucesso, false caso contrário
 */
bool Phone_remove(Contact *, const char *phone);

Phone *Phone_find(Contact *, const char *phone_number);

bool Phone_edit(Phone *phone_to_edit, const char *new_number);

/**
 * Tenta inserir um email no contato.
 * @param contact Ponteiro para a instância de contato
 * @param mail Endereço de email a ser inserido
 * @return true se o email foi inserido com sucesso, false caso contrário
 */
bool Email_insert(Contact *, const char *mail);

/**
 * Tenta remover um email do contato.
 * @param contact Ponteiro para a instância de contato.
 * @param mail Endereço de email a ser removido.
 * @return true se o email foi removido com sucesso, false caso contrário.
 */
bool Email_remove(Contact *, const char *mail);

Email *Email_find(Contact *, const char *mailaddress);

bool Email_edit(Email *email_to_edit, const char *new_mail);

/**
 * Insere um novo contato na agenda.
 * @param List Agenda.
 * @param Contact Contato a ser inserido.
 * @return true se o contato foi inserido com sucesso, false caso contrário
 */
bool List_insert(List *, Contact *);

/**
 * Remove um contato da agenda.
 * @param List Agenda.
 * @param cpf CPF do contato a ser removido.
 * @return true se o contato foi removido com sucesso, false caso contrário
 */

bool List_remove(List *, const char *cpf);

/**
 * Tenta encontrar um contato na agenda.
 * @param List Agenda.
 * @param cpf CPF do contato que se deseja encontrar.
 * @return Contact se o contato for encontrado, NULL caso contrário.
 */

Contact *Contact_find_by_cpf(List *, const char *cpf);

/**
 * Tenta encontrar um contato na agenda.
 * @param List Agenda.
 * @param name Nome do contato que se deseja encontrar.
 * @return Contact se o contato for encontrado, NULL caso contrário.
 */

Contact *Contact_find_by_name(List *, const char *name);

/**
 * Imprime a lista de contatos.
 * @param List Agenda.
 */
void List_print(List *);

/**
 * Imprime um contato.
 * @param Contact contato a ser imprimido.
 */
void Contact_print(Contact *);

/**
 * Tenta sincronizar a lista de contatos para um "banco de dados" local.
 * @param List lista a ser sincronizada
 * @return true se a sincronização foi bem-sucedida, false caso contrário
 */
bool List_sync_todb(List *);

/**
 * Tenta sincronizar a lista de contatos de um banco de dados local.
 * @return Lista sincronizada se a operação for bem-sucedida, NULL caso
 * contrário
 */
List *List_load_fromdb();

/**
 * Tenta inserir um ou mais contatos da lista informados por um arquivo txt
 * local.
 * @param List lista no qual os contatos devem ser inseridos
 * @return true caso a operação seja bem-sucedida, false caso contrário
 */

bool List_insert_by_file(List *);

bool List_remove_by_file(List *);

List *List_query_by_file(List *);

// Validação de entrada

bool validateCPF(const char *cpf);

bool validatePhoneNumber(const char *phoneNumber);

bool validateEmail(const char *email);

#endif /* CONTACT_H */
