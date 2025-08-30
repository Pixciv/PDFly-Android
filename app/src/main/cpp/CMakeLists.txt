cmake_minimum_required(VERSION 3.18.1)

project("pdfnative")

# C++ standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tüm MuPDF kaynak dosyalarını otomatik olarak bul
file(GLOB MUPDF_SOURCES
    "mupdf_source/source/fitz/*.c"
    "mupdf_source/source/pdf/*.c"
    "mupdf_source/source/xps/*.c"
)

# MuPDF static library
add_library(
    mupdf_lib
    STATIC
    ${MUPDF_SOURCES}
)

# MuPDF include dizinleri
target_include_directories(
    mupdf_lib
    PUBLIC
    mupdf_source/include
)

# Ana native library
add_library(
    pdfnative
    SHARED
    PdfNative.cpp
)

# log kütüphanesi
find_library(log-lib log)

# Bağlantılar
target_link_libraries(
    pdfnative
    mupdf_lib
    ${log-lib}
)

# Derleyici flag'leri - uyarıları kapat
target_compile_options(mupdf_lib PRIVATE -w)
target_compile_options(pdfnative PRIVATE -w)
