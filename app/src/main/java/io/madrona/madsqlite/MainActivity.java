package io.madrona.madsqlite;

import android.content.ContentValues;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import io.madrona.madsqlite.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main);

        Database memDb = new Database();
        memDb.exec("CREATE TABLE test(x INTEGER, " +
                "y TEXT, " +
                "z BLOB);");

        ContentValues cv = new ContentValues();
        cv.put("x", 1970);
        cv.put("y", 7070);
        cv.put("z", "i'm a blob");
        memDb.insert("test", cv);

        cv.clear();
        cv.put("x", 456);
        cv.put("y", "123");
        cv.put("z", "entry blob 2");
        memDb.insert("test", cv);

        Cursor cursor = memDb.query("SELECT * FROM test;");
        cursor.moveToFirst();
        while (!cursor.isAfterLast()) {
            Log.d(TAG, "x: " + cursor.getLong(0));
            Log.d(TAG, "y: " + cursor.getString(1));
            cursor.moveToNext();
        }

        cursor.close();
        memDb.close();

        binding.sampleText.setText("opened database");
    }

}
