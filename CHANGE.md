# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### [0.3.0] - 2026-01-25
#### Added
- `loggerprefix.h` for logging functionality
- New log level
- `screen` support
- `switchstand`
- `drivingdirection`
- New headers
- Setters
- `glib` integration
- `reopen` support
- Default and explicit destructors

#### Changed
- Use `std::format`
- Refactor timestamp handling in `loggerprefix.h`
- Rename `getString()` to `toString()` for clarity and consistency
- Split larger routines into several functions
- Replace deprecated `throw` specifications with `noexcept`
- Remove `boost` dependency
- Remove `syslog` and fix locking
- Remove `atomic.h` and `log.h`
- Add namespace

#### Fixed
- Array range bug
- Missing header

### [0.2.0] - 2022-11-27
#### Added
- `daemon` and `ini` file support
- Exception handling
- Assignment operator
- `AM_CPPFLAGS` to the build configuration

#### Changed
- Outsource and remove the JSON dependency
- Remove `boost` dependency
- Convert enums into enum classes
- Rename the library
- Replace deprecated functions
- Remove the logger
- Adjust namespaces

#### Fixed
- Version parsing now accepts `.`
- Disable `-Wstringop-truncation` warning at `strncpy`

### [0.1.0] - 2019-02-09
#### Added
- Library created
- IPC class (message queue based) with signal handler
- Message system and message handling (e.g. Connectivity, ambient-light,
  emergency-stop and layout messages)
- Ring buffer
- Enum-to-string conversion
- Read version as string
