package com.example.calendar

import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.recyclerview.widget.RecyclerView

class CustomAdapter(private val data: MutableList<Event>) : RecyclerView.Adapter<CustomAdapter.ViewHolder>() {

    class ViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        var titleView : TextView = view.findViewById(R.id.event_title)
        var dataView : TextView = view.findViewById(R.id.event_data)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.event_view, parent,false)
        val viewHolder = ViewHolder(view)

        view.setOnClickListener {
            val position: Int = viewHolder.adapterPosition
            val clickedEvent = data[position]

            val editIntent = Intent(view.context, EditEventActivity::class.java)
            editIntent.putExtra("event", clickedEvent)
            editIntent.putExtra("position", position)
            (view.context as MainActivity).resultLauncherFromEdit.launch(editIntent)
        }

        return viewHolder
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.titleView.text = data[position].getTitle()
        holder.dataView.text = data[position].getDate()
    }

    override fun getItemCount(): Int {
        return data.size
    }


}
