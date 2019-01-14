/*
Copyright (c) 2019 Steffen Illhardt

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "uni_deque.h"

typedef  struct ud_element  * ud_element_t;

struct ud_element
{
    ud_element_t    previous;
    ud_element_t    next;
    void          * data;
};

struct ud_detail
{
    ud_element_t  head;
    ud_element_t  tail;
    ud_size_t     size;
    int           err;
};


int CmpAscC(const char *p_1, const char *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescC(const char *p_1, const char *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscSC(const signed char *p_1, const signed char *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescSC(const signed char *p_1, const signed char *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscUC(const unsigned char *p_1, const unsigned char *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescUC(const unsigned char *p_1, const unsigned char *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscS(const short *p_1, const short *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescS(const short *p_1, const short *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscUS(const unsigned short *p_1, const unsigned short *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescUS(const unsigned short *p_1, const unsigned short *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscI(const int *p_1, const int *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescI(const int *p_1, const int *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscUI(const unsigned int *p_1, const unsigned int *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescUI(const unsigned int *p_1, const unsigned int *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscL(const long *p_1, const long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescL(const long *p_1, const long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscUL(const unsigned long *p_1, const unsigned long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescUL(const unsigned long *p_1, const unsigned long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscLL(const long long *p_1, const long long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescLL(const long long *p_1, const long long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscULL(const unsigned long long *p_1, const unsigned long long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescULL(const unsigned long long *p_1, const unsigned long long *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscF(const float *p_1, const float *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescF(const float *p_1, const float *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscD(const double *p_1, const double *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescD(const double *p_1, const double *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscLD(const long double *p_1, const long double *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 > *p_2 ? 1 : -1);
}

int CmpDescLD(const long double *p_1, const long double *p_2)
{
  return *p_1 == *p_2 ? 0 : (*p_1 < *p_2 ? 1 : -1);
}

int CmpAscStr(const char *p_1, const char *p_2)
{
  return strcmp(p_1, p_2);
}

int CmpDescStr(const char *p_1, const char *p_2)
{
  return strcmp(p_2, p_1);
}

int CmpAscWStr(const wchar_t *p_1, const wchar_t *p_2)
{
  return wcscmp(p_1, p_2);
}

int CmpDescWStr(const wchar_t *p_1, const wchar_t *p_2)
{
  return wcscmp(p_2, p_1);
}


ud_t UDOpen()
{
  return (ud_t)calloc(1u, sizeof(struct ud_detail));
}

void *UDPushFront(const ud_t deq, const void *const p_data, const size_t data_size)
{
  ud_element_t new_element = NULL;
  void *new_data = NULL;
  if ((new_element = (ud_element_t)malloc(sizeof(struct ud_element))) == NULL || (new_data = malloc(data_size)) == NULL)
  {
    deq->err = 1;
    free(new_element);
    return NULL;
  }

  new_element->data = memcpy(new_data, p_data, data_size);
  deq->head != NULL ? (deq->head->previous = new_element) : (deq->tail = new_element);
  new_element->next = deq->head;
  new_element->previous = NULL;
  deq->head = new_element;
  ++deq->size;
  deq->err = 0;
  return new_data;
}

void *UDFront(const ud_t deq)
{
  if (deq->head == NULL)
  {
    deq->err = 1;
    return NULL;
  }

  deq->err = 0;
  return deq->head->data;
}

void *UDPopFront(const ud_t deq)
{
  if (deq->head == NULL)
  {
    deq->err = 1;
    return NULL;
  }

  --deq->size;
  void *data = deq->head->data;
  ud_element_t new_head = deq->head->next;
  free(deq->head);
  deq->head = new_head;
  new_head != NULL ? (new_head->previous = NULL) : (deq->tail = NULL);
  deq->err = 0;
  return data;
}

void *UDPushBack(const ud_t deq, const void *const p_data, const size_t data_size)
{
  ud_element_t new_element = NULL;
  void *new_data = NULL;
  if ((new_element = (ud_element_t)malloc(sizeof(struct ud_element))) == NULL || (new_data = malloc(data_size)) == NULL)
  {
    deq->err = 1;
    free(new_element);
    return NULL;
  }

  new_element->data = memcpy(new_data, p_data, data_size);
  deq->tail != NULL ? (deq->tail->next = new_element) : (deq->head = new_element);
  new_element->previous = deq->tail;
  new_element->next = NULL;
  deq->tail = new_element;
  ++deq->size;
  deq->err = 0;
  return new_data;
}

void *UDBack(const ud_t deq)
{
  if (deq->tail == NULL)
  {
    deq->err = 1;
    return NULL;
  }

  deq->err = 0;
  return deq->tail->data;
}

void *UDPopBack(const ud_t deq)
{
  if (deq->tail == NULL)
  {
    deq->err = 1;
    return NULL;
  }

  --deq->size;
  void *data = deq->tail->data;
  ud_element_t new_tail = deq->tail->previous;
  free(deq->tail);
  deq->tail = new_tail;
  new_tail != NULL ? (new_tail->next = NULL) : (deq->head = NULL);
  deq->err = 0;
  return data;
}

void *UDInsert(const ud_t deq, const ud_size_t index, const void *const p_data, const size_t data_size)
{
  ud_element_t new_element = NULL;
  void *new_data = NULL;
  if (index >= deq->size || (new_element = (ud_element_t)malloc(sizeof(struct ud_element))) == NULL || (new_data = malloc(data_size)) == NULL)
  {
    deq->err = 1;
    free(new_element);
    return NULL;
  }

  new_element->data = memcpy(new_data, p_data, data_size);
  ud_size_t tail_distance = deq->size - index - 1;
  ud_element_t current_element = tail_distance < index ? deq->tail : deq->head;
  for (ud_size_t i = tail_distance < index ? tail_distance : index; i-- > 0; )
    current_element = tail_distance < index ? current_element->previous : current_element->next;

  current_element->previous == NULL ? (deq->head = new_element) : (current_element->previous->next = new_element);
  new_element->previous = current_element->previous;
  new_element->next = current_element;
  current_element->previous = new_element;
  ++deq->size;
  deq->err = 0;
  return new_data;
}

void *UDAt(const ud_t deq, const ud_size_t index)
{
  if (index >= deq->size)
  {
    deq->err = 1;
    return NULL;
  }

  ud_size_t tail_distance = deq->size - index - 1;
  ud_element_t current_element = tail_distance < index ? deq->tail : deq->head;
  for (ud_size_t i = tail_distance < index ? tail_distance : index; i-- > 0; )
    current_element = tail_distance < index ? current_element->previous : current_element->next;

  deq->err = 0;
  return current_element->data;
}

void *UDErase(const ud_t deq, const ud_size_t index)
{
  if (index >= deq->size)
  {
    deq->err = 1;
    return NULL;
  }

  ud_size_t tail_distance = --deq->size - index;
  ud_element_t current_element = tail_distance < index ? deq->tail : deq->head;
  for (ud_size_t i = tail_distance < index ? tail_distance : index; i-- > 0; )
    current_element = tail_distance < index ? current_element->previous : current_element->next;

  void *data = current_element->data;
  current_element->previous != NULL ? (current_element->previous->next = current_element->next) : (deq->head = current_element->next);
  current_element->next != NULL ? (current_element->next->previous = current_element->previous) : (deq->tail = current_element->previous);
  free(current_element);
  deq->err = 0;
  return data;
}

int UDForEach(const ud_t deq, const ud_size_t start_idx, const ud_ssize_t number, ud_for_each_proc_t callback_func, void *user_parameter)
{
  if (number == 0 || start_idx >= deq->size || start_idx + number + (number < 0 ? 1 : -1) >= deq->size)
  {
    deq->err = 1;
    return 0;
  }

  ud_size_t tail_distance = deq->size - start_idx - 1;
  ud_element_t current_element = tail_distance < start_idx ? deq->tail : deq->head;
  for (ud_size_t i = tail_distance < start_idx ? tail_distance : start_idx; i-- > 0; )
    current_element = tail_distance < start_idx ? current_element->previous : current_element->next;

  for (ud_size_t i = number < 0 ? -number : number; i-- > 0; )
  {
    if (current_element == NULL)
    {
      deq->err = 1;
      return 0;
    }

    if (callback_func(current_element->data, user_parameter) == 0)
      break;

    current_element = number < 0 ? current_element->previous : current_element->next;
  }

  deq->err = 0;
  return 1;
}

int UDSort(const ud_t deq, ud_cmp_t cmp_callback_func)
{
  if (deq->size == 0u)
  {
    deq->err = 1;
    return 0;
  }

  ud_element_t front = deq->head, back = NULL, left = NULL, right = NULL;
  for (ud_size_t max_extent = 1u, l_extent = 0u, r_extent = 0u, merge_cnt = UINT64_MAX; merge_cnt > 1u; back->next = NULL, max_extent <<= 1u)
  {
    for (merge_cnt = 0u, left = right = front, front = back = NULL ;left != NULL; ++merge_cnt, left = right)
    {
      for (l_extent = 1u, r_extent = max_extent, right = left->next; l_extent < max_extent && right != NULL; ++l_extent, right = right->next);
      for (ud_element_t picked = NULL; l_extent != 0u || (r_extent != 0u && right != NULL); back == NULL ? (front = picked) : (back->next = picked), picked->previous = back, back = picked)
      {
        if (l_extent != 0u && (r_extent == 0u || right == NULL || cmp_callback_func(left->data, right->data) < 1))
        {
          --l_extent;
          picked = left;
          left = left->next;
        }
        else
        {
          --r_extent;
          picked = right;
          right = right->next;
        }
      }
    }
  }

  deq->head = front;
  deq->tail = back;
  deq->err = 0;
  return 1;
}

void *UDInsertSorted(const ud_t deq, const void *const p_data, const size_t data_size, ud_cmp_t cmp_callback_func)
{
  if (deq->size == 0u || cmp_callback_func(p_data, deq->head->data) < 1)
    return UDPushFront(deq, p_data, data_size);

  if (cmp_callback_func(p_data, deq->tail->data) > -1)
    return UDPushBack(deq, p_data, data_size);

  ud_element_t new_element = NULL;
  void *new_data = NULL;
  if ((new_element = (ud_element_t)malloc(sizeof(struct ud_element))) == NULL || (new_data = malloc(data_size)) == NULL)
  {
    deq->err = 1;
    free(new_element);
    return NULL;
  }

  new_element->data = memcpy(new_data, p_data, data_size);
  ud_element_t current_element = deq->head->next;
  for ( ; current_element != deq->tail && cmp_callback_func(current_element->data, p_data) < 0; current_element = current_element->next);
  current_element->previous->next = new_element;
  new_element->previous = current_element->previous;
  new_element->next = current_element;
  current_element->previous = new_element;
  ++deq->size;
  deq->err = 0;
  return new_data;
}

ud_size_t UDFind(const ud_t deq, const void *const p_data, ud_cmp_t cmp_callback_func)
{
  ud_size_t index = 0u;
  for (ud_element_t current_element = deq->head; current_element != NULL; current_element = current_element->next, ++index)
  {
    if (cmp_callback_func(p_data, current_element->data) == 0)
    {
      deq->err = 0;
      return index;
    }
  }

  deq->err = 1;
  return UD_INVALID_IDX;
}

void *UDRemove(const ud_t deq, const void *const p_data, ud_cmp_t cmp_callback_func)
{
  for (ud_element_t current_element = deq->head; current_element != NULL; current_element = current_element->next)
  {
    if (cmp_callback_func(p_data, current_element->data) == 0)
    {
      --deq->size;
      void *data = current_element->data;
      current_element->previous != NULL ? (current_element->previous->next = current_element->next) : (deq->head = current_element->next);
      current_element->next != NULL ? (current_element->next->previous = current_element->previous) : (deq->tail = current_element->previous);
      free(current_element);
      deq->err = 0;
      return data;
    }
  }

  deq->err = 1;
  return NULL;
}

int UDReverse(const ud_t deq)
{
  if (deq->size == 0u)
  {
    deq->err = 1;
    return 0;
  }

  ud_element_t tmp = NULL;
  for (ud_element_t current_element = deq->head; current_element != NULL; current_element = tmp)
  {
    tmp = current_element->next;
    current_element->next = current_element->previous;
    current_element->previous = tmp;
  }

  tmp = deq->head;
  deq->head = deq->tail;
  deq->tail = tmp;
  deq->err = 0;
  return 1;
}

ud_size_t UDSize(const ud_t deq)
{
  deq->err = 0;
  return deq->size;
}

int UDEmpty(const ud_t deq)
{
  deq->err = 0;
  return deq->size == 0u;
}

int UDFailed(const ud_t deq)
{
  int current_err = deq->err;
  deq->err = 0;
  return current_err;
}

void UDDeleteData(const ud_t deq, void *p_data)
{
  deq->err = 0;
  free(p_data);
}

void UDClose(ud_t deq)
{
  if (deq != NULL)
  {
    ud_element_t element = deq->head;
    while (element != NULL)
    {
      ud_element_t next = element->next;
      free(element->data);
      free(element);
      element = next;
    }

    free(deq);
  }
}

char *UDPushFrontC(const ud_t deq, const char value)
{
  return (char *)UDPushFront(deq, &value, sizeof(value));
}

signed char *UDPushFrontSC(const ud_t deq, const signed char value)
{
  return (signed char *)UDPushFront(deq, &value, sizeof(value));
}

unsigned char *UDPushFrontUC(const ud_t deq, const unsigned char value)
{
  return (unsigned char *)UDPushFront(deq, &value, sizeof(value));
}

short *UDPushFrontS(const ud_t deq, const short value)
{
  return (short *)UDPushFront(deq, &value, sizeof(value));
}

unsigned short *UDPushFrontUS(const ud_t deq, const unsigned short value)
{
  return (unsigned short *)UDPushFront(deq, &value, sizeof(value));
}

int *UDPushFrontI(const ud_t deq, const int value)
{
  return (int *)UDPushFront(deq, &value, sizeof(value));
}

unsigned int *UDPushFrontUI(const ud_t deq, const unsigned int value)
{
  return (unsigned int *)UDPushFront(deq, &value, sizeof(value));
}

long *UDPushFrontL(const ud_t deq, const long value)
{
  return (long *)UDPushFront(deq, &value, sizeof(value));
}

unsigned long *UDPushFrontUL(const ud_t deq, const unsigned long value)
{
  return (unsigned long *)UDPushFront(deq, &value, sizeof(value));
}

long long *UDPushFrontLL(const ud_t deq, const long long value)
{
  return (long long *)UDPushFront(deq, &value, sizeof(value));
}

unsigned long long *UDPushFrontULL(const ud_t deq, const unsigned long long value)
{
  return (unsigned long long *)UDPushFront(deq, &value, sizeof(value));
}

float *UDPushFrontF(const ud_t deq, const float value)
{
  return (float *)UDPushFront(deq, &value, sizeof(value));
}

double *UDPushFrontD(const ud_t deq, const double value)
{
  return (double *)UDPushFront(deq, &value, sizeof(value));
}

long double *UDPushFrontLD(const ud_t deq, const long double value)
{
  return (long double *)UDPushFront(deq, &value, sizeof(value));
}

char UDFrontC(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(char *)ptr;
}

signed char UDFrontSC(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(signed char *)ptr;
}

unsigned char UDFrontUC(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned char *)ptr;
}

short UDFrontS(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(short *)ptr;
}

unsigned short UDFrontUS(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned short *)ptr;
}

int UDFrontI(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(int *)ptr;
}

unsigned int UDFrontUI(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned int *)ptr;
}

long UDFrontL(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(long *)ptr;
}

unsigned long UDFrontUL(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned long *)ptr;
}

long long UDFrontLL(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(long long *)ptr;
}

unsigned long long UDFrontULL(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned long long *)ptr;
}

float UDFrontF(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(float *)ptr;
}

double UDFrontD(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(double *)ptr;
}

long double UDFrontLD(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  return *(long double *)ptr;
}

char UDPopFrontC(const ud_t deq)
{
  void *ptr = UDFront(deq);
  if (ptr == NULL)
    return 0;

  char val = *(char *)ptr;
  free(ptr);
  return val;
}

signed char UDPopFrontSC(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  signed char val = *(signed char *)ptr;
  free(ptr);
  return val;
}

unsigned char UDPopFrontUC(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  unsigned char val = *(unsigned char *)ptr;
  free(ptr);
  return val;
}

short UDPopFrontS(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  short val = *(short *)ptr;
  free(ptr);
  return val;
}

unsigned short UDPopFrontUS(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  unsigned short val = *(unsigned short *)ptr;
  free(ptr);
  return val;
}

int UDPopFrontI(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  int val = *(int *)ptr;
  free(ptr);
  return val;
}

unsigned int UDPopFrontUI(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  unsigned int val = *(unsigned int *)ptr;
  free(ptr);
  return val;
}

long UDPopFrontL(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  long val = *(long *)ptr;
  free(ptr);
  return val;
}

unsigned long UDPopFrontUL(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  unsigned long val = *(unsigned long *)ptr;
  free(ptr);
  return val;
}

long long UDPopFrontLL(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  long long val = *(long long *)ptr;
  free(ptr);
  return val;
}

unsigned long long UDPopFrontULL(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  unsigned long long val = *(unsigned long long *)ptr;
  free(ptr);
  return val;
}

float UDPopFrontF(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  float val = *(float *)ptr;
  free(ptr);
  return val;
}

double UDPopFrontD(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  double val = *(double *)ptr;
  free(ptr);
  return val;
}

long double UDPopFrontLD(const ud_t deq)
{
  void *ptr = UDPopFront(deq);
  if (ptr == NULL)
    return 0;

  long double val = *(long double *)ptr;
  free(ptr);
  return val;
}

char *UDPushBackC(const ud_t deq, const char value)
{
  return (char *)UDPushBack(deq, &value, sizeof(value));
}

signed char *UDPushBackSC(const ud_t deq, const signed char value)
{
  return (signed char *)UDPushBack(deq, &value, sizeof(value));
}

unsigned char *UDPushBackUC(const ud_t deq, const unsigned char value)
{
  return (unsigned char *)UDPushBack(deq, &value, sizeof(value));
}

short *UDPushBackS(const ud_t deq, const short value)
{
  return (short *)UDPushBack(deq, &value, sizeof(value));
}

unsigned short *UDPushBackUS(const ud_t deq, const unsigned short value)
{
  return (unsigned short *)UDPushBack(deq, &value, sizeof(value));
}

int *UDPushBackI(const ud_t deq, const int value)
{
  return (int *)UDPushBack(deq, &value, sizeof(value));
}

unsigned int *UDPushBackUI(const ud_t deq, const unsigned int value)
{
  return (unsigned int *)UDPushBack(deq, &value, sizeof(value));
}

long *UDPushBackL(const ud_t deq, const long value)
{
  return (long *)UDPushBack(deq, &value, sizeof(value));
}

unsigned long *UDPushBackUL(const ud_t deq, const unsigned long value)
{
  return (unsigned long *)UDPushBack(deq, &value, sizeof(value));
}

long long *UDPushBackLL(const ud_t deq, const long long value)
{
  return (long long *)UDPushBack(deq, &value, sizeof(value));
}

unsigned long long *UDPushBackULL(const ud_t deq, const unsigned long long value)
{
  return (unsigned long long *)UDPushBack(deq, &value, sizeof(value));
}

float *UDPushBackF(const ud_t deq, const float value)
{
  return (float *)UDPushBack(deq, &value, sizeof(value));
}

double *UDPushBackD(const ud_t deq, const double value)
{
  return (double *)UDPushBack(deq, &value, sizeof(value));
}

long double *UDPushBackLD(const ud_t deq, const long double value)
{
  return (long double *)UDPushBack(deq, &value, sizeof(value));
}

char UDBackC(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(char *)ptr;
}

signed char UDBackSC(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(signed char *)ptr;
}

unsigned char UDBackUC(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned char *)ptr;
}

short UDBackS(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(short *)ptr;
}

unsigned short UDBackUS(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned short *)ptr;
}

int UDBackI(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(int *)ptr;
}

unsigned int UDBackUI(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned int *)ptr;
}

long UDBackL(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(long *)ptr;
}

unsigned long UDBackUL(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned long *)ptr;
}

long long UDBackLL(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(long long *)ptr;
}

unsigned long long UDBackULL(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(unsigned long long *)ptr;
}

float UDBackF(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(float *)ptr;
}

double UDBackD(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(double *)ptr;
}

long double UDBackLD(const ud_t deq)
{
  void *ptr = UDBack(deq);
  if (ptr == NULL)
    return 0;

  return *(long double *)ptr;
}

char UDPopBackC(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  char val = *(char *)ptr;
  free(ptr);
  return val;
}

signed char UDPopBackSC(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  signed char val = *(signed char *)ptr;
  free(ptr);
  return val;
}

unsigned char UDPopBackUC(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  unsigned char val = *(unsigned char *)ptr;
  free(ptr);
  return val;
}

short UDPopBackS(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  short val = *(short *)ptr;
  free(ptr);
  return val;
}

unsigned short UDPopBackUS(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  unsigned short val = *(unsigned short *)ptr;
  free(ptr);
  return val;
}

int UDPopBackI(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  int val = *(int *)ptr;
  free(ptr);
  return val;
}

unsigned int UDPopBackUI(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  unsigned int val = *(unsigned int *)ptr;
  free(ptr);
  return val;
}

long UDPopBackL(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  long val = *(long *)ptr;
  free(ptr);
  return val;
}

unsigned long UDPopBackUL(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  unsigned long val = *(unsigned long *)ptr;
  free(ptr);
  return val;
}

long long UDPopBackLL(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  long long val = *(long long *)ptr;
  free(ptr);
  return val;
}

unsigned long long UDPopBackULL(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  unsigned long long val = *(unsigned long long *)ptr;
  free(ptr);
  return val;
}

float UDPopBackF(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  float val = *(float *)ptr;
  free(ptr);
  return val;
}

double UDPopBackD(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  double val = *(double *)ptr;
  free(ptr);
  return val;
}

long double UDPopBackLD(const ud_t deq)
{
  void *ptr = UDPopBack(deq);
  if (ptr == NULL)
    return 0;

  long double val = *(long double *)ptr;
  free(ptr);
  return val;
}

char *UDInsertC(const ud_t deq, const ud_size_t index, const char value)
{
  return (char *)UDInsert(deq, index, &value, sizeof(value));
}

signed char *UDInsertSC(const ud_t deq, const ud_size_t index, const signed char value)
{
  return (signed char *)UDInsert(deq, index, &value, sizeof(value));
}

unsigned char *UDInsertUC(const ud_t deq, const ud_size_t index, const unsigned char value)
{
  return (unsigned char *)UDInsert(deq, index, &value, sizeof(value));
}

short *UDInsertS(const ud_t deq, const ud_size_t index, const short value)
{
  return (short *)UDInsert(deq, index, &value, sizeof(value));
}

unsigned short *UDInsertUS(const ud_t deq, const ud_size_t index, const unsigned short value)
{
  return (unsigned short *)UDInsert(deq, index, &value, sizeof(value));
}

int *UDInsertI(const ud_t deq, const ud_size_t index, const int value)
{
  return (int *)UDInsert(deq, index, &value, sizeof(value));
}

unsigned int *UDInsertUI(const ud_t deq, const ud_size_t index, const unsigned int value)
{
  return (unsigned int *)UDInsert(deq, index, &value, sizeof(value));
}

long *UDInsertL(const ud_t deq, const ud_size_t index, const long value)
{
  return (long *)UDInsert(deq, index, &value, sizeof(value));
}

unsigned long *UDInsertUL(const ud_t deq, const ud_size_t index, const unsigned long value)
{
  return (unsigned long *)UDInsert(deq, index, &value, sizeof(value));
}

long long *UDInsertLL(const ud_t deq, const ud_size_t index, const long long value)
{
  return (long long *)UDInsert(deq, index, &value, sizeof(value));
}

unsigned long long *UDInsertULL(const ud_t deq, const ud_size_t index, const unsigned long long value)
{
  return (unsigned long long *)UDInsert(deq, index, &value, sizeof(value));
}

float *UDInsertF(const ud_t deq, const ud_size_t index, const float value)
{
  return (float *)UDInsert(deq, index, &value, sizeof(value));
}

double *UDInsertD(const ud_t deq, const ud_size_t index, const double value)
{
  return (double *)UDInsert(deq, index, &value, sizeof(value));
}

long double *UDInsertLD(const ud_t deq, const ud_size_t index, const long double value)
{
  return (long double *)UDInsert(deq, index, &value, sizeof(value));
}

char UDAtC(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(char *)ptr;
}

signed char UDAtSC(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(signed char *)ptr;
}

unsigned char UDAtUC(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(unsigned char *)ptr;
}

short UDAtS(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(short *)ptr;
}

unsigned short UDAtUS(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(unsigned short *)ptr;
}

int UDAtI(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(int *)ptr;
}

unsigned int UDAtUI(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(unsigned int *)ptr;
}

long UDAtL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(long *)ptr;
}

unsigned long UDAtUL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(unsigned long *)ptr;
}

long long UDAtLL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(long long *)ptr;
}

unsigned long long UDAtULL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(unsigned long long *)ptr;
}

float UDAtF(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(float *)ptr;
}

double UDAtD(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(double *)ptr;
}

long double UDAtLD(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDAt(deq, index);
  if (ptr == NULL)
    return 0;

  return *(long double *)ptr;
}

char UDEraseC(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  char val = *(char *)ptr;
  free(ptr);
  return val;
}

signed char UDEraseSC(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  signed char val = *(signed char *)ptr;
  free(ptr);
  return val;
}

unsigned char UDEraseUC(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  unsigned char val = *(unsigned char *)ptr;
  free(ptr);
  return val;
}

short UDEraseS(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  short val = *(short *)ptr;
  free(ptr);
  return val;
}

unsigned short UDEraseUS(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  unsigned short val = *(unsigned short *)ptr;
  free(ptr);
  return val;
}

int UDEraseI(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  int val = *(int *)ptr;
  free(ptr);
  return val;
}

unsigned int UDEraseUI(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  unsigned int val = *(unsigned int *)ptr;
  free(ptr);
  return val;
}

long UDEraseL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  long val = *(long *)ptr;
  free(ptr);
  return val;
}

unsigned long UDEraseUL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  unsigned long val = *(unsigned long *)ptr;
  free(ptr);
  return val;
}

long long UDEraseLL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  long long val = *(long long *)ptr;
  free(ptr);
  return val;
}

unsigned long long UDEraseULL(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  unsigned long long val = *(unsigned long long *)ptr;
  free(ptr);
  return val;
}

float UDEraseF(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  float val = *(float *)ptr;
  free(ptr);
  return val;
}

double UDEraseD(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  double val = *(double *)ptr;
  free(ptr);
  return val;
}

long double UDEraseLD(const ud_t deq, const ud_size_t index)
{
  void *ptr = UDErase(deq, index);
  if (ptr == NULL)
    return 0;

  long double val = *(long double *)ptr;
  free(ptr);
  return val;
}

char *UDPushFrontStr(const ud_t deq, const char *str)
{
  return (char*)UDPushFront(deq, str, strlen(str) + 1u);
}

char *UDFrontStr(const ud_t deq)
{
  return (char*)UDFront(deq);
}

char *UDPopFrontStr(const ud_t deq)
{
  return (char*)UDPopFront(deq);
}

char *UDPushBackStr(const ud_t deq, const char *str)
{
  return (char*)UDPushBack(deq, str, strlen(str) + 1u);
}

char *UDBackStr(const ud_t deq)
{
  return (char*)UDBack(deq);
}

char *UDPopBackStr(const ud_t deq)
{
  return (char*)UDPopBack(deq);
}

char *UDInsertStr(const ud_t deq, const ud_size_t index, const char *str)
{
  return (char*)UDInsert(deq, index, str, strlen(str) + 1u);
}

char *UDAtStr(const ud_t deq, const ud_size_t index)
{
  return (char*)UDAt(deq, index);
}

char *UDEraseStr(const ud_t deq, const ud_size_t index)
{
  return (char*)UDErase(deq, index);
}

wchar_t *UDPushFrontWStr(const ud_t deq, const wchar_t *str)
{
  return (wchar_t*)UDPushFront(deq, str, (wcslen(str) + 1u) * sizeof(wchar_t));
}

wchar_t *UDFrontWStr(const ud_t deq)
{
  return (wchar_t*)UDFront(deq);
}

wchar_t *UDPopFrontWStr(const ud_t deq)
{
  return (wchar_t*)UDPopFront(deq);
}

wchar_t *UDPushBackWStr(const ud_t deq, const wchar_t *str)
{
  return (wchar_t*)UDPushBack(deq, str, (wcslen(str) + 1u) * sizeof(wchar_t));
}

wchar_t *UDBackWStr(const ud_t deq)
{
  return (wchar_t*)UDBack(deq);
}

wchar_t *UDPopBackWStr(const ud_t deq)
{
  return (wchar_t*)UDPopBack(deq);
}

wchar_t *UDInsertWStr(const ud_t deq, const ud_size_t index, const wchar_t *str)
{
  return (wchar_t*)UDInsert(deq, index, str, (wcslen(str) + 1u) * sizeof(wchar_t));
}

wchar_t *UDAtWStr(const ud_t deq, const ud_size_t index)
{
  return (wchar_t*)UDAt(deq, index);
}

wchar_t *UDEraseWStr(const ud_t deq, const ud_size_t index)
{
  return (wchar_t*)UDErase(deq, index);
}

int UDSortAscC(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscC);
}

int UDSortDescC(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescC);
}

int UDSortAscSC(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscSC);
}

int UDSortDescSC(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescSC);
}

int UDSortAscUC(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscUC);
}

int UDSortDescUC(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescUC);
}

int UDSortAscS(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscS);
}

int UDSortDescS(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescS);
}

int UDSortAscUS(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscUS);
}

int UDSortDescUS(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescUS);
}

int UDSortAscI(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscI);
}

int UDSortDescI(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescI);
}

int UDSortAscUI(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscUI);
}

int UDSortDescUI(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescUI);
}

int UDSortAscL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscL);
}

int UDSortDescL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescL);
}

int UDSortAscUL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscUL);
}

int UDSortDescUL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescUL);
}

int UDSortAscLL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscLL);
}

int UDSortDescLL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescLL);
}

int UDSortAscULL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscULL);
}

int UDSortDescULL(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescULL);
}

int UDSortAscF(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscF);
}

int UDSortDescF(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescF);
}

int UDSortAscD(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscD);
}

int UDSortDescD(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescD);
}

int UDSortAscLD(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscLD);
}

int UDSortDescLD(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescLD);
}

int UDSortAscStr(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscStr);
}

int UDSortDescStr(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescStr);
}

int UDSortAscWStr(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpAscWStr);
}

int UDSortDescWStr(const ud_t deq)
{
  return UDSort(deq, (ud_cmp_t)CmpDescWStr);
}

char *UDInsertAscC(const ud_t deq, const char value)
{
  return (char *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscC);
}

char *UDInsertDescC(const ud_t deq, const char value)
{
  return (char *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescC);
}

signed char *UDInsertAscSC(const ud_t deq, const signed char value)
{
  return (signed char *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscSC);
}

signed char *UDInsertDescSC(const ud_t deq, const signed char value)
{
  return (signed char *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescSC);
}

unsigned char *UDInsertAscUC(const ud_t deq, const unsigned char value)
{
  return (unsigned char *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscUC);
}

unsigned char *UDInsertDescUC(const ud_t deq, const unsigned char value)
{
  return (unsigned char *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescUC);
}

short *UDInsertAscS(const ud_t deq, const short value)
{
  return (short *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscS);
}

short *UDInsertDescS(const ud_t deq, const short value)
{
  return (short *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescS);
}

unsigned short *UDInsertAscUS(const ud_t deq, const unsigned short value)
{
  return (unsigned short *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscUS);
}

unsigned short *UDInsertDescUS(const ud_t deq, const unsigned short value)
{
  return (unsigned short *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescUS);
}

int *UDInsertAscI(const ud_t deq, const int value)
{
  return (int *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscI);
}

int *UDInsertDescI(const ud_t deq, const int value)
{
  return (int *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescI);
}

unsigned int *UDInsertAscUI(const ud_t deq, const unsigned int value)
{
  return (unsigned int *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscUI);
}

unsigned int *UDInsertDescUI(const ud_t deq, const unsigned int value)
{
  return (unsigned int *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescUI);
}

long *UDInsertAscL(const ud_t deq, const long value)
{
  return (long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscL);
}

long *UDInsertDescL(const ud_t deq, const long value)
{
  return (long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescL);
}

unsigned long *UDInsertAscUL(const ud_t deq, const unsigned long value)
{
  return (unsigned long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscUL);
}

unsigned long *UDInsertDescUL(const ud_t deq, const unsigned long value)
{
  return (unsigned long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescUL);
}

long long *UDInsertAscLL(const ud_t deq, const long long value)
{
  return (long long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscLL);
}

long long *UDInsertDescLL(const ud_t deq, const long long value)
{
  return (long long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescLL);
}

unsigned long long *UDInsertAscULL(const ud_t deq, const unsigned long long value)
{
  return (unsigned long long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscULL);
}

unsigned long long *UDInsertDescULL(const ud_t deq, const unsigned long long value)
{
  return (unsigned long long *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescULL);
}

float *UDInsertAscF(const ud_t deq, const float value)
{
  return (float *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscF);
}

float *UDInsertDescF(const ud_t deq, const float value)
{
  return (float *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescF);
}

double *UDInsertAscD(const ud_t deq, const double value)
{
  return (double *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscD);
}

double *UDInsertDescD(const ud_t deq, const double value)
{
  return (double *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescD);
}

long double *UDInsertAscLD(const ud_t deq, const long double value)
{
  return (long double *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpAscLD);
}

long double *UDInsertDescLD(const ud_t deq, const long double value)
{
  return (long double *)UDInsertSorted(deq, &value, sizeof(value), (ud_cmp_t)CmpDescLD);
}

char *UDInsertAscStr(const ud_t deq, const char *str)
{
  return (char *)UDInsertSorted(deq, str, strlen(str) + 1u, (ud_cmp_t)CmpAscStr);
}

char *UDInsertDescStr(const ud_t deq, const char *str)
{
  return (char *)UDInsertSorted(deq, str, strlen(str) + 1u, (ud_cmp_t)CmpDescStr);
}

wchar_t *UDInsertAscWStr(const ud_t deq, const wchar_t *str)
{
  return (wchar_t *)UDInsertSorted(deq, str, (wcslen(str) + 1u) * sizeof(wchar_t), (ud_cmp_t)CmpAscWStr);
}

wchar_t *UDInsertDescWStr(const ud_t deq, const wchar_t *str)
{
  return (wchar_t *)UDInsertSorted(deq, str, (wcslen(str) + 1u) * sizeof(wchar_t), (ud_cmp_t)CmpDescWStr);
}

ud_size_t UDFindC(const ud_t deq, const char value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscC);
}

ud_size_t UDFindSC(const ud_t deq, const signed char value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscSC);
}

ud_size_t UDFindUC(const ud_t deq, const unsigned char value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscUC);
}

ud_size_t UDFindS(const ud_t deq, const short value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscS);
}

ud_size_t UDFindUS(const ud_t deq, const unsigned short value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscUS);
}

ud_size_t UDFindI(const ud_t deq, const int value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscI);
}

ud_size_t UDFindUI(const ud_t deq, const unsigned int value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscUI);
}

ud_size_t UDFindL(const ud_t deq, const long value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscL);
}

ud_size_t UDFindUL(const ud_t deq, const unsigned long value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscUL);
}

ud_size_t UDFindLL(const ud_t deq, const long long value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscLL);
}

ud_size_t UDFindULL(const ud_t deq, const unsigned long long value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscULL);
}

ud_size_t UDFindF(const ud_t deq, const float value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscF);
}

ud_size_t UDFindD(const ud_t deq, const double value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscD);
}

ud_size_t UDFindLD(const ud_t deq, const long double value)
{
  return UDFind(deq, &value, (ud_cmp_t)CmpAscLD);
}

ud_size_t UDFindStr(const ud_t deq, const char *str)
{
  return UDFind(deq, str, (ud_cmp_t)CmpAscStr);
}

ud_size_t UDFindWStr(const ud_t deq, const wchar_t *str)
{
  return UDFind(deq, str, (ud_cmp_t)CmpAscWStr);
}

char UDRemoveC(const ud_t deq, const char value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscC);
  if (ptr == NULL)
    return 0;

  char val = *(char *)ptr;
  free(ptr);
  return val;
}

signed char UDRemoveSC(const ud_t deq, const signed char value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscSC);
  if (ptr == NULL)
    return 0;

  signed char val = *(signed char *)ptr;
  free(ptr);
  return val;
}

unsigned char UDRemoveUC(const ud_t deq, const unsigned char value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscUC);
  if (ptr == NULL)
    return 0;

  unsigned char val = *(unsigned char *)ptr;
  free(ptr);
  return val;
}

short UDRemoveS(const ud_t deq, const short value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscS);
  if (ptr == NULL)
    return 0;

  short val = *(short *)ptr;
  free(ptr);
  return val;
}

unsigned short UDRemoveUS(const ud_t deq, const unsigned short value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscUS);
  if (ptr == NULL)
    return 0;

  unsigned short val = *(unsigned short *)ptr;
  free(ptr);
  return val;
}

int UDRemoveI(const ud_t deq, const int value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscI);
  if (ptr == NULL)
    return 0;

  int val = *(int *)ptr;
  free(ptr);
  return val;
}

unsigned int UDRemoveUI(const ud_t deq, const unsigned int value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscUI);
  if (ptr == NULL)
    return 0;

  unsigned int val = *(unsigned int *)ptr;
  free(ptr);
  return val;
}

long UDRemoveL(const ud_t deq, const long value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscL);
  if (ptr == NULL)
    return 0;

  long val = *(long *)ptr;
  free(ptr);
  return val;
}

unsigned long UDRemoveUL(const ud_t deq, const unsigned long value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscUL);
  if (ptr == NULL)
    return 0;

  unsigned long val = *(unsigned long *)ptr;
  free(ptr);
  return val;
}

long long UDRemoveLL(const ud_t deq, const long long value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscLL);
  if (ptr == NULL)
    return 0;

  long long val = *(long long *)ptr;
  free(ptr);
  return val;
}

unsigned long long UDRemoveULL(const ud_t deq, const unsigned long long value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscULL);
  if (ptr == NULL)
    return 0;

  unsigned long long val = *(unsigned long long *)ptr;
  free(ptr);
  return val;
}

float UDRemoveF(const ud_t deq, const float value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscF);
  if (ptr == NULL)
    return 0;

  float val = *(float *)ptr;
  free(ptr);
  return val;
}

double UDRemoveD(const ud_t deq, const double value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscD);
  if (ptr == NULL)
    return 0;

  double val = *(double *)ptr;
  free(ptr);
  return val;
}

long double UDRemoveLD(const ud_t deq, const long double value)
{
  void *ptr = UDRemove(deq, &value, (ud_cmp_t)CmpAscLD);
  if (ptr == NULL)
    return 0;

  long double val = *(long double *)ptr;
  free(ptr);
  return val;
}

char *UDRemoveStr(const ud_t deq, const char *str)
{
  return (char *)UDRemove(deq, str, (ud_cmp_t)CmpAscStr);
}

wchar_t *UDRemoveWStr(const ud_t deq, const wchar_t *str)
{
  return (wchar_t *)UDRemove(deq, str, (ud_cmp_t)CmpAscWStr);
}
