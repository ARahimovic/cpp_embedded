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