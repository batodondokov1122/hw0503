package com.example.guessthenumber

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val wrongRange = intent.getStringExtra("wrongRange")
        if (wrongRange == "you enter wrong range"){
            val tvWrongRange = findViewById<TextView>(R.id.wrongRange)
            tvWrongRange.text = wrongRange
        }
    }
    fun onGuessClick(view: View) {
        val begin = findViewById<TextView>(R.id.begin)
        val end = findViewById<TextView>(R.id.end)
        val strBegin = begin.text.toString()
        val strEnd = end.text.toString()

        val intent = Intent(this, GameActivity::class.java)
        intent.putExtra("begin", strBegin.toInt())
        intent.putExtra("end", strEnd.toInt())
        startActivity(intent)

    }
}