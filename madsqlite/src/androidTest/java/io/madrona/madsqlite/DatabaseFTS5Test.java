package io.madrona.madsqlite;

import android.support.test.runner.AndroidJUnit4;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.ArrayList;
import java.util.List;

import static junit.framework.Assert.assertNull;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class DatabaseFTS5Test {

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
    public void match_near() throws Exception {
        /*
        https://sqlite.org/fts5.html

        CREATE VIRTUAL TABLE f USING fts5(x);
        INSERT INTO f(rowid, x) VALUES(1, 'A B C D x x x E F x');

        ... MATCH 'NEAR(e d, 4)';                      -- Matches!
        ... MATCH 'NEAR(e d, 3)';                      -- Matches!
        ... MATCH 'NEAR(e d, 2)';                      -- Does not match!

        ... MATCH 'NEAR("c d" "e f", 3)';              -- Matches!
        ... MATCH 'NEAR("c"   "e f", 3)';              -- Does not match!

        ... MATCH 'NEAR(a d e, 6)';                    -- Matches!
        ... MATCH 'NEAR(a d e, 5)';                    -- Does not match!

        ... MATCH 'NEAR("a b c d" "b c" "e f", 4)';    -- Matches!
        ... MATCH 'NEAR("a b c d" "b c" "e f", 3)';    -- Does not match!
         */
        _database.exec("CREATE VIRTUAL TABLE f USING fts5(x);");
        assertNull(_database.getError());
        _database.exec("INSERT INTO f(rowid, x) VALUES(1, 'A B C D x x x E F x');");
        assertNull(_database.getError());

        assertMatches("SELECT * FROM f WHERE f MATCH 'NEAR(e d, 4)';");
        assertMatches("SELECT * FROM f WHERE f MATCH 'NEAR(e d, 3)';");
        assertDoesNotMatche("SELECT * FROM f WHERE f MATCH 'NEAR(e d, 2)';");

        assertMatches("SELECT * FROM f WHERE f MATCH 'NEAR(\"c d\" \"e f\", 3)';");
        assertDoesNotMatche("SELECT * FROM f WHERE f MATCH 'NEAR(\"c\" \"e f\", 3)';");

        assertMatches("SELECT * FROM f WHERE f MATCH 'NEAR(a d e, 6)';");
        assertDoesNotMatche("SELECT * FROM f WHERE f MATCH 'NEAR(a d e, 5)';");

        assertMatches("SELECT * FROM f WHERE f MATCH 'NEAR(\"a b c d\" \"b c\" \"e f\", 4)';");
        assertDoesNotMatche("SELECT * FROM f WHERE f MATCH 'NEAR(\"a b c d\" \"b c\" \"e f\", 3)';");
    }

    private void assertMatches(String query) {
        assertFalse(queryMatches(query).isEmpty());
    }

    private void assertDoesNotMatche(String query) {
        assertTrue(queryMatches(query).isEmpty());
    }

    private List<String> queryMatches(String query) {
        List<String> matches = new ArrayList<>();
        Cursor cursor = _database.query(query);
        assertNull(_database.getError());
        assertTrue(cursor.moveToFirst());
        while (!cursor.isAfterLast()) {
            String value = cursor.getString(0);
            if (!value.isEmpty()) {
                matches.add(value);
            }
            cursor.moveToNext();
        }
        cursor.close();
        return matches;
    }

}