package io.madrona.madsqlite;

import android.content.ContentValues;
import android.support.test.runner.AndroidJUnit4;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static junit.framework.Assert.assertNull;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class DatabaseTest {

    private Database _database;

    @Before
    public void setup() {
        _database = new Database();
    }

    @After
    public void tearDown() {
        _database.close();
    }

    @Test
    public void insert_integer() throws Exception {
        _database.exec("CREATE TABLE test(keyInt INTEGER);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyInt", Integer.MIN_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyInt", Integer.MAX_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT keyInt FROM test;");
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());
        assertFalse(cursor.isAfterLast());
        final long firstResult = cursor.getLong(0);
        assertTrue(cursor.moveToNext());
        assertFalse(cursor.isAfterLast());
        final long secondResult = cursor.getLong(0);
        assertTrue(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());
        cursor.close();

        assertEquals(Integer.MIN_VALUE, firstResult);
        assertEquals(Integer.MAX_VALUE, secondResult);
    }

    @Test
    public void insert_long() throws Exception {
        _database.exec("CREATE TABLE test(keyInt INTEGER);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyInt", Long.MIN_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyInt", Long.MAX_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT keyInt FROM test;");
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());
        final long firstResult = cursor.getLong(0);
        assertTrue(cursor.moveToNext());
        assertFalse(cursor.isAfterLast());
        final long secondResult = cursor.getLong(0);
        assertTrue(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());
        cursor.close();

        assertEquals(Long.MIN_VALUE, firstResult);
        assertEquals(Long.MAX_VALUE, secondResult);
    }

    @Test
    public void insert_float() throws Exception {
        _database.exec("CREATE TABLE test(keyReal REAL);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyReal", Float.MIN_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyReal", Float.MAX_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyReal", 47.38723987F);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT keyReal FROM test;");
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());

        assertFalse(cursor.isAfterLast());
        final double firstResult = cursor.getReal(0);
        assertTrue(cursor.moveToNext());
        assertFalse(cursor.isAfterLast());

        assertFalse(cursor.isAfterLast());
        final double secondResult = cursor.getReal(0);
        assertTrue(cursor.moveToNext());
        assertFalse(cursor.isAfterLast());

        assertFalse(cursor.isAfterLast());
        final double thirdResult = cursor.getReal(0);
        assertTrue(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());

        cursor.close();
        assertEquals(Float.MIN_VALUE, firstResult, 0);
        assertEquals(Float.MAX_VALUE, secondResult, 0);
        assertEquals(47.38723987F, thirdResult, 0);
    }

    @Test
    public void insert_double() throws Exception {
        _database.exec("CREATE TABLE test(keyReal REAL);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyReal", Double.MIN_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyReal", Double.MAX_VALUE);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT keyReal FROM test;");
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());
        assertFalse(cursor.isAfterLast());
        final double firstResult = cursor.getReal(0);
        assertTrue(cursor.moveToNext());
        assertFalse(cursor.isAfterLast());
        final double secondResult = cursor.getReal(0);
        assertTrue(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());
        cursor.close();

        assertEquals(Double.MIN_VALUE, firstResult, 0);
        assertEquals(Double.MAX_VALUE, secondResult, 0);
    }

    @Test
    public void insert_blob() throws Exception {
        _database.exec("CREATE TABLE test(keyBlob BLOB);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyBlob", "data".getBytes());
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT keyBlob FROM test;");
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());
        assertFalse(cursor.isAfterLast());
        final byte[] data = cursor.getBlob(0);
        final String dataStr = cursor.getString(0);
        assertTrue(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());
        cursor.close();

        assertEquals("data", new String(data));
        assertEquals("data", dataStr);
    }

    @Test
    public void insert_text() throws Exception {
        _database.exec("CREATE TABLE test(keyText TEXT);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyText", "data");
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT keyText FROM test;");
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());
        assertFalse(cursor.isAfterLast());
        final String data = cursor.getString(0);
        assertTrue(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());
        cursor.close();

        assertEquals("data", data);
    }

    @Test
    public void query_args() throws Exception {
        _database.exec("CREATE TABLE test(keyInt INTEGER, keyText TEXT);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyText", "the quick brown fox");
        cv.put("keyInt", 99);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyText", "the slow white tortoise");
        cv.put("keyInt", 34);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        long number;
        String value;
        {
            final Cursor cursor = _database.query("SELECT keyText,keyInt FROM test WHERE keyInt is ?;", 99);
            assertNull(_database.getError());
            assertTrue(cursor.moveToFirst());
            assertFalse(cursor.isAfterLast());
            value = cursor.getString(0);
            number = cursor.getLong(1);
            assertTrue(cursor.moveToNext());
            assertTrue(cursor.isAfterLast());
            cursor.close();
        }
        assertEquals(99, number);
        assertEquals("the quick brown fox", value);

        {
            final Cursor cursor = _database.query("SELECT keyInt,keyText FROM test WHERE keyInt is ?;", 34);
            assertNull(_database.getError());
            assertTrue(cursor.moveToFirst());
            assertFalse(cursor.isAfterLast());
            number = cursor.getLong(0);
            value = cursor.getString(1);
            assertTrue(cursor.moveToNext());
            assertTrue(cursor.isAfterLast());
            cursor.close();
        }
        assertEquals(34, number);
        assertEquals("the slow white tortoise", value);
    }

    @Test
    public void query_args_str() throws Exception {
        _database.exec("CREATE TABLE test(keyInt INTEGER, keyText TEXT);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("keyText", "the quick brown fox");
        cv.put("keyInt", 99);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyText", "the slow white tortoise");
        cv.put("keyInt", 34);
        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT keyText,keyInt FROM test WHERE keyInt is ?;", "99");
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());
        assertFalse(cursor.isAfterLast());
        String value = cursor.getString(0);
        long number = cursor.getLong(1);
        assertTrue(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());
        cursor.close();
        assertEquals(99, number);
        assertEquals("the quick brown fox", value);
    }

    @Test
    public void test_multi_index_cursor() throws Exception {
        _database.exec("CREATE TABLE test(" +
                "keyInt INTEGER, " +
                "keyReal REAL," +
                "keyText TEXT);");

        ContentValues cv = new ContentValues();
        cv.put("keyText", "the quick brown fox");
        cv.put("keyInt", 99);
        cv.put("keyReal", Math.PI);

        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        cv.clear();
        cv.put("keyText", "the slow red tortoise");
        cv.put("keyInt", 42);
        cv.put("keyReal", Math.E);

        assertTrue(_database.insert("test", cv));
        assertNull(_database.getError());

        final Cursor cursor = _database.query("SELECT * FROM test;");
        assertNull(_database.getError());

        assertTrue(cursor.moveToFirst());
        assertEquals(Math.PI, cursor.getReal(1), 0);
        assertEquals("the quick brown fox", cursor.getString(2));
        assertEquals(99, cursor.getLong(0));
        assertFalse(cursor.isAfterLast());

        assertTrue(cursor.moveToNext());
        assertFalse(cursor.isAfterLast());
        assertEquals(Math.E, cursor.getReal(1), 0);
        assertEquals("the slow red tortoise", cursor.getString(2));
        assertEquals(42, cursor.getLong(0));
        assertFalse(cursor.isAfterLast());

        assertTrue(cursor.moveToNext());
        assertFalse(cursor.moveToNext());
        assertTrue(cursor.isAfterLast());

        cursor.close();
    }

}