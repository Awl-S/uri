#include "uri.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PORT_NUMBER 65535
/**
 * @brief Safely duplicates a substring.
 *
 * @param source Source string.
 * @param length Length of the substring.
 * @return char* Duplicated substring or nullptr if failed.
 *
 * @brief Безопасно дублирует подстроку.
 *
 * @param source Исходная строка.
 * @param length Длина подстроки.
 * @return char* Дублированная подстрока или nullptr в случае ошибки.
 */
static char *strndupSafe(const char *source, size_t length) {
    char *destination = malloc(length + 1);
    if (destination) {
        memcpy(destination, source, length);
        destination[length] = '\0';
    }
    return destination;
}
/**
 * @brief Parses the scheme from the URI.
 *
 * @param uriString Pointer to the URI string.
 * @param scheme Pointer to store the scheme.
 * @param schemeLength Pointer to store the length of the scheme.
 * @return int 0 on success, -1 on failure.
 *
 * @brief Разбирает схему из URI.
 *
 * @param uriString Указатель на строку URI.
 * @param scheme Указатель для хранения схемы.
 * @param schemeLength Указатель для хранения длины схемы.
 * @return int 0 при успешном выполнении, -1 при ошибке.
 */
static int parseScheme(const char **uriString, char **scheme, size_t *schemeLength) {
    const char *pos = strstr(*uriString, ":");
    if (pos == nullptr) {
        return -1;
    }
    *schemeLength = pos - *uriString;
    *scheme = strndupSafe(*uriString, *schemeLength);
    if (*scheme == nullptr) { // Проверка успешности выделения памяти
        return -1;
    }
    *uriString = pos + 1;
    return 0;
}


/**
 * @brief Parses the authority from the URI.
 *
 * @param uriString Pointer to the URI string.
 * @param userInfo Pointer to store the user info.
 * @param userInfoLength Pointer to store the length of the user info.
 * @param host Pointer to store the host.
 * @param hostLength Pointer to store the length of the host.
 * @param port Pointer to store the port.
 * @param portLength Pointer to store the length of the port.
 * @return int 0 on success, -1 on failure.
 *
 * @brief Разбирает авторитет из URI.
 *
 * @param uriString Указатель на строку URI.
 * @param userInfo Указатель для хранения информации о пользователе.
 * @param userInfoLength Указатель для хранения длины информации о пользователе.
 * @param host Указатель для хранения хоста.
 * @param hostLength Указатель для хранения длины хоста.
 * @param port Указатель для хранения порта.
 * @param portLength Указатель для хранения длины порта.
 * @return int 0 при успешном выполнении, -1 при ошибке.
 */
static int parseAuthority(const char **uriString, char **userInfo, size_t *userInfoLength, char **host, size_t *hostLength, char **port, size_t *portLength) {
    const char *pos = *uriString;

    if (*pos == '/' && *(pos + 1) == '/') {
        pos += 2;
    } else {
        return 0;
    }

    const char *atPos = strchr(pos, '@');
    if (atPos != nullptr) {
        *userInfoLength = atPos - pos;
        *userInfo = strndupSafe(pos, *userInfoLength);
        if (*userInfo == nullptr) { // Проверка успешности выделения памяти
            return -1;
        }
        pos = atPos + 1;
    }

    const char *hostEnd = pos + strcspn(pos, "]:/?#");
    *hostLength = hostEnd - pos;
    *host = strndupSafe(pos, *hostLength);
    if (*host == nullptr) { // Проверка успешности выделения памяти
        return -1;
    }
    pos = hostEnd;

    if ((*host)[0] == '[' && (*host)[*hostLength - 1] != ']') {
        return -1;
    }

    if (*pos == ':') {
        pos++;
        const char *portStart = pos;
        while (*pos >= '0' && *pos <= '9') {
            pos++;
        }
        *portLength = pos - portStart;
        *port = strndupSafe(portStart, *portLength);
        if (*port == nullptr) { // Проверка успешности выделения памяти
            return -1;
        }
        unsigned long portNum = strtoul(*port, nullptr, 10);
        if (portNum > MAX_PORT_NUMBER) {
            return -1;
        }
    }

    *uriString = pos;
    return 0;
}

/**
 * @brief Parses the path, query, and fragment from the URI.
 *
 * @param uriString URI string.
 * @param path Pointer to store the path.
 * @param pathLength Pointer to store the length of the path.
 * @param query Pointer to store the query.
 * @param queryLength Pointer to store the length of the query.
 * @param fragment Pointer to store the fragment.
 * @param fragmentLength Pointer to store the length of the fragment.
 *
 * @brief Разбирает путь, запрос и фрагмент из URI.
 *
 * @param uriString Строка URI.
 * @param path Указатель для хранения пути.
 * @param pathLength Указатель для хранения длины пути.
 * @param query Указатель для хранения запроса.
 * @param queryLength Указатель для хранения длины запроса.
 * @param fragment Указатель для хранения фрагмента.
 * @param fragmentLength Указатель для хранения длины фрагмента.
 */
