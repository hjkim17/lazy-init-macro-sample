#include <stdio.h>
#include <openssl/err.h>
#include <openssl/rand.h>

class crypto_gv_init_test {
private:
    int retVal;
    unsigned char *buffer;
public:
    crypto_gv_init_test(int arg1, int arg2) {
        printf("%d %d",arg1,arg2);
        int i;
        int length = 64;
        printf("Before RAND_bytes in INIT_ARRAY processing\n");
        // eventually call __pthread_key_create in RAND_bytes
        buffer = (unsigned char*)malloc(sizeof(unsigned char) * length);
        retVal = RAND_bytes(buffer, length);
        printf("After RAND_bytes in INIT_ARRAY processing, buffer:");
        for(i = 0; i < length; i++)
            printf(" %3d", buffer[i]);
        printf("\n");
    }
};
////////////////////////////////////////////////////////
// global variable to call RAND_Bytes in the constructor
#define _GLOBAL_DECLARE_ARGS(GV_typ, GV_fn_name, GV_var, ...) \
GV_typ* GV_fn_name##GV_ptr = 0; \
GV_typ& GV_fn_name() { \
    if(GV_fn_name##GV_ptr) { \
        return *(GV_fn_name##GV_ptr); \
    } \
    static GV_typ GV_var(__VA_ARGS__); \
    (GV_fn_name##GV_ptr) = &GV_var; \
    return GV_var; \
}

_GLOBAL_DECLARE_ARGS(crypto_gv_init_test, _FN_A, _A, printf("test"), 2.2)
#define _GV_A _FN_A()
////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    _GV_A;
    _GV_A;
    _GV_A;
    _GV_A;
    int i;
    int retVal = 0;
    int length = 64;
    printf("Before RAND_bytes in main\n");
    unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char) * length);
    retVal = RAND_bytes(buffer, length);
    if(retVal<=0) {
        printf("Error Occurs!\n");
        printf("retVal: %d", retVal);
        printf("ERR_get_error(): %ld", ERR_get_error());
        return 1;
    }
    printf("After RAND_bytes in main, buffer:");
    for(i = 0; i < length; i++)
        printf(" %3d", buffer[i]);
    printf("\n");
    return 0;
}