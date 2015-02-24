#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../Include/Application.h"


extern "C" {
    JNIEXPORT void JNICALL Java_com_gamePlus_box2dsamples_Box2DLite_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_gamePlus_box2dsamples_Box2DLite_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_gamePlus_box2dsamples_Box2DLite_touch(JNIEnv * env, jobject obj, jint x, jint y);
};

JNIEXPORT void JNICALL Java_com_gamePlus_box2dsamples_Box2DLite_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	Application::Instance()->init(width, height);
}

JNIEXPORT void JNICALL Java_com_gamePlus_box2dsamples_Box2DLite_step(JNIEnv * env, jobject obj)
{
	Application::Instance()->update();
	Application::Instance()->draw();

}

JNIEXPORT void JNICALL Java_com_gamePlus_box2dsamples_Box2DLite_touch(JNIEnv * env, jobject obj, jint x, jint y)
{
    Application::Instance()->mouseReleased(x,y);
}
