package com.example.calendar

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.navigation.ActivityNavigator

class AddEventActivity : AppCompatActivity() {

    lateinit var titleView: EditText
    lateinit var notesView: EditText

    @SuppressLint("MissingInflatedId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_event)
        define()
        val date = intent.getStringExtra("date")
        findViewById<TextView>(R.id.date).text = date
    }

    fun define() {
        titleView = findViewById(R.id.title_edit_view)
        notesView = findViewById(R.id.notes_edit_view)
    }

    fun accept(view: View) {
        val title = titleView.text.toString()
        val notes = notesView.text.toString()
        Log.i("TITLE", title)
        Log.i("TITLE_NOTES", notes)

        val myIntent = Intent()
        myIntent.putExtra("event_title", title)
        myIntent.putExtra("event_notes", notes)
        myIntent.putExtra("button_type", "accept")
        setResult(Activity.RESULT_OK, myIntent)
        finish()
    }

    fun back(view: View) {
        val backIntent = Intent()
        backIntent.putExtra("button_type", "back")
        setResult(Activity.RESULT_OK, backIntent)
        finish()
    }


}