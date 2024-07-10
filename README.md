# URI Library

This is a robust C library for parsing and managing Uniform Resource Identifiers (URIs). It supports the extraction of various components of a URI, such as the scheme, user info, host, port, path, query, and fragment.

## Features

- Parse and create a URI structure from a string.
- Extract different components of the URI.
- Retrieve the full URI as a string.
- Memory management for URI structures.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- CMake (version 3.18 or higher)

### Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/Awl-S/uri.git
    cd uri
    ```

2. Compile the library and example program:

    ```sh
    gcc -o main main.c uri.c
    ```
    
2. Compile the library and example program using CMake:

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

### Usage

Include the header file in your C program:

```c
#include "uri.h"
```

### Create and use a URI:

```c

#include "uri.h"
#include <stdio.h>

int main() {
    struct Uri *my_uri = uriCreate("http://user:pass@www.example.com:8080/path?query#fragment");
    if (!my_uri) {
        fprintf(stderr, "Failed to create URI\n");
        return 1;
    }

    printf("Scheme: %s\n", uriGetScheme(my_uri));
    printf("User Info: %s\n", uriGetUserInfo(my_uri));
    printf("Host: %s\n", uriGetHost(my_uri));
    printf("Port: %s\n", uriGetPort(my_uri));
    printf("Path: %s\n", uriGetPath(my_uri));
    printf("Query: %s\n", uriGetQuery(my_uri));
    printf("Fragment: %s\n", uriGetFragment(my_uri));

    char *full_uri = uriGetFullUri(my_uri);
    if (full_uri) {
        printf("Full URI: %s\n", full_uri);
        free(full_uri);
    }

    uriDestroy(my_uri);
    return 0;
}
```

### API Reference
#### uriCreate

```c
struct Uri *uriCreate(const char *uriString);
```
Creates and parses a URI structure from the given string.
* uriString: URI string.
* Returns a pointer to the created Uri structure, or nullptr if it fails.

#### uriDestroy
```c
void uriDestroy(struct Uri *uri); 
```
Destroys the URI structure and frees allocated memory.
* uri: Pointer to the Uri structure to destroy.

#### uriGetScheme
```c
char *uriGetScheme(const struct Uri *uri);
```
Retrieves the scheme part of the URI.

* uri: Pointer to the Uri structure.
* Returns the scheme part of the URI.


#### uriGetUserInfo
```c
char *uriGetUserInfo(const struct Uri *uri);
```
Retrieves the user info part of the URI.

* uri: Pointer to the Uri structure.
* Returns the user info part of the URI.

#### uriGetHost
```c
char *uriGetHost(const struct Uri *uri);
```
Retrieves the host part of the URI.

* uri: Pointer to the Uri structure.
* Returns the host part of the URI.

#### uriGetPort
```c
char *uriGetPort(const struct Uri *uri);
```
Retrieves the port part of the URI.

* uri: Pointer to the Uri structure.
* Returns the port part of the URI.

#### uriGetPath
```c
char *uriGetPath(const struct Uri *uri);
```
Retrieves the path part of the URI.

* uri: Pointer to the Uri structure.
* Returns the path part of the URI.

#### uriGetQuery
```c
char *uriGetQuery(const struct Uri *uri);
```
Retrieves the query part of the URI.

* uri: Pointer to the Uri structure.
* Returns the query part of the URI.

#### uriGetFragment
```c
char *uriGetFragment(const struct Uri *uri);
```
Retrieves the fragment part of the URI.

* uri: Pointer to the Uri structure.
* Returns the fragment part of the URI.

#### uriGetFullUri
```c
char *uriGetFullUri(const struct Uri *uri);
```
Retrieves the full URI as a string.

* uri: Pointer to the Uri structure.
* Returns the full URI string.

