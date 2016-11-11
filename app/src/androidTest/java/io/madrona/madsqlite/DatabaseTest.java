package io.madrona.madsqlite;

import android.content.ContentValues;
import android.support.test.runner.AndroidJUnit4;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

@RunWith(AndroidJUnit4.class)
public class DatabaseTest {

    private Database _database;

    @Before
    public void setup() {
        _database = new Database();
        _database.exec("CREATE TABLE test(x INTEGER, " +
                "y TEXT, " +
                "z BLOB);");
    }

    @After
    public void tearDown() {
        _database.close();
    }

    @Test
    public void insert_int() throws Exception {
        ContentValues cv = new ContentValues();
        cv.put("x", Long.MIN_VALUE);
        _database.insert("test", cv);

        cv.clear();
        cv.put("x", Long.MAX_VALUE);
        _database.insert("test", cv);

        final Cursor cursor = _database.query("SELECT x FROM test;");
        assertEquals(2, cursor.getCount());
        assertTrue(cursor.moveToFirst());
        assertEquals(Long.MIN_VALUE, cursor.getInt(0));
        assertTrue(cursor.moveToNext());
        assertEquals(Long.MAX_VALUE, cursor.getInt(0));
        cursor.close();
    }

    @Test
    public void insert_blob() throws Exception {
        ContentValues cv = new ContentValues();
        cv.put("z", "blob".getBytes());
        _database.insert("test", cv);

        final Cursor cursor = _database.query("SELECT * FROM test;");
        assertEquals(1, cursor.getCount());
        assertTrue(cursor.moveToFirst());
        assertEquals("blob", new String(cursor.getBlob(0)));
        cursor.close();
    }

}