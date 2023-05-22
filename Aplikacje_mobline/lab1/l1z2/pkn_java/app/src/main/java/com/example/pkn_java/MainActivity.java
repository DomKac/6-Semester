package com.example.pkn_java;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private int player_score = 0;
    private int comp_score = 0;

    private int comp_choice = -1;
    // 0 -> kamien
    // 1 -> papier
    // 2 -> nozyce

    TextView playerPoints;
    TextView compPoints;
    ImageView playerImage;
    ImageView compImage;

    Random random = new Random();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        playerPoints = findViewById(R.id.playerPoints);
        compPoints = findViewById(R.id.compPoints);

        playerImage = findViewById(R.id.playerImage);
        compImage = findViewById(R.id.compImage);

        player_score = 0;
        comp_score = 0;
        update_points();
    }

    @SuppressLint("SetTextI18n")
    private void update_points() {
        playerPoints.setText("" + player_score);
        compPoints.setText("" + comp_score);
    }

    // kamien -> 0
    public void play_kamien(View view) {
        comp_choice = random.nextInt(3);
        playerImage.setImageResource(R.drawable.kamien);
        if (comp_choice == 0) {
            compImage.setImageResource(R.drawable.kamien);
            Toast.makeText(this, "Remis", Toast.LENGTH_SHORT).show();
        }
        else if (comp_choice == 1) {
            comp_score++;
            compImage.setImageResource(R.drawable.papier);
            Toast.makeText(this, "Komputer wygrał :(", Toast.LENGTH_SHORT).show();
        }
        else {
            player_score++;
            compImage.setImageResource(R.drawable.nozyce);
            Toast.makeText(this, "Wygrałeś!!! :)", Toast.LENGTH_SHORT).show();
        }
        update_points();
    }

    // papier -> 1
    public void play_papier(View view) {
        comp_choice = random.nextInt(3);
        playerImage.setImageResource(R.drawable.papier);
        if (comp_choice == 1) {
            compImage.setImageResource(R.drawable.papier);
            Toast.makeText(this, "Remis", Toast.LENGTH_SHORT).show();
        }
        else if (comp_choice == 2) {
            comp_score++;
            compImage.setImageResource(R.drawable.nozyce);
            Toast.makeText(this, "Komputer wygrał :(", Toast.LENGTH_SHORT).show();
        }
        else {
            player_score++;
            compImage.setImageResource(R.drawable.kamien);
            Toast.makeText(this, "Wygrałeś!!! :)", Toast.LENGTH_SHORT).show();
        }
        update_points();
    }

    // nozyce -> 2
    public void play_nozyce(View view) {
        comp_choice = random.nextInt(3);
        playerImage.setImageResource(R.drawable.nozyce);
        if (comp_choice == 2) {
            compImage.setImageResource(R.drawable.nozyce);
            Toast.makeText(this, "Remis", Toast.LENGTH_SHORT).show();
        }
        else if (comp_choice == 0) {
            comp_score++;
            compImage.setImageResource(R.drawable.kamien);
            Toast.makeText(this, "Komputer wygrał :(", Toast.LENGTH_SHORT).show();
        }
        else {
            player_score++;
            compImage.setImageResource(R.drawable.papier);
            Toast.makeText(this, "Wygrałeś!!! :)", Toast.LENGTH_SHORT).show();
        }
        update_points();
    }

    public void resetButton(View view) {
        player_score = 0;
        comp_score = 0;
        update_points();
        compImage.setImageResource(R.mipmap.ic_launcher_round);
        playerImage.setImageResource(R.drawable.steve);
    }
}