package com.example.myapplication

import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import kotlin.random.Random

class MainActivity : AppCompatActivity() {

    private lateinit var words: Array<String>
    private lateinit var letter : EditText
    private lateinit var guessButton : Button
    private lateinit var resetButton : Button
    private lateinit var image : ImageView
    private lateinit var wordToGuess : TextView

    private lateinit var images: Array<Int>
    private var randIndex = 0
    private var state = 1

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        define()
        startGame()
    }

    private fun define() {
        images = arrayOf(R.drawable.wisielec0, R.drawable.wisielec1, R.drawable.wisielec2,
            R.drawable.wisielec3, R.drawable.wisielec4, R.drawable.wisielec5, R.drawable.wisielec6,
            R.drawable.wisielec7, R.drawable.wisielec_win)
        words = resources.getStringArray(R.array.words)

        letter = findViewById(R.id.plain_text_input)
        guessButton = findViewById(R.id.button)
        resetButton = findViewById(R.id.reset_button)
        image = findViewById(R.id.imageView)
        wordToGuess = findViewById(R.id.word_to_guess)
    }

    fun startGame() {
        setRandomWord()
        image.setImageResource(R.drawable.wisielec0)
        state = 1;
        resetButton.isClickable = false
        guessButton.isClickable = true
    }

    fun guessLetter(view: View) {
        val let = letter.text.toString().first()
        if (letter.text != null && state < 8) {
            Toast.makeText(this, letter.text, Toast.LENGTH_SHORT).show()
            if (!verifyLetter(let)) {
                image.setImageResource(images[state])
                state++
            }
            if (!wordToGuess.text.contains('?')) {
                Toast.makeText(this, "Wygrałeś!!!", Toast.LENGTH_SHORT).show()
                wordToGuess.setTextColor(Color.GREEN)
                image.setImageResource(R.drawable.wisielec_win)
                guessButton.isClickable = false
                resetButton.isClickable = true
            }

        }
        if (state > 7){
            Toast.makeText(this, "Przegrałeś :(", Toast.LENGTH_SHORT).show()
            wordToGuess.text = words[randIndex]
            wordToGuess.setTextColor(Color.RED)
            guessButton.isClickable = false
            resetButton.isClickable = true
        }
        letter.setText("")

    }

    fun verifyLetter(let: Char) : Boolean {

        var goodGuess = false
        val newWord : CharArray = wordToGuess.text.toString().toCharArray()
        for (i in words[randIndex].indices) {
            if (words[randIndex][i] == let) {
                newWord[i] = let
                goodGuess = true
            }
        }
        wordToGuess.text = String(newWord)
        return goodGuess
    }

    fun setRandomWord() {
        randIndex = Random.nextInt(100) // losujemy index słowa
        val mysteryWord = mysteryWord(words[randIndex])
        wordToGuess.setTextColor(Color.WHITE)
        wordToGuess.text = mysteryWord
    }
    private fun mysteryWord(word : String): String {
        val mystery = word.toCharArray()
        for (i in word.indices) {
            if (word[i] != ' ') {
                mystery[i] = '?'
            }
        }
        return String(mystery)
    }

    fun newGame(view: View) {
        startGame()
    }
}