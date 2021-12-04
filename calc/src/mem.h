
#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void err_handle(void);

void* new_ptr(size_t n, size_t size) {
  void* ptr = calloc(n,size);
  if (ptr == NULL) {
    err_handle();
  }
  return ptr;
}

void* resize_ptr(void* ptr, size_t size) {
  ptr = realloc(ptr,size);
  if (ptr == NULL) {
    err_handle();
  }
  return ptr;
}

FILE* file_open(const char* filename, const char* mode) {
  FILE* fp = fopen(filename, mode);
  if (fp == NULL) {
    err_handle();
  }
  return fp;
}

void file_close(FILE* fp) {
  fclose(fp);
  fp = NULL;
}

void err_handle(void) {
  fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
  exit(EXIT_FAILURE);
}

void free_ptr(void* ptr) {
  if (ptr != NULL) {
    free(ptr);
    ptr = NULL;
  }
}

#endif
