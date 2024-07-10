#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uri.h"

// Генерация массива URI
const char *uriArray[22] = {
        "https://shop.kz/offer/videokarta-gigabyte-rtx-4070-ti-aorus-xtreme-waterforce-wb-12-gb-geforce-rtx-4070-ti/",
        "https://market.yandex.kz/product--h610m-itx-ac/1779556307?sponsored=1&clid=5511841&vid=v334&pp=900&mclid=1003&distr_type=7",
        "https://user:pass@www.example1.com:8080/path?query#fragment",
        "http://www.example2.com/path",
        "ftp://ftp.example3.com/resource",
        "https://example4.com:443/path/to/resource?query=value#frag",
        "http://example5.com",
        "https://user:password@example6.com:9090/path/to/page",
        "ftp://user@ftp.example7.com:21/path",
        "https://example8.com?query=search",
        "http://example9.com#section",
        "https://user:pass@www.example10.com/path",
        "http://example11.com:80/resource?query=value",
        "https://example12.com:8443/path/to/file",
        "ftp://anonymous@ftp.example13.com/resource",
        "https://example14.com/resource?query",
        "http://example15.com/path#fragment",
        "https://example16.com",
        "ftp://ftp.example17.com:2121",
        "https://example18.com/path/to/resource#fragment",
        "http://example19.com/path?query",
        "https://example20.com:1234"
};



int main() {
    int result = 0;

    for (int i = 0; i < 21; ++i) {
        printf("Running tests for URI: %s\n", uriArray[i]);
        struct Uri *uri = uriCreate(uriArray[i]);
        if (uri == NULL) {
            printf("Failed to parse URI\n");
            result = 1;
        } else {
            printf("Scheme: %s\n", uriGetScheme(uri));
            printf("User info: %s\n", uriGetUserInfo(uri));
            printf("Host: %s\n", uriGetHost(uri));
            printf("Port: %s\n", uriGetPort(uri));
            printf("Path: %s\n", uriGetPath(uri));
            printf("Query: %s\n", uriGetQuery(uri));
            printf("Fragment: %s\n", uriGetFragment(uri));
            printf("Full URI: %s\n", uriGetFullUri(uri));
            uriDestroy(uri);
            printf("\n\n");
        }

    }

    return result;
}