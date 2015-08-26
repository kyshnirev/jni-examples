
#include "gk_tutorial_jni_callback_RunJNICallback.h"
#include <stdio.h>

// library local
// global pointer to gk.tutorial.jni.callback.NativeCallListener instance
static jobject pNativeCallListenerRef = 0;
// method descriptors for class gk.tutorial.jni.callback.NativeCallListener
static jmethodID mOnNativeVoidCall;
static jmethodID mOnNativeStringCall;

/*
 * Class:     gk_tutorial_jni_callback_RunJNICallback
 * Method:    registerCallback
 * Signature: (Lgk/tutorial/jni/callback/NativeCallListener;)V
 */
JNIEXPORT void JNICALL Java_gk_tutorial_jni_callback_RunJNICallback_registerCallback(JNIEnv * pEnv, jclass clazz, jobject pNativeCallListener)
{
  jclass cNativeCallListener;

  printf("NATIVE: registerCallback begin\n");

  // take gk.tutorial.jni.callback.NativeCallListener.class object
  cNativeCallListener = (*pEnv)->GetObjectClass(pEnv, pNativeCallListener);

  // take method descriptors
  mOnNativeVoidCall = (*pEnv)->GetMethodID(pEnv, cNativeCallListener, "onNativeVoidCall", "()V");
  mOnNativeStringCall = (*pEnv)->GetMethodID(pEnv, cNativeCallListener, "onNativeStringCall", "(Ljava/lang/String;)I");

  pNativeCallListenerRef = (*pEnv)->NewGlobalRef(pEnv, pNativeCallListener);

  printf("NATIVE: registerCallback end\n");
}

/*
 * Class:     gk_tutorial_jni_callback_RunJNICallback
 * Method:    invokeCallbackFromNative
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gk_tutorial_jni_callback_RunJNICallback_invokeCallbackFromNative(JNIEnv * pEnv, jclass clazz, jstring pString)
{
  jint res;

  // invoke methods by descriptors on instance: pNativeCallListenerRef
  (*pEnv)->CallVoidMethod(pEnv, pNativeCallListenerRef, mOnNativeVoidCall);
  res = (*pEnv)->CallIntMethod(pEnv, pNativeCallListenerRef, mOnNativeStringCall, pString);

  printf("invokeCallbackFromNative, res: %d\n", res);
}





