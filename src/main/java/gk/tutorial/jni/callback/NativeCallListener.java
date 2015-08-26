package gk.tutorial.jni.callback;

public interface NativeCallListener {

	public void onNativeVoidCall();

	public int onNativeStringCall(String arg);

}
