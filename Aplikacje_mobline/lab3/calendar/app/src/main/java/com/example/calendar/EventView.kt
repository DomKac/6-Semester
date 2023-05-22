package com.example.calendar

import android.content.Context
import android.util.AttributeSet
import android.view.LayoutInflater
import android.widget.TextView
import androidx.constraintlayout.widget.ConstraintLayout

class EventView(context: Context, attrs: AttributeSet?) : ConstraintLayout(context, attrs) {

    private val titleView: TextView
    private val dateView: TextView

    init {
        LayoutInflater.from(context).inflate(R.layout.event_view, this, true)
        titleView = findViewById(R.id.event_title)
        dateView = findViewById(R.id.event_data)
    }

    fun setTitle(title: String) {
        titleView.text = title
    }

    fun setDate(date: String) {
        dateView.text = date
    }

}
