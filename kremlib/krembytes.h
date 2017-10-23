/* Garbage-collected fat pointers that keep track of their lengths. */
#ifndef __KREMBYTES_H
#ifndef __FStar_H
#define __KREMBYTES_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "Prims.h"


#include "FStar.h"

typedef uint8_t FStar_Bytes_byte;

/* Copying two words of memory is ok, I guess, when passing around bytes.
 * Alternatively, one could use C99 flexible arrays:
 *
 * typedef struct {
 *   size_t length;
 *   char *data[];
 * }
 */
/* TODO: how to resolve this, this must declared in kremlib.h due to
   circular deps. */


/* typedef struct { */
/*   uint8_t fst, snd; */
/* } K___uint8_t_uint8_t; */

/* typedef struct { */
/*   FStar_Bytes_bytes fst, snd; */
/* } K___FStar_Bytes_bytes_FStar_Bytes_bytes; */

#define CHECK(x) do { \
  if (!(x)) { \
    fprintf(stderr, "malloc failed at %s:%d", __FILE__, __LINE__); \
    exit(253); \
  } \
} while (0)

static inline FStar_Bytes_bytes FStar_Bytes_copy(FStar_Bytes_bytes b1) {
  return b1;
}

static inline krml_checked_int_t FStar_Bytes_length(FStar_Bytes_bytes b) {
  return b.length;
}

static FStar_Bytes_bytes FStar_Bytes_empty_bytes = { .length = 0, .data = NULL };

static inline FStar_Bytes_byte FStar_Bytes_get(FStar_Bytes_bytes b, uint32_t i) {
  return (FStar_Bytes_byte) b.data[i];
}

static inline FStar_Bytes_bytes FStar_Bytes_set_byte(FStar_Bytes_bytes b1, uint32_t i, FStar_Bytes_byte v) {
  char *data = malloc(b1.length);
  CHECK(data);
  memcpy(data, b1.data, b1.length);
  data[i] = (char) v;
  FStar_Bytes_bytes b2 = { .length = b1.length, data = data };
  return b2;
}

static inline FStar_Bytes_bytes FStar_Bytes_create(uint32_t length, FStar_Bytes_byte initial) {
  char *data = malloc(length);
  CHECK(data);
  memset(data, initial, length);
  FStar_Bytes_bytes b = { .length = length, .data = data };
  return b;
}

static inline FStar_Bytes_bytes FStar_Bytes_init(uint32_t length, FStar_Bytes_byte (*initial)(uint32_t i)) {
  char *data = malloc(length);
  CHECK(data);
  for (uint32_t i = 0; i < length; ++i)
    data[i] = initial(i);
  FStar_Bytes_bytes b = { .length = length, .data = data };
  return b;
}

static inline FStar_Bytes_bytes FStar_Bytes_abyte(FStar_Bytes_byte v1) {
  char * data = (char*)malloc(1);
  CHECK(data);
  data[0] = v1;
  FStar_Bytes_bytes b = { .length = 1, .data = data };
  return b;
}

static inline FStar_Bytes_bytes FStar_Bytes_twobytes(K___uint8_t_uint8_t v) {
  char * data = malloc(2);
  CHECK(data);
  data[0] = v.fst;
  data[1] = v.snd;
  FStar_Bytes_bytes b = { .length = 2, .data = data };
  return b;
}

static inline FStar_Bytes_bytes FStar_Bytes_append(FStar_Bytes_bytes b1, FStar_Bytes_bytes b2) {
  // Overflow check
  uint32_t length = Prims_op_Addition(b1.length, b2.length);
  char * data = (char*)malloc(length);
  CHECK(data);
  memcpy(data, b1.data, b1.length);
  memcpy(data + b1.length, b2.data, b2.length);
  FStar_Bytes_bytes b = { .length = length, .data = data };
  return b;
}

static inline FStar_Bytes_bytes FStar_Bytes_slice(FStar_Bytes_bytes b1, uint32_t s, uint32_t e) {
  if (s == e)
    return FStar_Bytes_empty_bytes;
  if (s > e)
    exit(254);
  uint32_t length = e - s;
  char * data = malloc(length);
  CHECK(data);
  memcpy(data, b1.data + s, length);
  FStar_Bytes_bytes b = { .length = length, .data = data };
  return b;
}

static inline FStar_Bytes_bytes FStar_Bytes_sub(FStar_Bytes_bytes b1, uint32_t s, uint32_t l) {
  return FStar_Bytes_slice(b1, s, Prims_op_Addition(s, l));
}

static inline FStar_Bytes_bytes FStar_Bytes_utf8_encode(const char *str) {
  // Note: the const char * helps ensuring that this is a string literal.
  // Strings in F* are UTF8-compatible already so this just writes out utf8
  // bytes in the string literal in C (TODO: check).
  // Assuming that there's no \0 in the string literal. TODO enforce at the F*
  // level.
  FStar_Bytes_bytes b = { .length = strlen(str), .data = str };
  return b;
}

static inline K___FStar_Bytes_bytes_FStar_Bytes_bytes FStar_Bytes_split(FStar_Bytes_bytes bs, FStar_UInt32_t i) {
   K___FStar_Bytes_bytes_FStar_Bytes_bytes p = { .fst = FStar_Bytes_sub(bs, 0, i),
                                                 .snd = FStar_Bytes_sub(bs, i, bs.length) };
   return p;
}

static inline FStar_UInt32_t FStar_Bytes_len(FStar_Bytes_bytes b1) {
  return b1.length;
}

// TODO

static inline FStar_Bytes_bytes FStar_Bytes_bytes_of_int(krml_checked_int_t k, krml_checked_int_t n) {
  FStar_Bytes_bytes b = { .length = 0ul, .data = NULL }; //placeholder!
  return b;
}

static inline krml_checked_int_t FStar_Bytes_int_of_bytes(FStar_Bytes_bytes bs) {
  return 0; //placeholder!
}

static inline int FStar_Bytes_repr_bytes(Prims_nat bs) {
  return bs;
}

static inline FStar_Bytes_bytes FStar_Bytes_xor(FStar_UInt32_t x, FStar_Bytes_bytes b1, FStar_Bytes_bytes b2) {
  FStar_Bytes_bytes b = { .length = 0ul, .data = NULL }; //placeholder!
  return b;
}


static inline FStar_Bytes_bytes FStar_Bytes_bytes_of_hex(Prims_string str) {
  FStar_Bytes_bytes b = { .length = 0ul, .data = NULL }; //placeholder!
  return b;
}

#endif
#endif
