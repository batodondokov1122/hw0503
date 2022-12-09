package com.example.nameslist

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ArrayAdapter
import android.widget.EditText
import android.widget.ListView
import kotlin.random.Random

class MainActivity : AppCompatActivity() {
    val fullNamesMutable: MutableList<String> = arrayListOf()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val lvPeople = findViewById<ListView>(R.id.people)
        val names = resources.getStringArray(R.array.names)
        val lastnames = resources.getStringArray(R.array.lastNames)
        for (i in 1..15){
            fullNamesMutable.add("${names[Random.nextInt(names.size)]} ${lastnames[Random.nextInt(lastnames.size)]}")
        }
        // TODO: сгенерировать список персон из случайных сочетаний имён и фамилий
        // TODO: создайте два string-array в ресурсах и получите список их случайных комбинаций
        val adapter = ArrayAdapter<String>(this, R.layout.item, fullNamesMutable)
        lvPeople.adapter = adapter // задаём адаптер (посредник) для отображения данных на списке

        // пример чтения строк из ресурсов
//        val names = resources.getStringArray(R.array.names) // функция возвращает массив
    }

    fun onAddPersonClick(view: View) {
        val newFullName = findViewById<EditText>(R.id.newFullName)
        val newFullNameString = newFullName.text.toString()
        fullNamesMutable.add(newFullNameString)

        // TODO: реализовать добавление новых персон в список
        // имя считывать из текстового поля
        // если нужно изменять число элементов, используйте MutableList<String>
    }
}