static void parsePathQueryFragment(const char *uriString, char **path, size_t *pathLength, char **query, size_t *queryLength, char **fragment, size_t *fragmentLength) {
    const char *pathStart = uriString;
    const char *queryStart = strchr(pathStart, '?');
    const char *fragmentStart = strchr(pathStart, '#');

    // Разделяем вложенный условный оператор на независимые операторы
    // Separate nested conditional operator into independent statements
    if (queryStart) {
        if (fragmentStart) {
            *pathLength = queryStart - pathStart;
        } else {
            *pathLength = queryStart - pathStart;
        }
    } else {
        if (fragmentStart) {
            *pathLength = fragmentStart - pathStart;
        } else {
            *pathLength = strlen(pathStart);
        }
    }
    *path = strndupSafe(pathStart, *pathLength);

    // Parse query if present
    if (queryStart) {
        if (fragmentStart) {
            *queryLength = fragmentStart - queryStart - 1;
        } else {
            *queryLength = strlen(queryStart) - 1;
        }
        *query = strndupSafe(queryStart + 1, *queryLength);
    }

    // Parse fragment if present
    if (fragmentStart) {
        *fragmentLength = strlen(fragmentStart) - 1;
        *fragment = strndupSafe(fragmentStart + 1, *fragmentLength);
    }
}

/**
 * @brief Creates and parses a URI structure from the given string.
 *
 * @param uriString URI string.
 * @return struct Uri* Pointer to the created Uri structure, or nullptr if failed.
 *
 * @brief Создает и разбирает структуру URI из заданной строки.
 *
 * @param uriString Строка URI.
 * @return struct Uri* Указатель на созданную структуру Uri, или nullptr в случае ошибки.
 */
struct Uri *uriCreate(const char *uriString) {
    if (uriString == nullptr) {
        return nullptr;
    }

//    printf("Allocating memory for Uri structure...\n");
    struct Uri *uri = calloc(1, sizeof(*uri));
    if (uri == nullptr) {
//        printf("Memory allocation failed for Uri structure.\n");
        return nullptr;
    }

    const char *pos = uriString;
    if (parseScheme(&pos, &uri->scheme, &uri->schemeLength) < 0) {
//        printf("Failed to parse scheme.\n");
        uriDestroy(uri);
        return nullptr;
    }

//    printf("Scheme parsed successfully: %.*s\n", (int)uri->schemeLength, uri->scheme);

    if (parseAuthority(&pos, &uri->userInfo, &uri->userInfoLength, &uri->host, &uri->hostLength, &uri->port, &uri->portLength) < 0) {
//        printf("Failed to parse authority.\n");
        uriDestroy(uri);
        return nullptr;
    }

//    printf("Authority parsed successfully.\n");
//    printf("UserInfo: %.*s\n", (int)uri->userInfoLength, uri->userInfo);
//    printf("Host: %.*s\n", (int)uri->hostLength, uri->host);
//    printf("Port: %.*s\n", (int)uri->portLength, uri->port);

    parsePathQueryFragment(pos, &uri->path, &uri->pathLength, &uri->query, &uri->queryLength, &uri->fragment, &uri->fragmentLength);

//    printf("Path, query, and fragment parsed successfully.\n");
//    printf("Path: %.*s\n", (int)uri->pathLength, uri->path);
//    printf("Query: %.*s\n", (int)uri->queryLength, uri->query);
//    printf("Fragment: %.*s\n", (int)uri->fragmentLength, uri->fragment);
//    printf("Scheme: %.*s\n", (int)uri->schemeLength, uri->scheme);

    // Calculate the total length required for the full URI string
    size_t totalLength = uri->schemeLength + 3 + // scheme + "://"
                         uri->userInfoLength + (uri->userInfoLength ? 1 : 0) + // userInfo + "@"
                         uri->hostLength +
                         uri->portLength + (uri->portLength ? 1 : 0) + // port + ":"
                         uri->pathLength +
                         uri->queryLength + (uri->queryLength ? 1 : 0) + // query + "?"
                         uri->fragmentLength + (uri->fragmentLength ? 1 : 0) + // fragment + "#"
                         1; // nullptr terminator

//    printf("Allocating memory for buffer...\n");
    uri->buffer = malloc(totalLength);
    if (uri->buffer == nullptr) {
//        printf("Memory allocation failed for buffer.\n");
        uriDestroy(uri);
        return nullptr;
    }

//    printf("Constructing full URI...\n");
    char *bufPos = uri->buffer;

