#pragma once
typedef unsigned __int64 uint64_t;
uint64_t MurmurHash64A(const void * key, int len, unsigned int seed);
uint64_t MurmurHash64B(const void * key, int len, unsigned int seed);