#include "gk_tutorial_jni_call_UnoNativeCall.h"
#include <stdio.h>

/*
 * Class:     gk_tutorial_jni_call_UnoNativeCall
 * Method:    unoMetodo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_gk_tutorial_jni_call_UnoNativeCall_unoMetodo(JNIEnv * pEnv, jclass clazz)
{
  printf("native unoMetodo\n");
}