    // Copy scheme
    memcpy(bufPos, uri->scheme, uri->schemeLength);
    bufPos += uri->schemeLength;
    memcpy(bufPos, "://", 3);
    bufPos += 3;

    // Copy userInfo if present
    if (uri->userInfoLength) {
        memcpy(bufPos, uri->userInfo, uri->userInfoLength);
        bufPos += uri->userInfoLength;
        *bufPos = '@';
        bufPos += 1;
    }

    // Copy host
    memcpy(bufPos, uri->host, uri->hostLength);
    bufPos += uri->hostLength;

    // Copy port if present
    if (uri->portLength) {
        *bufPos = ':';
        bufPos += 1;
        memcpy(bufPos, uri->port, uri->portLength);
        bufPos += uri->portLength;
    }

    // Copy path
    memcpy(bufPos, uri->path, uri->pathLength);
    bufPos += uri->pathLength;

    // Copy query if present
    if (uri->queryLength) {
        *bufPos = '?';
        bufPos += 1;
        memcpy(bufPos, uri->query, uri->queryLength);
        bufPos += uri->queryLength;
    }

    // Copy fragment if present
    if (uri->fragmentLength) {
        *bufPos = '#';
        bufPos += 1;
        memcpy(bufPos, uri->fragment, uri->fragmentLength);
        bufPos += uri->fragmentLength;
    }

    // nullptr terminate the buffer
    *bufPos = '\0';

//    printf("Full URI constructed: %s\n", uri->buffer);

    return uri;
}

/**
 * @brief Destroys the URI structure and frees allocated memory.
 *
 * @param uri Pointer to the Uri structure to destroy.
 *
 * @brief Уничтожает структуру URI и освобождает выделенную память.
 *
 * @param uri Указатель на структуру Uri для уничтожения.
 */
void uriDestroy(struct Uri *uri) {
    if (uri) {
        if (uri->scheme) free(uri->scheme);
        if (uri->userInfo) free(uri->userInfo);
        if (uri->host) free(uri->host);
        if (uri->port) free(uri->port);
        if (uri->path) free(uri->path);
        if (uri->query) free(uri->query);
        if (uri->fragment) free(uri->fragment);
        if (uri->buffer) free(uri->buffer);
        free(uri);
    }
}

/**
 * @brief Retrieves the scheme part of the URI.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* Scheme part of the URI.
 *
 * @brief Получает часть схемы URI.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Часть схемы URI.
 */
char *uriGetScheme(const struct Uri *uri) {
    return uri->scheme;
}

/**
 * @brief Retrieves the user info part of the URI.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* User info part of the URI.
 *
 * @brief Получает часть информации о пользователе URI.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Часть информации о пользователе URI.
 */
char *uriGetUserInfo(const struct Uri *uri) {
    return uri->userInfo;
}

/**
 * @brief Retrieves the host part of the URI.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* Host part of the URI.
 *
 * @brief Получает часть хоста URI.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Часть хоста URI.
 */
char *uriGetHost(const struct Uri *uri) {
    return uri->host;
}

/**
 * @brief Retrieves the port part of the URI.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* Port part of the URI.
 *
 * @brief Получает часть порта URI.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Часть порта URI.
 */
char *uriGetPort(const struct Uri *uri) {
    return uri->port;
}

/**
 * @brief Retrieves the path part of the URI.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* Path part of the URI.
 *
 * @brief Получает часть пути URI.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Часть пути URI.
 */
char *uriGetPath(const struct Uri *uri) {
    return uri->path;
}

/**
 * @brief Retrieves the query part of the URI.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* Query part of the URI.
 *
 * @brief Получает часть запроса URI.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Часть запроса URI.
 */
char *uriGetQuery(const struct Uri *uri) {
    return uri->query;
}

/**
 * @brief Retrieves the fragment part of the URI.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* Fragment part of the URI.
 *
 * @brief Получает часть фрагмента URI.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Часть фрагмента URI.
 */
char *uriGetFragment(const struct Uri *uri) {
    return uri->fragment;
}

/**
 * @brief Retrieves the full URI as a string.
 *
 * @param uri Pointer to the Uri structure.
 * @return char* Full URI string.
 *
 * @brief Получает полный URI в виде строки.
 *
 * @param uri Указатель на структуру Uri.
 * @return char* Полная строка URI.
 */
char *uriGetFullUri(const struct Uri *uri) {
    if (uri == nullptr || uri->buffer == nullptr) {
        return nullptr;
    }

    // Выделяем память для копии строки buffer
    char *fullUri = strdup(uri->buffer);
    if (fullUri == nullptr) {
//        printf("Memory allocation failed for fullUri.\n");
        return nullptr;
    }

    return fullUri;
}





