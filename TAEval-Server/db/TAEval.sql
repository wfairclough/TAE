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
  courseId INTEGER NOT NULL,
  taId INTEGER NOT NULL,
  PRIMARY KEY (courseId, taId),
  FOREIGN KEY(courseId) REFERENCES Course(id),
  FOREIGN KEY(taId) REFERENCES TA(id)
);


CREATE TABLE IF NOT EXISTS Evaluation (
  taskid INTEGER PRIMARY KEY NOT NULL,
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
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Christine", "Laurendeau", "claurendeau", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="claurendeau";
--Insert a test instructor user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Louis", "Nel", "ldnel", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="ldnel";
--Insert a test instructor user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "David", "Maybury", "dmaybury", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="dmaybury";
--Insert a test instructor user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Dr", "Who", "drwho", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="drwho";
--Insert a test instructor user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Daniel", "Faraday", "dfaraday", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="dfaraday";
--Insert a test instructor user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Thanatos", " ", "thanatos", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="thanatos";
--Insert a test instructor user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Zoidberg", " ", "zoidberg", 2 );
INSERT OR REPLACE INTO INSTRUCTOR (id) SELECT id from USER where username="zoidberg";




--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Stephanie", "Hurtado", "shurtado", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="shurtado";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Joshua", "Beltramin", "jbeltramin", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="jbeltramin";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Han", "Solo", "hsolo", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="hsolo";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Emilie", "de Ravin", "ederavin", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="ederavin";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "John", "Snow", "jsnow", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="jsnow";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Ned", "Stark", "nstark", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="nstark";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Hodor", " ", "hodor", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="hodor";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Joffrey", "Baratheon", "jbaratheon", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="jbaratheon";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "50", "Cent", "50cent", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="50cent";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Number", "Six", "nsix", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="nsix";
--Insert a test TA user
INSERT OR REPLACE INTO USER (firstName, lastName, username, type) VALUES ( "Rose", "Tyler", "rtyler", 3 );
INSERT OR REPLACE INTO TA (id) SELECT id from USER where username="rtyler";


--Insert test Courses
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "COMP3004", 2, 2013, (SELECT id from USER where username='claurendeau') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "COMP3005", 2, 2013, (SELECT id from USER where username='ldnel') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "COMP2404", 1, 2013, (SELECT id from USER where username='ldnel') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "COMP3005", 0, 2013, (SELECT id from USER where username='ldnel') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "COMP2402", 0, 2012, (SELECT id from USER where username='ldnel') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "PHYS1901", 2, 2013, (SELECT id from USER where username='dmaybury') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "PHYS1901", 2, 2012, (SELECT id from USER where username='dmaybury') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "PHYS1002", 2, 2013, (SELECT id from USER where username='drwho') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "PHYS7105", 2, 2013, (SELECT id from USER where username='dfaraday') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "LIFE4000", 2, 2012, (SELECT id from USER where username='thanatos') );
INSERT OR REPLACE INTO COURSE (name, semester, year, instructorId) VALUES ( "FOOD1006", 1, 2012, (SELECT id from USER where username='zoidberg') );


-- Add a TA to a Couse
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='shurtado'), (SELECT id from COURSE where name="COMP3004" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='jbeltramin'), (SELECT id from COURSE where name="COMP3004" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='hsolo'), (SELECT id from COURSE where name="PHYS1901" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='ederavin'), (SELECT id from COURSE where name="COMP3005" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='hsolo'), (SELECT id from COURSE where name="COMP3005" and semester=0 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='nsix'), (SELECT id from COURSE where name="COMP3005" and semester=0 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='jsnow'), (SELECT id from COURSE where name="PHYS1002" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='jsnow'), (SELECT id from COURSE where name="FOOD1006" and semester=1 and year=2012));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='rtyler'), (SELECT id from COURSE where name="PHYS1002" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='50cent'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='hodor'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='nsix'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='nstark'), (SELECT id from COURSE where name="LIFE4000" and semester=2 and year=2012));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='nstark'), (SELECT id from COURSE where name="COMP2402" and semester=0 and year=2012));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='jbaratheon'), (SELECT id from COURSE where name="FOOD1006" and semester=1 and year=2012));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='rtyler'), (SELECT id from COURSE where name="COMP2404" and semester=1 and year=2013));
INSERT OR REPLACE INTO TA_COURSES (taId, courseId) VALUES ((SELECT id from USER where username='jbaratheon'), (SELECT id from COURSE where name="COMP2404" and semester=1 and year=2013));

