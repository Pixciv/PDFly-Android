package com.arvinapp.pdfreader

object PdfNative {
    init {
        System.loadLibrary("pdfnative")
    }

    external fun initMuPDF()
    external fun getTitle(path: String): String
    external fun getPageSize(path: String, pageNum: Int): Array<Float>
}
