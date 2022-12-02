package com.example.guessthenumber

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.TextView

class GameActivity : AppCompatActivity() {
    var begin: Int = 0
    var end: Int = 100
    var number: Int = -1
    var guessStatus = false
    lateinit var tvQuestion: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_game)
        tvQuestion = findViewById<TextView>(R.id.question)
        begin = intent.getIntExtra("begin", 0)
        end = intent.getIntExtra("end", 100)
        Log.d("mytag", "begin = $begin")
        Log.d("mytag", "end = $end")
        if(end - begin > 1){
            number = ((end - begin) / 2 + begin)
            tvQuestion.text = "is your number above $number ?"
        }else{
            val intent = Intent(this, MainActivity::class.java)
            intent.putExtra("wrongRange", "you enter wrong range")
            startActivity(intent)
        }
    }

    fun onYesNoClick(view: View) {
        tvQuestion = findViewById<TextView>(R.id.question)
        if(!guessStatus){
            when (view.id) {
                R.id.yes -> {
                    Log.d("mytag", "yes")
                    begin = number
                }
                R.id.no -> {
                    Log.d("mytag", "no")
                    end = number
                }
            }
            if(end - begin == 1){
                number = end
                guessStatus = true
                tvQuestion.text = "your number is $number"
            }else{
                number = (end - begin) / 2 + begin
                tvQuestion.text = "is number above $number ?"
                Log.d("mytag", "$begin - $end")
            }
        }
    }

    fun onRestartClick(view: View){
        val intent = Intent(this, MainActivity::class.java)
        startActivity(intent)
    }
}