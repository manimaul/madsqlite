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
public class MadDatabaseRTreeTest {

    private static final double PRECISION_MAX_DELTA = .00002;
    private MadDatabase _database;

    @Before
    public void setup() {
        _database = new MadDatabase();
    }

    @After
    public void tearDown() {
        _database.close();
    }

    //todo: add tests for Custom R-Tree Queries
    //(sqlite3_rtree_query_callback and sqlite3_rtree_geometry_callback)

    @Test
    public void rtree() throws Exception {
        givenAnRtreeDatabase();
        givenValuesInserted();
        final ContentValues cv = givenContentValuesInserted();

        {
            MadQuery query = _database.query("SELECT * FROM demo_index WHERE id=2;");
            assertTrue(query.moveToFirst());
            assertEquals(query.getLong(0), 2);
            assertEquals(cv.getAsDouble("minX"), query.getReal(1), PRECISION_MAX_DELTA);
            assertEquals(cv.getAsDouble("maxX"), query.getReal(2), PRECISION_MAX_DELTA);
            assertEquals(cv.getAsDouble("minY"), query.getReal(3), PRECISION_MAX_DELTA);
            assertEquals(cv.getAsDouble("maxY"), query.getReal(4), PRECISION_MAX_DELTA);
            assertTrue(query.moveToNext());
            assertTrue(query.isAfterLast());
            assertFalse(query.moveToNext());
            query.close();
        }

        {
            MadQuery query = _database.query("SELECT * FROM demo_index WHERE id=1;");
            assertTrue(query.moveToFirst());
            assertEquals(query.getLong(0), 1);
            assertEquals(-80.7749582, query.getReal(1), PRECISION_MAX_DELTA);
            assertEquals(-80.7747392, query.getReal(2), PRECISION_MAX_DELTA);
            assertEquals(35.3776136, query.getReal(3), PRECISION_MAX_DELTA);
            assertEquals(35.3778356, query.getReal(4), PRECISION_MAX_DELTA);
            assertTrue(query.moveToNext());
            assertTrue(query.isAfterLast());
            assertFalse(query.moveToNext());
            query.close();
        }

    }

    @Test
    public void rtree_between() throws Exception {
        givenAnRtreeDatabase();
        givenValuesInserted();
        givenContentValuesInserted();

        String sql = "SELECT id FROM demo_index WHERE minX>=-81.08 AND maxX<=-80.58 AND minY>=35.00 AND maxY<=35.44;";
        MadQuery query = _database.query(sql);
        assertFalse(query.isAfterLast());
        assertTrue(query.moveToFirst());
        assertFalse(query.isAfterLast());
        assertEquals(1, query.getLong(0));

        assertTrue(query.moveToNext());
        assertTrue(query.isAfterLast());
        assertFalse(query.moveToNext());
        query.close();
    }

    private void givenAnRtreeDatabase() {
        // https://www.sqlite.org/rtree.html
        _database.exec("CREATE VIRTUAL TABLE demo_index USING rtree(" +
                "   id   INTEGER," +
                "   minX REAL," +
                "   maxX REAL," +
                "   minY REAL," +
                "   maxY REAL" +
                ");");
        assertNull(_database.getError());
    }

    private void givenValuesInserted() {
        _database.exec("INSERT INTO demo_index VALUES(1,-80.7749582,-80.7747392,35.3776136,35.3778356);");
        assertNull(_database.getError());
    }

    private ContentValues givenContentValuesInserted() {
        ContentValues cv = new ContentValues();
        cv.put("id", 2);
        // NC 12th Congressional District in 2010
        cv.put("minX", -81.0);
        cv.put("maxX", -79.6);
        cv.put("minY", 35.0);
        cv.put("maxY", 36.2);
        assertTrue(_database.insert("demo_index", cv));
        return cv;
    }

}