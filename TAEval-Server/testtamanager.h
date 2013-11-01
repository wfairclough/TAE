#ifndef TESTTAMANAGER_H
#define TESTTAMANAGER_H

#include <QObject>
//#include <QtTest/QtTest>
#include <tamanager.h>

//QTEST_MAIN(TestTaManager)
//#include "testtamanager.moc"

class TestTaManager : public QObject
{
    Q_OBJECT
public:
    explicit TestTaManager(QObject *parent = 0);

//private slots:
    void testFetchAllTas();
    void testFetchAllTasksForTeachingAssistance();
    void testFetchAllTasksForCourse();
    void testDeleteTaskForTa();
    void testAddTaskForCourse();
    void testFetchEvaluationForTask();
    void testAddEvaluationToTask();
};

#endif // TESTTAMANAGER_H
