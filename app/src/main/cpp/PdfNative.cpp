#include <jni.h>
#include <android/log.h>
#include <string>
#include <cstring>

// MuPDF header'ları
extern "C" {
    #include "mupdf_source/include/mupdf/fitz.h"
    #include "mupdf_source/include/mupdf/pdf.h"
}

#define LOG_TAG "PDFNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Global context
fz_context* ctx = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_com_arvinapp_pdfreader_PdfNative_initMuPDF(JNIEnv* env, jobject /* this */) {
    try {
        if (ctx == nullptr) {
            ctx = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
            if (ctx) {
                fz_register_document_handlers(ctx);
                LOGI("MuPDF initialized successfully");
            } else {
                LOGE("Failed to initialize MuPDF context");
            }
        }
    } catch (const std::exception& e) {
        LOGE("Exception in initMuPDF: %s", e.what());
    }
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_arvinapp_pdfreader_PdfNative_getTitle(JNIEnv* env, jobject /* this */, jstring path) {
    if (ctx == nullptr) {
        return env->NewStringUTF("Error: MuPDF not initialized");
    }

    const char* filePath = env->GetStringUTFChars(path, nullptr);
    if (!filePath) {
        return env->NewStringUTF("Error: Invalid file path");
    }

    try {
        fz_document* doc = fz_open_document(ctx, filePath);
        if (!doc) {
            env->ReleaseStringUTFChars(path, filePath);
            return env->NewStringUTF("Error: Cannot open document");
        }

        const char* title = fz_get_metadata(ctx, doc, FZ_META_INFO_TITLE);
        std::string result;
        
        if (title && strlen(title) > 0) {
            result = title;
        } else {
            // Dosya adından title oluştur
            const char* lastSlash = strrchr(filePath, '/');
            const char* fileName = lastSlash ? lastSlash + 1 : filePath;
            result = fileName;
        }

        fz_drop_document(ctx, doc);
        env->ReleaseStringUTFChars(path, filePath);

        return env->NewStringUTF(result.c_str());

    } catch (const std::exception& e) {
        LOGE("Exception in getTitle: %s", e.what());
        env->ReleaseStringUTFChars(path, filePath);
        return env->NewStringUTF("Error: Exception occurred");
    }
}

extern "C" JNIEXPORT jfloatArray JNICALL
Java_com_arvinapp_pdfreader_PdfNative_getPageSize(JNIEnv* env, jobject /* this */, 
                                                 jstring path, jint pageNum) {
    if (ctx == nullptr) {
        return nullptr;
    }

    const char* filePath = env->GetStringUTFChars(path, nullptr);
    if (!filePath) {
        return nullptr;
    }

    try {
        fz_document* doc = fz_open_document(ctx, filePath);
        if (!doc) {
            env->ReleaseStringUTFChars(path, filePath);
            return nullptr;
        }

        int totalPages = fz_count_pages(ctx, doc);
        if (pageNum < 0 || pageNum >= totalPages) {
            fz_drop_document(ctx, doc);
            env->ReleaseStringUTFChars(path, filePath);
            return nullptr;
        }

        fz_page* page = fz_load_page(ctx, doc, pageNum);
        fz_rect bounds;
        fz_bound_page(ctx, page, &bounds);

        jfloatArray result = env->NewFloatArray(2);
        jfloat dimensions[2] = {bounds.x1 - bounds.x0, bounds.y1 - bounds.y0};
        env->SetFloatArrayRegion(result, 0, 2, dimensions);

        fz_drop_page(ctx, page);
        fz_drop_document(ctx, doc);
        env->ReleaseStringUTFChars(path, filePath);

        return result;

    } catch (const std::exception& e) {
        LOGE("Exception in getPageSize: %s", e.what());
        env->ReleaseStringUTFChars(path, filePath);
        return nullptr;
    }
}

// JNI_OnLoad fonksiyonu
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    
    LOGI("PDFNative library loaded successfully");
    return JNI_VERSION_1_6;
}

// JNI_OnUnload fonksiyonu
JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved) {
    if (ctx) {
        fz_drop_context(ctx);
        ctx = nullptr;
        LOGI("MuPDF context cleaned up");
    }
}
