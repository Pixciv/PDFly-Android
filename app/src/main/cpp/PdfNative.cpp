#include <jni.h>
#include <string>
#include <android/log.h>

// MuPDF core header
extern "C" {
#include "mupdf/fitz.h"
}

#define LOG_TAG "PdfNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Global context
static fz_context *ctx = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_arvinapp_pdfreader_PdfNative_initMuPDF(JNIEnv *env, jobject thiz) {
    if (!ctx) {
        ctx = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
        if (!ctx) {
            LOGI("Failed to create MuPDF context!");
        } else {
            LOGI("MuPDF context initialized.");
        }
    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_arvinapp_pdfreader_PdfNative_getTitle(JNIEnv *env, jobject thiz, jstring jpath) {
    if (!ctx) {
        return env->NewStringUTF("MuPDF not initialized");
    }

    const char *path = env->GetStringUTFChars(jpath, nullptr);

    fz_document *doc = nullptr;
    fz_try(ctx) {
        doc = fz_open_document(ctx, path);
    } fz_catch(ctx) {
        env->ReleaseStringUTFChars(jpath, path);
        return env->NewStringUTF("Error opening PDF");
    }

    char title[256] = {0};
    fz_lookup_metadata(ctx, doc, FZ_META_INFO_TITLE, title, sizeof(title));

    fz_drop_document(ctx, doc);
    env->ReleaseStringUTFChars(jpath, path);

    if (strlen(title) == 0) {
        return env->NewStringUTF("No title");
    }

    return env->NewStringUTF(title);
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_arvinapp_pdfreader_PdfNative_getPageSize(JNIEnv *env, jobject thiz, jstring jpath, jint page_num) {
    if (!ctx) {
        return nullptr;
    }

    const char *path = env->GetStringUTFChars(jpath, nullptr);
    fz_document *doc = nullptr;
    fz_page *page = nullptr;
    jobjectArray result = nullptr;

    fz_try(ctx) {
        doc = fz_open_document(ctx, path);
        int page_count = fz_count_pages(ctx, doc);
        if (page_num < 0 || page_num >= page_count) {
            fz_throw(ctx, FZ_ERROR_GENERIC, "Page out of range");
        }
        page = fz_load_page(ctx, doc, page_num);
        fz_rect rect;
        fz_bound_page(ctx, page, &rect);

        result = env->NewObjectArray(2, env->FindClass("java/lang/Float"), nullptr);
        jclass floatClass = env->FindClass("java/lang/Float");
        jmethodID floatInit = env->GetMethodID(floatClass, "<init>", "(F)V");

        jobject w = env->NewObject(floatClass, floatInit, (jfloat)rect.x1);
        jobject h = env->NewObject(floatClass, floatInit, (jfloat)rect.y1);

        env->SetObjectArrayElement(result, 0, w);
        env->SetObjectArrayElement(result, 1, h);

        fz_drop_page(ctx, page);
        fz_drop_document(ctx, doc);
    } fz_always(ctx) {
        env->ReleaseStringUTFChars(jpath, path);
    } fz_catch(ctx) {
        LOGI("Error getting page size");
    }

    return result;
}
