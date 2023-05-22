package com.example.zad1_java;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private int score = 0;
    private int r1 = 0;
    private int r2 = 0;

    Random random = new Random();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        score = 0;
        roll();
    }

    @SuppressLint("SetTextI18n")
    private void roll() {
        final TextView leftBut = (TextView) findViewById(R.id.leftButton);
        final TextView rightBut = (TextView) findViewById(R.id.rightButton);
        final TextView punkty = (TextView) findViewById(R.id.points);
        punkty.setText("Punkty: "+ score);
        r1 = random.nextInt(11);    // losowanie r1
        r2 = random.nextInt(11);    // losowanie r2
        leftBut.setText("" + r1);
        rightBut.setText("" + r2);
    }

    public void leftClick(View view) {
        if (r1>=r2){
            score++;
            Toast.makeText(this, "Dobrze :)", Toast.LENGTH_SHORT).show();
        }
        else {
            score--;
            Toast.makeText(this, "Źle :(", Toast.LENGTH_SHORT).show();
        }
        roll();
    }

    public void rightClick(View view) {
        if (r2>=r1){
            score++;
            Toast.makeText(this, "Dobrze :)", Toast.LENGTH_SHORT).show();
        }
        else {
            score--;
            Toast.makeText(this, "Źle :(", Toast.LENGTH_SHORT).show();
        }
        roll();
    }
}