-- Add a Task to a TA
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Mark Analysis", "Mark Phase 1 Deliverable for section A", (SELECT id from USER where username='shurtado'), (SELECT id from COURSE where name="COMP3004" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Mark Analysis", "Mark Phase 1 Deliverable for section A", (SELECT id from USER where username='jbeltramin'), (SELECT id from COURSE where name="COMP3004" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Create Assignment 1", "Make an Assignment", (SELECT id from USER where username='jbeltramin'), (SELECT id from COURSE where name="COMP3004" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Create A2", "Work Hard", (SELECT id from USER where username='jbeltramin'), (SELECT id from COURSE where name="COMP3004" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Field Trip", "Organize a Trip to the Observatory", (SELECT id from USER where username='hsolo'), (SELECT id from COURSE where name="PHYS1901" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Mark Projects", "Mark the Projects from your Section", (SELECT id from USER where username='ederavin'), (SELECT id from COURSE where name="COMP3005" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Build db", "Build new db for the millennium falcon", (SELECT id from USER where username='hsolo'), (SELECT id from COURSE where name="COMP3005" and semester=0 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "00101110","", (SELECT id from USER where username='nsix'), (SELECT id from COURSE where name="COMP3005" and semester=0 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "11001101","", (SELECT id from USER where username='nsix'), (SELECT id from COURSE where name="COMP3005" and semester=0 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Sword Practice", "Learn to be a better swordsman", (SELECT id from USER where username='jsnow'), (SELECT id from COURSE where name="PHYS1002" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Protect the Wall", "...protect the wall you bastard", (SELECT id from USER where username='jsnow'), (SELECT id from COURSE where name="PHYS1002" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Go beyond the wall", "the white walkers are coming", (SELECT id from USER where username='jsnow'), (SELECT id from COURSE where name="FOOD1006" and semester=1 and year=2012) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Get head reattached", "its probably still up on that pike", (SELECT id from USER where username='nstark'), (SELECT id from COURSE where name="LIFE4000" and semester=2 and year=2012) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Go South", "Go to kings landing and become hand of the king", (SELECT id from USER where username='nstark'), (SELECT id from COURSE where name="COMP2402" and semester=0 and year=2012) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "hodor", "hodor hodor ... hodor", (SELECT id from USER where username='hodor'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "hodor", "hodor hodor ... hodor", (SELECT id from USER where username='hodor'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Raise death count", "hurt as many people as you can", (SELECT id from USER where username='jbaratheon'), (SELECT id from COURSE where name="FOOD1006" and semester=1 and year=2012) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Whine", "Whine as much as humany possible", (SELECT id from USER where username='jbaratheon'), (SELECT id from COURSE where name="FOOD1006" and semester=1 and year=2012) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Get slapped", "Get slapped around by uncle Tyrion", (SELECT id from USER where username='jbaratheon'), (SELECT id from COURSE where name="COMP2404" and semester=1 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Get rich", "or die tryin'", (SELECT id from USER where username='50cent'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Try to stay emotionless", "Act like all other humanoid cylons", (SELECT id from USER where username='nsix'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Stay Calm", "Just ignor Gaius", (SELECT id from USER where username='nsix'), (SELECT id from COURSE where name="PHYS7105" and semester=2 and year=2013) );
INSERT OR REPLACE INTO TASK (name, description, taid, courseid) VALUES ( "Save Earth", "Stop the Daleks", (SELECT id from USER where username='rtyler'), (SELECT id from COURSE where name="PHYS1002" and semester=2 and year=2013) );







-- Add Evaluation to Task
INSERT OR REPLACE INTO EVALUATION (rating, comment, taskid) VALUES (5, "You are doing very well", 4);
INSERT OR REPLACE INTO EVALUATION (rating, comment, taskid) VALUES (3, "Nicely done", 2);
INSERT OR REPLACE INTO EVALUATION (rating, comment, taskid) VALUES (1, "Please try HARDER", 5);
INSERT OR REPLACE INTO EVALUATION (rating, comment, taskid) VALUES (1, "You tried", 9);
INSERT OR REPLACE INTO EVALUATION (rating, comment, taskid) VALUES (3, "Please try HARDER", 11);
INSERT OR REPLACE INTO EVALUATION (rating, comment, taskid) VALUES (5, "You got slapped very well, hope there is more to come!", 19);
INSERT OR REPLACE INTO EVALUATION (rating, comment, taskid) VALUES (2, "That didnt turn out too well for you", 14);


end transaction;












