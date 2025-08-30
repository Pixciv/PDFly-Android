package com.arvinapp.pdfreader

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import android.view.Gravity
import android.view.ViewGroup.LayoutParams

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // MuPDF'yi başlat
        PdfNative.initMuPDF()

        val textView = TextView(this).apply {
            text = "PDF Reader with MuPDF\n\nNative library loaded successfully!"
            textSize = 24f
            gravity = Gravity.CENTER
            layoutParams = LayoutParams(
                LayoutParams.MATCH_PARENT,
                LayoutParams.MATCH_PARENT
            )
        }

        setContentView(textView)
    }
}
