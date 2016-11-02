package io.madrona.madsqlite;

import android.content.ContentValues;
import android.databinding.DataBindingUtil;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

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
        cv.put("z", "i'm a blob");
        cv.put("y", 7070);
        cv.put("x", 1970);
        memDb.insert("test", cv);

        Cursor cursor = memDb.query("SELECT * FROM test;");
        while (!cursor.isAfterLast()) {
            Log.d(TAG, "data count " + cursor.getDataCount());
//            Log.d(TAG, "x: " + cursor.getInt(0));
//            Log.d(TAG, "y: " + cursor.getString(1));
//            Log.d(TAG, "z: " + new String(cursor.getBlob(2)));
            cursor.moveToNext();
        }

        cursor.close();
        memDb.close();

        binding.sampleText.setText("opened database");
    }

}
