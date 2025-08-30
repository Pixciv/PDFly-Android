#include <jni.h>
#include <android/log.h>
#include <string>

#define LOG_TAG "PDFNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL
Java_com_arvinapp_pdfreader_PdfNative_initMuPDF(JNIEnv* env, jobject /* this */) {
    LOGI("MuPDF initialization called (stub)");
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_arvinapp_pdfreader_PdfNative_getTitle(JNIEnv* env, jobject /* this */, jstring path) {
    return env->NewStringUTF("Test Title");
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_com_arvinapp_pdfreader_PdfNative_getPageSize(JNIEnv* env, jobject /* this */, jstring path, jint pageNum) {
    jfloatArray result = env->NewFloatArray(2);
    jfloat dimensions[2] = {595.0f, 842.0f}; // A4 size
    env->SetFloatArrayRegion(result, 0, 2, dimensions);
    return result;
}
