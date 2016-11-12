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
        _database.exec("CREATE TABLE test(" +
                "keyInt INTEGER, " +
                "keyReal REAL," +
                "keyText TEXT, " +
                "keyBlob BLOB);");
    }

    @After
    public void tearDown() {
        _database.close();
    }

    @Test
    public void insert_integer() throws Exception {
        ContentValues cv = new ContentValues();
        cv.put("keyInt", Integer.MIN_VALUE);
        _database.insert("test", cv);

        cv.clear();
        cv.put("keyInt", Integer.MAX_VALUE);
        _database.insert("test", cv);

        final Cursor cursor = _database.query("SELECT keyInt FROM test;");
        assertTrue(cursor.moveToFirst());
        final long firstResult = cursor.getInt(0);
        assertTrue(cursor.moveToNext());
        final long secondResult = cursor.getInt(0);
        cursor.close();

        assertEquals(Integer.MIN_VALUE, firstResult);
        assertEquals(Integer.MAX_VALUE, secondResult);
    }

    @Test
    public void insert_long() throws Exception {
        ContentValues cv = new ContentValues();
        cv.put("keyInt", Long.MIN_VALUE);
        _database.insert("test", cv);

        cv.clear();
        cv.put("keyInt", Long.MAX_VALUE);
        _database.insert("test", cv);

        final Cursor cursor = _database.query("SELECT keyInt FROM test;");
        assertTrue(cursor.moveToFirst());
        final long firstResult = cursor.getInt(0);
        assertTrue(cursor.moveToNext());
        final long secondResult = cursor.getInt(0);
        cursor.close();

        assertEquals(Long.MIN_VALUE, firstResult);
        assertEquals(Long.MAX_VALUE, secondResult);
    }

    @Test
    public void insert_float() throws Exception {
        ContentValues cv = new ContentValues();
        cv.put("keyReal", Float.MIN_VALUE);
        _database.insert("test", cv);

        cv.clear();
        cv.put("keyReal", Float.MAX_VALUE);
        _database.insert("test", cv);

        final Cursor cursor = _database.query("SELECT keyReal FROM test;");
        assertTrue(cursor.moveToFirst());
        final double firstResult = cursor.getReal(0);
        assertTrue(cursor.moveToNext());
        final double secondResult = cursor.getReal(0);
        cursor.close();

        assertEquals(Float.MIN_VALUE, firstResult, 0);
        assertEquals(Float.MAX_VALUE, secondResult, 0);
    }

    @Test
    public void insert_double() throws Exception {
        ContentValues cv = new ContentValues();
        cv.put("keyReal", Double.MIN_VALUE);
        _database.insert("test", cv);

        cv.clear();
        cv.put("keyReal", Double.MAX_VALUE);
        _database.insert("test", cv);

        final Cursor cursor = _database.query("SELECT keyReal FROM test;");
        assertTrue(cursor.moveToFirst());
        final double firstResult = cursor.getReal(0);
        assertTrue(cursor.moveToNext());
        final double secondResult = cursor.getReal(0);
        cursor.close();

        assertEquals(Double.MIN_VALUE, firstResult, 0);
        assertEquals(Double.MAX_VALUE, secondResult, 0);
    }

}