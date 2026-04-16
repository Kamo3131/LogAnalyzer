# LogAnalyzer
## How to compile
`cmake -B build` or `cmake -B build -G "Ninja"` (if Ninja is present)

`cmake --build build`

## Query commands
For sorting on log level:
`LOG_LEVEL="[Level]"`

For sorting on log source:
`SOURCE="[Source]"`

For sorting on log message:
`Message="[Message]"`

For sorting on timestamp range:
`TIMESTAMP from "[FromDate]" to "[ToDate]"`