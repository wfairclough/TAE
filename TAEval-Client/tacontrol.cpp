#include "tacontrol.h"
#include "connectionclient.h"
#include <QList>

TaControl::TaControl(QObject *parent) :
    QObject(parent)
{
}

/**
 * Description: Send request for list of TAs
 * Paramters: a string the represents the view that wants the information
 * Returns: None
 */
void TaControl::getTas() {
    ConnectionClient::getInstance().sendTaListMessage();
}

/**
 * Description: Send request for list of Tasks that a TA has
 * Paramters: a string the represents the view that wants the information, the TA whose Tasks you want to see
 * Returns: None
 */
void TaControl::getTaskListForTa(QString uname) {
    ConnectionClient::getInstance().sendTaskForTa(uname);
}

/**
 * Description: Send request for an Evalution for a Task
 * Paramters: a string the represents the view that wants the information, the id of the Task that owns the Evaluation
 * Returns: None
 */
void TaControl::getEvaluationListForTasks(QList<quint32> taskIds) {
    ConnectionClient::getInstance().sendEvaluationListForTasks(taskIds);
}

/**
  * Description: Send request to delete a Task from a TA
  * Parameters: a string the represents the view that wants the information, the TA whose Task you want to delete
  * Returns: None
  */
void TaControl::deleteTask(Task *task) {
    ConnectionClient::getInstance().sendDeleteTask(task);
}

/**
  * Description: Send request to add a Task from a TA
  * Parameters: a string the represents the view that wants the information, the TA whose Task you want to add and Task info
  * Returns: None
  */
void TaControl::addTaskForTa(QString uname, QString taskName, QString taskDescription, QString courseName, Semester::semester_t sem, int courseYear) {
    ConnectionClient::getInstance().sendAddTaskForTa(taskName, taskDescription, uname, courseName, sem, courseYear);
}

/**
  * Description: Send request to update a Task and Evaluation for a TA
  * Parameters: view that requested info, TA username, task to update, evaluation to update
  * Returns: None
  */
void TaControl::updateTaskAndEvaluation(Task *task, QString iName, QString taName) {
    ConnectionClient::getInstance().sendUpdateTaskAndEvaluation(task, iName, taName);
}

/**
  * Description: Send request to get all the courses a TA has done
  * Parameters: TeachingAssistant that you want the courses for.
  * Returns: None
  */
void TaControl::getCoursesForTeachingAssistant(TeachingAssistant* ta) {
    ConnectionClient::getInstance().sendCourseForTeachingAssistantMessage(ta);
}

/**
  * Description: Send request to get all Tasks for a TA and a specific course
  * Parameters: TeachingAssistant and Course that you want the tasks for.
  * Returns: None
  */
void TaControl::getTaskListForTaAndCourse(TeachingAssistant* ta, Course* course) {
    ConnectionClient::getInstance().sendTaskForTaAndCourse(ta, course);
}
