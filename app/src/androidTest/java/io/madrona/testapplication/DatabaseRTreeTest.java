package io.madrona.testapplication;

import android.support.test.runner.AndroidJUnit4;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import io.madrona.madsqlite.Database;

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
    public void match_near() throws Exception {

    }

}