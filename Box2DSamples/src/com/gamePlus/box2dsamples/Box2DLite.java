package com.gamePlus.box2dsamples;

import android.os.Bundle;
import android.view.MotionEvent;
import android.app.Activity;

public class Box2DLite extends Activity {

	static {
        System.loadLibrary("gl2jni");
    }
	
   GL2JNIView mView;

   @Override protected void onCreate(Bundle icicle) {
       super.onCreate(icicle);
		System.out.println("GL2JNIActivity status: onStart");
       mView = new GL2JNIView(getApplication());
	setContentView(mView);
   }

   @Override protected void onPause() {
		super.onPause();
		System.out.println("GL2JNIActivity status: onPause");
       mView.onPause();
   }

   @Override protected void onResume() {
       super.onResume();
		System.out.println("GL2JNIActivity status: onResume");
       mView.onResume();
   }
	@Override protected void onStop() {
	 super.onStop();
		System.out.println("GL2JNIActivity status: onStop");
	}
	@Override protected void onStart() {
		super.onStart();
		System.out.println("GL2JNIActivity status: onStart");
	}
	@Override protected void onDestroy() {
		super.onDestroy();
		System.out.println("GL2JNIActivity status: onDestroy");
	}
	@Override protected void onRestart() {
		super.onRestart();
		System.out.println("GL2JNIActivity status: onRestart");
	}
	@Override
    public boolean onTouchEvent(MotionEvent e) {
    	touch((int)e.getX(),(int)e.getY());
    	return super.onTouchEvent(e);
}

public static native void init(int width, int height);
public static native void step();
public static native void touch(int x, int y);
}
