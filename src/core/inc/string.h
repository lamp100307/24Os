#ifndef STRING_H
#define STRING_H

#include "types.h"

size_t strlen(const char *s);
char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
void *memset(void *s, int c, size_t n);
void *memcpy(void *d, const void *s, size_t n);
void *memmove(void *d, const void *s, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
char *strchr(const char *s, int c);
char *strcat(char *d, const char *s);
char *strncat(char *d, const char *s, size_t n);
char *strrchr(const char *s, int c);
size_t strspn(const char *s, const char *a);
size_t strcspn(const char *s, const char *r);
char *strpbrk(const char *s, const char *a);
char *strstr(const char *h, const char *n);
char *strtok(char *s, const char *d);
void *memchr(const void *s, int c, size_t n);
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);

#endif