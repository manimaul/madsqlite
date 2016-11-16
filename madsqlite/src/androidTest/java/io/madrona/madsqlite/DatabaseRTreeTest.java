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
public class DatabaseRTreeTest {

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
    public void rtree() throws Exception {
        // https://www.sqlite.org/rtree.html
        _database.exec("CREATE VIRTUAL TABLE demo_index USING rtree(" +
                "   id   INTEGER," +
                "   minX REAL," +
                "   maxX REAL," +
                "   minY REAL," +
                "   maxY REAL" +
                ");");
        assertNull(_database.getError());

        _database.exec("INSERT INTO demo_index VALUES(1,-80.7749,-80.7747,35.3776,35.3778);");
        assertNull(_database.getError());

        ContentValues cv = new ContentValues();
        cv.put("id", 2);
        // NC 12th Congressional District in 2010
        cv.put("minX", "-81.0");
        cv.put("maxX", "-79.6");
        cv.put("minY", "35.0");
        cv.put("maxY", "36.2");
        assertTrue(_database.insert("demo_index", cv));

        {
            Cursor cursor = _database.query("SELECT * FROM demo_index WHERE id=2;");
            assertTrue(cursor.moveToFirst());
            assertEquals(cursor.getLong(0), 2);
            assertEquals(cv.getAsDouble("minX"), cursor.getReal(1), 0);
            assertEquals(cv.getAsDouble("maxX"), cursor.getReal(2), 0);
            assertEquals(cv.getAsDouble("minY"), cursor.getReal(3), 0);
            assertEquals(cv.getAsDouble("maxY"), cursor.getReal(4), 0);
            assertTrue(cursor.moveToNext());
            assertTrue(cursor.isAfterLast());
            assertFalse(cursor.moveToNext());
            cursor.close();
        }

    }

}