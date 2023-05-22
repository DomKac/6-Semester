package com.example.calendar

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.CalendarView
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.size
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import java.util.*

class MainActivity : AppCompatActivity() {

    lateinit var calendar : CalendarView
    lateinit var addButton : Button
    lateinit var date : String
    private var selectedDate: String? = null // zmienna przechowująca aktualnie wybraną datę
    lateinit var recyclerView : RecyclerView
    private val eventList : MutableList<Event> = mutableListOf()

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        define()
        Log.i("DUPA", "onCreate")
    }
//
//    override fun onResume() {
//        super.onResume()
//        if (eventList != null) {
//            recyclerView.layoutManager.onRestoreInstanceState(eventList)
//        }
//    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        Log.i("OBROT", "zmieniono poziom ekranu")
        // konwertujemy MutableList<Event> na ArrayList<String>
//        outState.putStringArrayList("eventList", ArrayList(eventList.map { it.toString() }))
        val size = recyclerView.size
        outState.putInt("arrayListSize", size)

        val titleList = eventList.map { it.getTitle() }
        val dateList = eventList.map { it.getDate() }
        val notesList = eventList.map { it.getNotes() }

        outState.putStringArrayList("titleList", ArrayList(titleList))
        outState.putStringArrayList("dateList", ArrayList(dateList))
        outState.putStringArrayList("notesList", ArrayList(notesList))
    }

    // tutaj odtwarzamy widok po obrocie ekranu
    @SuppressLint("NotifyDataSetChanged")
    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        val size = savedInstanceState.getInt("arrayListSize", 0)
        val titleList = savedInstanceState.getStringArrayList("titleList")
        val dateList = savedInstanceState.getStringArrayList("dateList")
        val notesList = savedInstanceState.getStringArrayList("notesList")
        if (titleList != null) {
            Log.i("SIZES KURWA", "Title " + titleList.size.toString())
        }
        if (dateList != null) {
            Log.i("SIZES KURWA", "Date " + dateList.size.toString())
        }
        if (notesList != null) {
            Log.i("SIZES KURWA", "Notes " + notesList.size.toString())
        }
        Log.i("SIZES KURWA", "Size $size")
        if (titleList != null && dateList != null && notesList != null){
            for (i in 0 until size) {
                val event = Event(titleList[i], dateList[i], notesList[i])
                eventList.add(event)
            }
//            recyclerView.adapter?.notifyDataSetChanged()
            Log.i("SIZES KURWA", "EventListSize " + eventList.size.toString())
////            recyclerView.layoutManager = LinearLayoutManager(this)
////            recyclerView.adapter = CustomAdapter(eventList)
//            Log.i("SIZES KURWA", "recyclerAdapterSize: " + recyclerView.size.toString())
        }
    }

    private fun define() {
        calendar = findViewById(R.id.calendarView)
        addButton = findViewById(R.id.addButton)
        recyclerView = findViewById(R.id.recyclerView)
        recyclerView.layoutManager = LinearLayoutManager(this)
        calendar.setOnDateChangeListener { view, year, month, dayOfMonth ->
            date = "$year-${month+1}-$dayOfMonth" // Utwórz format daty, np. "2023-04-16"
            Log.i("GOWNO", date)
        }
        recyclerView.adapter = CustomAdapter(eventList)
    }

    fun addNewEvent(view: View) {
        val myIntent = Intent(this, AddEventActivity::class.java)
        myIntent.putExtra("date", date)
        resultLauncher.launch(myIntent)
    }

    @SuppressLint("NotifyDataSetChanged")
    private var resultLauncher = registerForActivityResult(ActivityResultContracts.StartActivityForResult()) {
            result -> val data = result.data
        if (data?.getStringExtra("button_type") == "accept") {
            val notes: String = data?.getStringExtra("event_notes")!!
            val title: String = data.getStringExtra("event_title")!!
            val event = Event(title, date, notes)
            Log.i("EVENT_Title", event.getTitle())
            Log.i("EVENT_NOTES", event.getNotes())
            eventList.add(event)
        }
        recyclerView.adapter?.notifyDataSetChanged()
    }

    @SuppressLint("NotifyDataSetChanged")
    var resultLauncherFromEdit = registerForActivityResult(ActivityResultContracts.StartActivityForResult()) {
            result -> val data = result.data
        if (data?.getStringExtra("button_type") == "delete") {
            val pos = data.getIntExtra("position", 0)
            eventList.removeAt(pos)
            recyclerView.adapter?.notifyDataSetChanged()
            Toast.makeText(this, "Event deleted", Toast.LENGTH_SHORT).show()
        }
    }
}