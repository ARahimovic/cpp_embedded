# Custom Logger

Lets implement a custom logger library for our application , the logger should : 
- Support multiple log levels (DEBUG, INFO, WARN, ERROR)
- Allow configurable log level threshold to filter messages
- Include timeStamps (date and time) in each log entry
- Ensure thread safety for concurent logging
- Provide customisable log mesage formatting
- Optionally include contextual information (source file, line number, function name)
- can log to different output simultanously 
- be easy to extend and integrate into various application

## Respecting SOLID principles :
- in this custom logger we will try as much as possible to respect the SOLID principles.

- Single respnosabiltiy : a class should do only one thing
- Open/Closed principle : software should be open for extensions but closed for modifications
- Liskov Subtitute principle :
- Interface Segeration principle 
- Dependency Injection principle :


in order to respect the SOLID principels, we will try to refactor the code
the custom logger should only be responsible for logging 
the formatting of the message and the output of the message shoud be done by seperate classes that implement seperate intefaces


