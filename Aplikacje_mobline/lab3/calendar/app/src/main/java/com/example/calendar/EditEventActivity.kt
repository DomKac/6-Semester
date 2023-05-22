package com.example.calendar

import android.app.Activity
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView

class EditEventActivity : AppCompatActivity() {

    lateinit var titleView: TextView
    lateinit var dateView: TextView
    lateinit var notesView: TextView
    lateinit var event: Event

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit_event)
        define()
//        val eventTitle = intent.getStringExtra("event_title")
//        val eventDate = intent.getStringExtra("event_date")
//        val eventNotes = intent.getStringExtra("event_notes")


        titleView.text = event.getTitle()
        dateView.text = event.getDate()
        notesView.text = event.getNotes()
    }

    private fun define() {
        titleView = findViewById(R.id.title_head)
        dateView = findViewById(R.id.date_head)
        notesView = findViewById(R.id.notes_edit_view)
        event = (intent.getSerializableExtra("event") as? Event)!!
    }

    fun back(view: View) {
        finish()
    }

    fun edit(view: View) {

    }

    fun delete(view: View) {
        val myIntent = Intent()
        myIntent.putExtra("button_type", "delete")
        myIntent.putExtra("event_to_delete", event)
        val pos = intent.getIntExtra("position", 0)
        myIntent.putExtra("position", pos)
        setResult(Activity.RESULT_OK, myIntent)
        finish()

    }


}