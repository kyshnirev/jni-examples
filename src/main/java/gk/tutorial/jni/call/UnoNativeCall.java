package gk.tutorial.jni.call;

import java.io.File;

/**
 * native methods implementation: src/main/c/gk_tutorial_jni_call_UnoNativeCall.c
 */
public class UnoNativeCall {

	public static void loadLibrary() {
		String libPath = new File("bin/unolibo.so").getAbsolutePath();
		System.out.println("UnoNativeCall: load library from "+ libPath);
		System.load(libPath);
	}

	public static native void unoMetodo();

}
