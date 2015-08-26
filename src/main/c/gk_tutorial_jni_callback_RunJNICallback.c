
#include "gk_tutorial_jni_callback_RunJNICallback.h"
#include <stdio.h>
#include <pthread.h>

// global pointer to gk.tutorial.jni.callback.NativeCallListener instance
static jobject pNativeCallListenerRef = 0;
// method descriptors for class gk.tutorial.jni.callback.NativeCallListener
static jmethodID mOnNativeVoidCall;
static jmethodID mOnNativeStringCall;

static JavaVM * jvm;

/*
 * get current JavaVM and attach to java java thread
 */
JNIEnv * get_JNIEnv() {
  JavaVMAttachArgs attachArgs;
  attachArgs.version = JNI_VERSION_1_6; // no 1_7 version in jni.h
  attachArgs.name = ">>>NativeThread_Any"; // java: Thread.currentThread().getName()
  attachArgs.group = NULL;

  JNIEnv * env;
  if ( (*jvm)->AttachCurrentThread(jvm, (void**) &env, &attachArgs) != JNI_OK) {
    env = NULL;
  }

  return env;
}

/**
 * run this function in native pthread
 */
void * pthread_function(void) {
  JNIEnv * jniEnv = get_JNIEnv();
  jstring jStr = (*jniEnv)->NewStringUTF(jniEnv, "utf str from native!");
  jint i, res;

  for (i = 0; i<10; i++) {
    res = (*jniEnv)->CallIntMethod(jniEnv, pNativeCallListenerRef, mOnNativeStringCall, jStr);
  }

  printf("native pthread: invokeCallbackFromNative, invocations: %d, last res: %d\n", i, res);

  pthread_exit(0); // terminate pthread
}

/*
 * Class:     gk_tutorial_jni_callback_RunJNICallback
 * Method:    registerCallback
 * Signature: (Lgk/tutorial/jni/callback/NativeCallListener;)V
 */
JNIEXPORT void JNICALL Java_gk_tutorial_jni_callback_RunJNICallback_registerCallback(JNIEnv * pEnv, jclass clazz, jobject pNativeCallListener)
{
  jclass cNativeCallListener;

  // save JavaVM to use in callbacks
  (*pEnv)->GetJavaVM(pEnv, &jvm);

  // take gk.tutorial.jni.callback.NativeCallListener.class object
  cNativeCallListener = (*pEnv)->GetObjectClass(pEnv, pNativeCallListener);

  // take method descriptors
  mOnNativeVoidCall = (*pEnv)->GetMethodID(pEnv, cNativeCallListener, "onNativeVoidCall", "()V");
  mOnNativeStringCall = (*pEnv)->GetMethodID(pEnv, cNativeCallListener, "onNativeStringCall", "(Ljava/lang/String;)I");

  pNativeCallListenerRef = (*pEnv)->NewGlobalRef(pEnv, pNativeCallListener);

  printf("NATIVE: registerCallback\n");

  // start native thread
  pthread_t thread_ptr_1, thread_ptr_2;
  pthread_create(&thread_ptr_1, NULL, (void * (*) (void *)) &pthread_function, NULL);
  pthread_create(&thread_ptr_2, NULL, (void * (*) (void *)) &pthread_function, NULL);
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




