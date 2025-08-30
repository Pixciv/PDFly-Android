cmake_minimum_required(VERSION 3.18.1)

project("pdfnative")

# C++ standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MuPDF kaynak dosyaları
add_library(
    mupdf_lib
    STATIC
    mupdf_source/source/fitz/archive.c
    mupdf_source/source/fitz/bidi.c
    mupdf_source/source/fitz/bitmap.c
    mupdf_source/source/fitz/blend.c
    mupdf_source/source/fitz/buffer.c
    mupdf_source/source/fitz/color.c
    mupdf_source/source/fitz/context.c
    mupdf_source/source/fitz/crypt.c
    mupdf_source/source/fitz/device.c
    mupdf_source/source/fitz/document.c
    mupdf_source/source/fitz/display-list.c
    mupdf_source/source/fitz/draw-device.c
    mupdf_source/source/fitz/filter.c
    mupdf_source/source/fitz/font.c
    mupdf_source/source/fitz/glyph.c
    mupdf_source/source/fitz/hash.c
    mupdf_source/source/fitz/image.c
    mupdf_source/source/fitz/interpret.c
    mupdf_source/source/fitz/list.c
    mupdf_source/source/fitz/math.c
    mupdf_source/source/fitz/memory.c
    mupdf_source/source/fitz/output.c
    mupdf_source/source/fitz/path.c
    mupdf_source/source/fitz/pixmap.c
    mupdf_source/source/fitz/printf.c
    mupdf_source/source/fitz/shade.c
    mupdf_source/source/fitz/stext.c
    mupdf_source/source/fitz/store.c
    mupdf_source/source/fitz/string.c
    mupdf_source/source/fitz/strtod.c
    mupdf_source/source/fitz/struc.c
    mupdf_source/source/fitz/tree.c
    mupdf_source/source/fitz/unzip.c
    mupdf_source/source/fitz/util.c
    mupdf_source/source/fitz/xml.c
    mupdf_source/source/pdf/pdf-annot.c
    mupdf_source/source/pdf/pdf-appearance.c
    mupdf_source/source/pdf/pdf-clean.c
    mupdf_source/source/pdf/pdf-cmap.c
    mupdf_source/source/pdf/pdf-colorspace.c
    mupdf_source/source/pdf/pdf-crypt.c
    mupdf_source/source/pdf/pdf-device.c
    mupdf_source/source/pdf/pdf-document.c
    mupdf_source/source/pdf/pdf-encode.c
    mupdf_source/source/pdf/pdf-font.c
    mupdf_source/source/pdf/pdf-form.c
    mupdf_source/source/pdf/pdf-graft.c
    mupdf_source/source/pdf/pdf-image.c
    mupdf_source/source/pdf/pdf-interpret.c
    mupdf_source/source/pdf/pdf-lex.c
    mupdf_source/source/pdf/pdf-mod.c
    mupdf_source/source/pdf/pdf-nametree.c
    mupdf_source/source/pdf/pdf-object.c
    mupdf_source/source/pdf/pdf-op-run.c
    mupdf_source/source/pdf/pdf-page.c
    mupdf_source/source/pdf/pdf-parse.c
    mupdf_source/source/pdf/pdf-pattern.c
    mupdf_source/source/pdf/pdf-pkcs7.c
    mupdf_source/source/pdf/pdf-run.c
    mupdf_source/source/pdf/pdf-shade.c
    mupdf_source/source/pdf/pdf-signature.c
    mupdf_source/source/pdf/pdf-store.c
    mupdf_source/source/pdf/pdf-type3.c
    mupdf_source/source/pdf/pdf-unicode.c
    mupdf_source/source/pdf/pdf-write.c
    mupdf_source/source/pdf/pdf-xobject.c
    mupdf_source/source/pdf/pdf.c
    mupdf_source/source/xps/xps-common.c
    mupdf_source/source/xps/xps-doc.c
    mupdf_source/source/xps/xps-glyphs.c
    mupdf_source/source/xps/xps-gradient.c
    mupdf_source/source/xps/xps-image.c
    mupdf_source/source/xps/xps-link.c
    mupdf_source/source/xps/xps-outline.c
    mupdf_source/source/xps/xps-path.c
    mupdf_source/source/xps/xps-resource.c
    mupdf_source/source/xps/xps-util.c
    mupdf_source/source/xps/xps-zip.c
    mupdf_source/source/xps/xps.c
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

# Derleyici flag'leri
target_compile_options(mupdf_lib PRIVATE -w)
target_compile_options(pdfnative PRIVATE -w)
