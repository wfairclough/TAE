## Welcome to TAEval

TAEval is a system for managing TAs for courses and allowing the Instructor to assign TAs tasks and evaluate them on these task.

View full [System Description](http://people.scs.carleton.ca/~claurend/Courses/COMP3004/F13/Project/TAEval.pdf)


## Getting Started

1. Clone the Qt Projects from GitHub

        git clone git@github.com:wfairclough/TAEval.git

3. Generate a new ssh key for GitHub in the COMP3004 VM

  [Instructions on configuring ssh for GitHub](https://help.github.com/articles/generating-ssh-keys)

4. Open the Client, Server and Commons Qt Project in QtCreator

        $ ./TAEval-Client/TAEval-Client.pro
        $ ./TAEval-Server/TAEval-Server.pro
        $ ./TAEvalCommons/TAEvalCommons.pro

5. Be sure to build the TAEvalCommons library project first as it is a dependancy for the client and server projects.

6. Another thing to note is that the TAEvalCommosn build directory should point to ./TAEvalCommons not build-TAEvalCommons-*

## Project Managment

We will be using a Redmine server to do our Project Managment. You must register a new user on the server and then wait to be given access. 

The Redmine server is at [http://redmine.wfairclough.com/](http://redmine.wfairclough.com/)

This will then give us the ability to task all the tasks that we need to get done and whether we are on time or late for certain features. This will also be perfect for creating reports to put in our documentation.

Useful git commit message keywords:
To resolve an issue type any of the following keywords - fixes, fixed, closes, resolve, resolves or resolved followed # and then the issue number. (ex. fixes #5)

### Gantt

Gantt for major Epic milestone:

[![TAEval Gantt](http://res.cloudinary.com/dmtms9gh8/image/upload/v1378921635/al0vwlijjgtpfmjjgpzi.png)](http://redmine.wfairclough.com/projects/taeval)

## Contributing

Team Members
Ben Fairclough, Will Fairclough and Sean Malcolmson

A little tutorial on using Git that I found very helpful [Git Tutorial](http://try.github.io/levels/1/challenges/2).

## Code Status

* Building Successfully


