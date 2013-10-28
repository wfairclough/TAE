--SQLite TAEval Database


--CREATE DATABASE TABLES
--=======================

CREATE TABLE IF NOT EXISTS Administrator (
  id INTEGER PRIMARY KEY NOT NULL,
  FOREIGN KEY(id) REFERENCES User(id)
);


CREATE TABLE IF NOT EXISTS Course (
  id INTEGER PRIMARY KEY NOT NULL,
  name varchar(8) NOT NULL,
  semester int NOT NULL,
  year int NOT NULL,
  instructorid INTEGER NOT NULL,
  FOREIGN KEY(instructorId) REFERENCES Instructor(id)
);


-- Join Table for many-to-many relationship between TAs and Courses
CREATE TABLE IF NOT EXISTS TA_Courses (
  courseid INTEGER NOT NULL,
  taid INTEGER NOT NULL,
  PRIMARY KEY (courseId, taId),
  FOREIGN KEY(courseId) REFERENCES Course(id),
  FOREIGN KEY(taId) REFERENCES TA(id)
);


CREATE TABLE IF NOT EXISTS Evaluation (
  id INTEGER PRIMARY KEY NOT NULL,
  taskid INTEGER NOT NULL,
  rating int NOT NULL,
  comment varchar(255),
  FOREIGN KEY(taskId) REFERENCES Task(id)
);


CREATE TABLE IF NOT EXISTS Instructor (
  id INTEGER PRIMARY KEY NOT NULL,
  FOREIGN KEY(id) REFERENCES User(id)
);


CREATE TABLE IF NOT EXISTS Task (
  id INTEGER PRIMARY KEY NOT NULL,
  name varchar(45) NOT NULL,
  description varchar(45) NOT NULL,
  taid INTEGER NOT NULL,
  courseid INTEGER NOT NULL,
  FOREIGN KEY(taId) REFERENCES TA(id),
  FOREIGN KEY(courseId) REFERENCES Course(id)
);


CREATE TABLE IF NOT EXISTS TA (
  id INTEGER PRIMARY KEY NOT NULL,
  FOREIGN KEY(id) REFERENCES User(id)
);


-- Abstract User table for TA, Instructor, and Administrator
CREATE TABLE IF NOT EXISTS User (
  id INTEGER PRIMARY KEY NOT NULL,
  firstName varchar(100) NOT NULL,
  lastName varchar(100) NOT NULL,
  username varchar(100) NOT NULL,
  type int NOT NULL
);



--INSERT TEST DATA
--=======================

begin transaction;


--Insert default admin user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "super", "admin", "admin", 1 );
INSERT OR REPLACE INTO ADMINISTRATOR (id) SELECT id from USER where username="admin";


--Insert a test instructor user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Dr. Christine", "Laurendeau", "claurendeau", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="claurendeau";


--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Stephanie", "Hurtado", "shurtado", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="shurtado";


--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Joshua", "Beltramin", "jbeltramin", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="jbeltramin";


--Insert a test Course
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "COMP3004", 1, 2013, (SELECT id from USER where username='claurendeau') );


-- Add a TA to a Couse
INSERT OR REPLACE INTO TA_COURSES (courseId, taId) VALUES ((SELECT id from USER where username='shurtado'), (SELECT id from COURSE where name="COMP3004" and semester=1 and year=2013));


-- Add a Task to a TA
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Mark Analysis", "Mark Phase 1 Deliverable for section A", (SELECT id from USER where username='shurtado'), (SELECT id from COURSE where name="COMP3004" and semester=1 and year=2013) );


end transaction;











