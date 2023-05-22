package com.example.zad1

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView
import android.widget.Toast
import kotlin.random.Random

class MainActivity : AppCompatActivity() {

    private var score = 0
    private var r1 = 0
    private var r2 = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        score = 0
        roll()
    }

    @SuppressLint("SetTextI18n")
    private fun roll() {
        findViewById<TextView>(R.id.points).text = "Punkty: $score"
        r1 = Random.nextInt(10)
        r2 = Random.nextInt(10)
        findViewById<TextView>(R.id.leftClick).text = "" + r1
        findViewById<TextView>(R.id.rightClick).text = "" + r2
    }

    fun buttonLeft(view: View) {
        if (r1>=r2){
            score++
            Toast.makeText(this, "Dobrze :)", Toast.LENGTH_SHORT).show()
        }
        else {
            score--
            Toast.makeText(this, "Źle :(", Toast.LENGTH_SHORT).show()
        }
        roll()
    }
    fun buttonRight(view: View) {
        if (r2>=r1){
            score++
            Toast.makeText(this, "Dobrze :)", Toast.LENGTH_SHORT).show()
        }
        else {
            score--
            Toast.makeText(this, "Źle :(", Toast.LENGTH_SHORT).show()
        }
        roll()
    }
}