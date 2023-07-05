#include <stdio.h>
#include <string.h>


int main(void) {
  char phone[20];
  //+551199999-9999

  scanf("%s", phone);
  insert_spaces_in_phone(phone);
  printf("%s", phone);
  return 0;
}