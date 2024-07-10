#ifndef URI_H
#define URI_H

#include <stddef.h>

/**
 * @struct Uri
 * @brief Structure to represent a parsed URI.
 *
 * @struct Uri
 * @brief Структура для представления разобранного URI.
 */
struct Uri {
    char *scheme;     /**< Scheme part of the URI / Часть схемы URI */
    char *userInfo;   /**< User info part of the URI / Часть информации о пользователе URI */
    char *host;       /**< Host part of the URI / Часть хоста URI */
    char *port;       /**< Port part of the URI / Часть порта URI */
    char *path;       /**< Path part of the URI / Часть пути URI */
    char *query;      /**< Query part of the URI / Часть запроса URI */
    char *fragment;   /**< Fragment part of the URI / Часть фрагмента URI */
    size_t schemeLength;  /**< Length of the scheme / Длина схемы */
    size_t userInfoLength;/**< Length of the user info / Длина информации о пользователе */
    size_t hostLength;    /**< Length of the host / Длина хоста */
    size_t portLength;    /**< Length of the port / Длина порта */
    size_t pathLength;    /**< Length of the path / Длина пути */
    size_t queryLength;   /**< Length of the query / Длина запроса */
    size_t fragmentLength;/**< Length of the fragment / Длина фрагмента */
    char *buffer;         /**< Buffer to store the full URI / Буфер для хранения полного URI */
};

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
struct Uri *uriCreate(const char *uriString);

/**
 * @brief Destroys the URI structure and frees allocated memory.
 *
 * @param uri Pointer to the Uri structure to destroy.
 *
 * @brief Уничтожает структуру URI и освобождает выделенную память.
 *
 * @param uri Указатель на структуру Uri для уничтожения.
 */
void uriDestroy(struct Uri *uri);

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
char *uriGetScheme(const struct Uri *uri);

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
char *uriGetUserInfo(const struct Uri *uri);

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
char *uriGetHost(const struct Uri *uri);

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
char *uriGetPort(const struct Uri *uri);

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
char *uriGetPath(const struct Uri *uri);

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
char *uriGetQuery(const struct Uri *uri);

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
char *uriGetFragment(const struct Uri *uri);

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
char *uriGetFullUri(const struct Uri *uri);

#endif // URI_H
