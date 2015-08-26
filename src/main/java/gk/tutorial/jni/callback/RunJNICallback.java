package gk.tutorial.jni.callback;

import java.io.File;

public class RunJNICallback {

	public static native void registerCallback(NativeCallListener listener);

	public static native void invokeCallbackFromNative(String str);

	public static void main(String[] args) {

		System.load(new File("bin/callback.so").getAbsolutePath());

		registerCallback(new NativeCallListener() {
			int count = 0;
			@Override
			public void onNativeVoidCall() {
				System.out.println("onNativeVoidCall: this="+ this);
			}
			@Override
			public int onNativeStringCall(String arg) {
				count ++;
				System.out.println("onNativeStringCall: this="+ this +" arg="+ arg +"; return "+ count);
				return count;
			}
		});

		invokeCallbackFromNative("string-from-java");

	}

}
