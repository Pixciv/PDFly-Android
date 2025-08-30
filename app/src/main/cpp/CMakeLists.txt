cmake_minimum_required(VERSION 3.22.1)

project(pdfnative)

# C++ standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JNI için include dizinleri
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# Eğer ileride MuPDF kaynaklarını ekleyeceksek buraya path ekleyeceğiz
# örn: include_directories(${CMAKE_SOURCE_DIR}/mupdf/include)

# Native kaynak dosyalarımız
add_library(
    pdfnative
    SHARED
    PdfNative.cpp
)

# log kütüphanesi (Android logcat için)
find_library(
    log-lib
    log
)

# Bağlantılar
target_link_libraries(
    pdfnative
    ${log-lib}
)
