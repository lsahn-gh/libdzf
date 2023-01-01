# What is libdzf?
libdzf is a header-only data structure C library based on C99 std, template-like in C++. The most terrible point in C programming is that programmers, they have to implement their own data structures, not even generic-able. They might feel such a pain and therefore get pissed off. The project comes from that point.

## Supported
- Vector (like in C++)
- Stack
- Queue

## Build
```sh
$ ./autogen.sh
$ ./configure
$ make
```

## testcases
```sh
$ tests/main
```

## Documentation
Prerequirements:
- Doxygen

```sh
$ make -C doc
```
