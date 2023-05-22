package com.example.myapplication

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ImageButton
import android.widget.Toast
import java.util.*
import kotlin.collections.ArrayList
import kotlin.random.Random


class MainActivity : AppCompatActivity() {

    private var bombNum = 17
    var boardSize = 9

    private var buttons =  arrayOf<ArrayList<ImageButton>>(
        arrayListOf(), arrayListOf(), arrayListOf(),arrayListOf(), arrayListOf(), arrayListOf(),
        arrayListOf(), arrayListOf(), arrayListOf()
    )

    // Arrays holding inforations about field
    private val isBomb = Array(boardSize) { BooleanArray(boardSize) }
    private val isUncovered = Array(boardSize) { BooleanArray(boardSize) }
    private val isFlagged = Array(boardSize) { BooleanArray(boardSize) }
    private val bombsNearby = Array(boardSize) { IntArray(boardSize) }

    val bombsPos = ArrayList<Int>()

    var setFlag = false
    var points = 0
    var maxPoints = boardSize * boardSize

    @SuppressLint("DiscouragedApi")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        for (i in 0 until 9) {
            for (j in 0 until 9) {
                val buttonID = "imageButton$i$j"
                val resId = resources.getIdentifier(buttonID, "id", packageName)
                buttons[i].add(findViewById(resId))
                isBomb[i][j] = false
                isUncovered[i][j] = false
                isFlagged[i][j] = false
                bombsNearby[i][j] = 0
            }
        }
        wypelnijPlansze()
    }



    fun wylosujBomby() {
        while (bombsPos.size < bombNum) {
            val rand = Random.nextInt(81)
            if (!bombsPos.contains(rand)) {
                bombsPos.add(rand)
                val i = rand / 9
                val j = rand % 9
                isBomb[i][j] = true
            }
        }
    }

    fun wypelnijPlansze() {
        wylosujBomby()
        for (b in bombsPos.indices){
            // (i, j) - pozycja bomby na planszy
            val i = bombsPos[b] / 9
            val j = bombsPos[b] % 9
            print("i: $i | j: $j\n")
            if (i > 0) {(bombsNearby[i-1][j])++}
            if (i < 8) {(bombsNearby[i+1][j])++}
            if (j > 0) {(bombsNearby[i][j-1])++}
            if (j < 8) {(bombsNearby[i][j+1])++}
            if (i > 0 && j < 8) {(bombsNearby[i-1][j+1])++}
            if (i > 0 && j > 0) {(bombsNearby[i-1][j-1])++}
            if (i < 8 && j > 0) {(bombsNearby[i+1][j-1])++}
            if (i < 8 && j < 8) {(bombsNearby[i+1][j+1])++}
        }

    }

    fun odkryjPole(i: Int, j: Int){
        isUncovered[i][j] = true
        buttons[i][j].isClickable = false
        isFlagged[i][j] = false
        points++
        if (isBomb[i][j])
            buttons[i][j].setImageResource(R.drawable.bomb)
        else if (bombsNearby[i][j] == 1)
            buttons[i][j].setImageResource(R.drawable.one)
        else if (bombsNearby[i][j] == 2)
            buttons[i][j].setImageResource(R.drawable.two)
        else if (bombsNearby[i][j] == 3)
            buttons[i][j].setImageResource(R.drawable.three)
        else if (bombsNearby[i][j] == 4)
            buttons[i][j].setImageResource(R.drawable.four)
        else if (bombsNearby[i][j] == 5)
            buttons[i][j].setImageResource(R.drawable.five)
        else if (bombsNearby[i][j] == 6)
            buttons[i][j].setImageResource(R.drawable.six)
        else if (bombsNearby[i][j] == 7)
            buttons[i][j].setImageResource(R.drawable.seven)
        else if (bombsNearby[i][j] == 8)
            buttons[i][j].setImageResource(R.drawable.eight)
        else if (bombsNearby[i][j] == 0)
            buttons[i][j].setImageResource(R.drawable.zero)
    }

    fun odkryjWszystkiePola(){
        for (i in 0 until 9) {
            for (j in 0 until 9) {
                odkryjPole(i, j)
            }
        }
    }

    fun odkryjSasiada(x : Int, y : Int) {
        isFlagged[x][y] = false
        if (bombsNearby[x][y] == 0) {
            odkryjSasiadow(x, y)
        }
        else {
            odkryjPole(x, y)
        }
    }


    fun odkryjSasiadow(i : Int, j : Int) {
        isUncovered[i][j] = true
        buttons[i][j].isClickable = false
        points++
        //sprawdz prawego sasiada
        buttons[i][j].setImageResource(R.drawable.zero)
        var x = i
        var y = j-1
        if (y >= 0 && !isUncovered[x][y]){
            odkryjSasiada(x,y)
        }

        //sprawdz prawego sasiada
        x = i
        y = j+1
        if (y < boardSize && !isUncovered[x][y]){
            odkryjSasiada(x,y)
        }
        //sprawdz dolnego sasiada
        x = i+1
        y = j
        if (x < boardSize && !isUncovered[x][y]){
            odkryjSasiada(x,y)

        }
        //sprawdz dolnego sasiada
        x = i-1
        y = j
        if (x >= 0 && !isUncovered[x][y]){
            odkryjSasiada(x,y)
        }
        //sprawdz NW sasiada
        x = i-1
        y = j-1
        if (x >= 0 && y >=0 && !isUncovered[x][y]){
            odkryjSasiada(x,y)
        }
        //sprawdz NE sasiada
        x = i-1
        y = j+1
        if (x >= 0 && y < boardSize && !isUncovered[x][y]){
            odkryjSasiada(x,y)
        }
        //sprawdz SW sasiada
        x = i+1
        y = j-1
        if (x < boardSize && y >=0 && !isUncovered[x][y]){
            odkryjSasiada(x,y)
        }
        //sprawdz SE sasiada
        x = i+1
        y = j+1
        if (x < boardSize && y < boardSize && !isUncovered[x][y]){
            odkryjSasiada(x,y)
        }
    }


    @SuppressLint("ResourceAsColor", "DiscouragedApi")
    fun zaznaczPole(view: View) {
        val id = view.resources.getResourceName(view.id);
        val len = id.length
        val i = id[len-2].digitToInt()  // char to int
        val j = id[len-1].digitToInt()  // char to int
        // Guzik nie był klikniety
        if (!isUncovered[i][j]) {
            // nie stawiamy flagi na pole i pole nie jest oflagowane
            if (!setFlag) {
                if (!isFlagged[i][j]) {
                    // jezeli na polu jest bomba to przegrywamy
                    if (isBomb[i][j]) {
                        odkryjWszystkiePola()
                        buttons[i][j].setImageResource(R.drawable.bumbum)
                        Toast.makeText(this, "Przegrałeś :(", Toast.LENGTH_SHORT).show()
                    }
                    else {
                        if (bombsNearby[i][j] == 0){
                            odkryjSasiadow(i, j)
                        }
                        else {
                            odkryjPole(i, j)
                        }

                    }
                }
            }
            // ustawiona flaga
            else {
                if (isFlagged[i][j]) {
                    isFlagged[i][j] = false
                    buttons[i][j].setImageResource(android.R.color.transparent)
                    if (isBomb[i][j])
                        points--
                }
                else {
                    isFlagged[i][j] = true
                    buttons[i][j].setImageResource(R.drawable.flag)
                    if (isBomb[i][j])
                        points++
                }
            }
            if (points == 81) {
                Toast.makeText(this, "Wygrałeś!!!", Toast.LENGTH_SHORT).show()
                odkryjWszystkiePola()
            }
        }
    }

    fun nowaGra(view: View) {
            for (i in 0 until 9) {
                for (j in 0 until 9) {
                    buttons[i][j].setImageResource(android.R.color.transparent)
                    isBomb[i][j] = false
                    isUncovered[i][j] = false
                    isFlagged[i][j] = false
                    bombsNearby[i][j] = 0
                    buttons[i][j].isClickable = true
                }
            }
            points = 0
            bombsPos.clear()
            wylosujBomby()
            wypelnijPlansze()
    }

    fun setFlag(view: View) {
        if (setFlag) {
            setFlag = false
            findViewById<ImageButton>(R.id.flagButton).alpha = 0.5F
        }
        else {
            setFlag = true
            findViewById<ImageButton>(R.id.flagButton).alpha = 1.0F
        }

    }
}