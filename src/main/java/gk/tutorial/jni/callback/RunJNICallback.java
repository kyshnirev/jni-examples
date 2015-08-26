package gk.tutorial.jni.callback;

import java.io.File;
import java.util.concurrent.atomic.AtomicInteger;

public class RunJNICallback {

	public static native void registerCallback(NativeCallListener listener);

	public static native void invokeCallbackFromNative(String str);

	public static void main(String[] args) throws InterruptedException {

		System.load(new File("bin/callback.so").getAbsolutePath());

		registerCallback(new NativeCallListener() {
			AtomicInteger count = new AtomicInteger();
			@Override
			public void onNativeVoidCall() {
				System.out.println("onNativeVoidCall: this="+ this);
			}
			@Override
			public int onNativeStringCall(String arg) {
				int res = count.incrementAndGet();
				System.out.println("onNativeStringCall: this="+ this
						+" arg="+ arg
						+"; thread.id="+ Thread.currentThread().getId()
						+"; thread.name="+ Thread.currentThread().getName()
						+"; return "+ res);
				return res;
			}
		});

		invokeCallbackFromNative("string-from-java");


		Thread.sleep(1000);
		System.out.println("JAVA END.");
	}

}
