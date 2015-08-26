package gk.tutorial.jni.call;

public class RunJNINative {

	public static void main(String[] args) {

		UnoNativeCall.loadLibrary(); // native library load

		UnoNativeCall.unoMetodo(); // native method call

	}

}
