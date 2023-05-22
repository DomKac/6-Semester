package com.example.kamien_papier_nozyce

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import kotlin.random.Random

class MainActivity : AppCompatActivity() {

    private var player_score = 0
    private var comp_score = 0

//    private var player_image = findViewById<ImageView>(R.id.playerImage)
//    private var comp_image = findViewById<ImageView>(R.id.compImage)

    private var player_choice = -1
    private var comp_choice = -1
    // 0 -> kamien
    // 1 -> papier
    // 2 -> nozyce


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        player_score = 0
        comp_score = 0
        update_points()
    }

    @SuppressLint("SetTextI18n")
    private fun update_points() {
        findViewById<TextView>(R.id.playerPoints).text = "" + player_score
        findViewById<TextView>(R.id.compPoints).text = "" + comp_score
    }

    // kamien -> 0
    fun play_kamien(view: View) {
        comp_choice = Random.nextInt(3) // wybór komputera
        findViewById<ImageView>(R.id.playerImage).setImageResource(R.drawable.kamien)
        if (comp_choice == 0) {
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.kamien)
            Toast.makeText(this, "Remis", Toast.LENGTH_SHORT).show()
        }
        else if (comp_choice == 1) {
            comp_score++
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.papier)
            Toast.makeText(this, "Komputer wygrał :(", Toast.LENGTH_SHORT).show()
        }
        else {
            player_score++
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.nozyce)
            Toast.makeText(this, "Wygrałeś!!! :)", Toast.LENGTH_SHORT).show()
        }
        update_points()
    }

    // papier -> 1
    fun play_papier(view: View) {
        comp_choice = Random.nextInt(3) // wybór komputera
        findViewById<ImageView>(R.id.playerImage).setImageResource(R.drawable.papier)
        if (comp_choice == 1) {
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.papier)
            Toast.makeText(this, "Remis", Toast.LENGTH_SHORT).show()
        }
        else if (comp_choice == 2) {
            comp_score++
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.nozyce)
            Toast.makeText(this, "Komputer wygrał :(", Toast.LENGTH_SHORT).show()
        }
        else {
            player_score++
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.kamien)
            Toast.makeText(this, "Wygrałeś!!! :)", Toast.LENGTH_SHORT).show()
        }
        update_points()
    }

    // nożyce -> 2
    fun play_nozyce(view: View) {
        comp_choice = Random.nextInt(3) // wybór komputera
        findViewById<ImageView>(R.id.playerImage).setImageResource(R.drawable.nozyce)
        if (comp_choice == 2) {
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.nozyce)
            Toast.makeText(this, "Remis", Toast.LENGTH_SHORT).show()
        }
        else if (comp_choice == 0) {
            comp_score++
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.kamien)
            Toast.makeText(this, "Komputer wygrał :(", Toast.LENGTH_SHORT).show()
        }
        else {
            player_score++
            findViewById<ImageView>(R.id.compImage).setImageResource(R.drawable.papier)
            Toast.makeText(this, "Wygrałeś!!! :)", Toast.LENGTH_SHORT).show()
        }
        update_points()
    }

    fun resetButton(view: View) {
        player_score = 0
        comp_score = 0
        update_points()
        findViewById<ImageView>(R.id.compImage).setImageResource(R.mipmap.ic_launcher_round)
        findViewById<ImageView>(R.id.playerImage).setImageResource(R.drawable.steve)
    }
}