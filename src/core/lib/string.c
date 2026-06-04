#include "../inc/string.h"

size_t strlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return p - s;
}

char *strcpy(char *d, const char *s) {
    char *r = d;
    while ((*d++ = *s++));
    return r;
}

char *strncpy(char *d, const char *s, size_t n) {
    char *r = d;
    while (n && (*d++ = *s++)) n--;
    while (n--) *d++ = 0;
    return r;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) { s1++; s2++; }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    if (!n) return 0;
    while (--n && *s1 && *s1 == *s2) { s1++; s2++; }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

void *memcpy(void *d, const void *s, size_t n) {
    unsigned char *dst = d;
    const unsigned char *src = s;
    while (n--) *dst++ = *src++;
    return d;
}

void *memmove(void *d, const void *s, size_t n) {
    unsigned char *dst = d;
    const unsigned char *src = s;
    if (dst < src) {
        while (n--) *dst++ = *src++;
    } else if (dst > src) {
        dst += n; src += n;
        while (n--) *--dst = *--src;
    }
    return d;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1, *p2 = s2;
    while (n--) {
        if (*p1 != *p2) return *p1 - *p2;
        p1++; p2++;
    }
    return 0;
}

char *strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c) return (char *)s;
        s++;
    }
    return (c == 0) ? (char *)s : NULL;
}

char *strcat(char *d, const char *s) {
    char *r = d;
    while (*d) d++;
    while ((*d++ = *s++));
    return r;
}

char *strncat(char *d, const char *s, size_t n) {
    char *r = d;
    while (*d) d++;
    while (n && (*d++ = *s++)) n--;
    *d = 0;
    return r;
}

char *strrchr(const char *s, int c) {
    char *r = NULL;
    do { if (*s == (char)c) r = (char *)s; } while (*s++);
    return r;
}

size_t strspn(const char *s, const char *a) {
    const char *p = s;
    while (*p) {
        const char *a_p = a;
        while (*a_p && *a_p != *p) a_p++;
        if (!*a_p) break;
        p++;
    }
    return p - s;
}

size_t strcspn(const char *s, const char *r) {
    const char *p = s;
    while (*p) {
        const char *r_p = r;
        while (*r_p && *r_p != *p) r_p++;
        if (*r_p) break;
        p++;
    }
    return p - s;
}

char *strpbrk(const char *s, const char *a) {
    while (*s) {
        const char *p = a;
        while (*p) { if (*p++ == *s) return (char *)s; }
        s++;
    }
    return NULL;
}

char *strstr(const char *h, const char *n) {
    if (!*n) return (char *)h;
    for (; *h; h++) {
        if (*h == *n) {
            const char *h_p = h, *n_p = n;
            while (*h_p && *n_p && *h_p == *n_p) { h_p++; n_p++; }
            if (!*n_p) return (char *)h;
        }
    }
    return NULL;
}

char *strtok(char *s, const char *d) {
    static char *last;
    if (!s && !(s = last)) return NULL;
    s += strspn(s, d);
    if (!*s) return last = NULL;
    char *t = s + strcspn(s, d);
    if (*t) { *t = 0; last = t + 1; } else last = NULL;
    return s;
}

void *memchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    while (n--) { if (*p == (unsigned char)c) return (void *)p; p++; }
    return NULL;
}

int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && ((*s1 | 32) == (*s2 | 32))) { s1++; s2++; }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncasecmp(const char *s1, const char *s2, size_t n) {
    if (!n) return 0;
    while (--n && *s1 && ((*s1 | 32) == (*s2 | 32))) { s1++; s2++; }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}