#include <mod/amlmod.h>
#include <dlfcn.h>

MYMOD(psvita.fuzzyseek, FuzzySeek, 1.0, TheOfficialFloW)

void* pGameHandle = NULL;
DECL_HOOK(int, mpg123_param, void* mh, int key, long val, int ZERO, double fval)
{
    val |= 0x200 | 0x100 | 0x40;
    return mpg123_param(mh, key, val, ZERO, fval);
}
extern "C" void OnModPreLoad()
{
    pGameHandle = dlopen("libGTASA.so", RTLD_LAZY);
    if(pGameHandle == NULL) pGameHandle = dlopen("libGTAVC.so", RTLD_LAZY);
    if(pGameHandle != NULL)
    {
        HOOK(mpg123_param, aml->GetSym(pGameHandle, "mpg123_param"));
    }
}