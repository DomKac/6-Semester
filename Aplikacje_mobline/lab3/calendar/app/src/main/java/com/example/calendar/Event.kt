//import android.os.Parcel
//import android.os.Parcelable
//
//class Event(var title: String, var date: String, var notes: String) : Parcelable {
//
//    constructor(parcel: Parcel) : this(
//        parcel.readString()!!,
//        parcel.readString()!!,
//        parcel.readString()!!
//    )
//
//    override fun writeToParcel(parcel: Parcel, flags: Int) {
//        parcel.writeString(title)
//        parcel.writeString(date)
//        parcel.writeString(notes)
//    }
//
//    override fun describeContents(): Int {
//        return 0
//    }
//
//    companion object CREATOR : Parcelable.Creator<Event> {
//        override fun createFromParcel(parcel: Parcel): Event {
//            return Event(parcel)
//        }
//
//        override fun newArray(size: Int): Array<Event?> {
//            return arrayOfNulls(size)
//        }
//    }
//}


package com.example.calendar

class Event(title: String, date: String, notes: String) : java.io.Serializable{
    private var title: String
    private var date: String
    private var notes: String

    init {
        this.title = title
        this.date = date
        this.notes = notes
    }

    fun getTitle(): String {
        return title
    }
    fun getDate(): String {
        return date
    }
    fun getNotes(): String {
        return notes
    }

    fun setTitle(title: String) {
        this.title = title
    }
    fun setDate(date: String) {
        this.date = date
    }
    fun setNotes(notes: String) {
        this.notes = notes
    }

}