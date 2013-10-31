#include "testtamanager.h"
#include "course.h"
#include "dbcoordinator.h"

TestTaManager::TestTaManager(QObject *parent) :
    QObject(parent)
{
    DbCoordinator::getInstance().openDatabase("/Users/will/Development/Carleton/Comp3004/Project/TAEval/TAEval-Server/db/", "TAEval.db");
}


void TestTaManager::testFetchAllTas() {

}


void TestTaManager::testFetchAllTasksForTeachingAssistance() {

}


void TestTaManager::testFetchAllTasksForCourse() {

}


void TestTaManager::testDeleteTaskForTa() {

}


void TestTaManager::testAddTaskForCourse() {
    TaManager tm;

    Task* task = new Task();
    task->setName("Test Task");
    task->setDescription("This is a test task");

    Course* course = new Course;
    course->setName("COMP3004");
    course->setYear(2013);
    course->setSemesterType(Semester::FALL);

    tm.addTaskForCourse(task, course);

//    QVERIFY(1 == 1);

//    QVERIFY(1 == 2);

}


void TestTaManager::testFetchEvaluationForTask() {

    TaManager tm;

    Task* task = new Task();
    task->setName("Test Task");
    task->setDescription("This is a test task");

    tm.fetchEvaluationForTask(task);

}

void TestTaManager::testAddEvaluationToTask() {
    TaManager tm;

    Task* task = new Task();
    task->setName("Test Task");

    Evaluation* eval = new Evaluation;
    eval->setRating(RATING::GOOD);
    eval->setComment("This is the comment for the test task. I guess they did GOOD.");

    tm.addEvaluationToTask(eval, task);
}

