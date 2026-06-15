*This project has been created as part of the 42 curriculum by wkozlows.*

# minishell — As beautiful as a shell

## Description

Minishell is a simplified Unix shell written in C, inspired by Bash. The goal of the project is to implement a functional interactive shell capable of parsing and executing commands, handling pipes and redirections, expanding environment variables, and managing signals correctly.

Key features:
- Interactive prompt with command history
- Execution of binaries via `PATH` lookup or relative/absolute paths
- Pipes (`|`) connecting multiple commands
- Redirections: `<`, `>`, `>>`, `<<` (here-doc)
- Environment variable expansion (`$VAR`, `$?`)
- Single (`'`) and double (`"`) quote handling
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`

## Instructions

### Requirements

- GCC or Clang with C standard support
- GNU Readline library (`libreadline-dev` on Debian/Ubuntu, or `brew install readline` on macOS)

### Compilation

```bash
make
```

This builds the `minishell` binary. Other available targets:

| Target | Description |
|--------|-------------|
| `make all` | Build the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the binary |
| `make re` | Full rebuild |

### Execution

```bash
./minishell
```

The shell launches with an interactive prompt. Type any command and press Enter to execute it. Press `Ctrl+D` to exit.

### Examples

```
/home/user $piwkomuszla$> echo "Hello, $USER"
Hello, wkozlows
/home/user $piwkomuszla$> ls -la | grep ".c" | wc -l
42
/home/user $piwkomuszla$> export GREETING="hello world"
/home/user $piwkomuszla$> echo $GREETING
hello world
/home/user $piwkomuszla$> cat << EOF
> line one
> line two
> EOF
line one
line two
/home/user $piwkomuszla$> exit
```

## Resources

### References

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — primary behavioral reference for all shell features
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentation for readline, history, and signal interaction
- [The Open Group — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — POSIX shell specification
- [Advanced Programming in the UNIX Environment (Stevens & Rago)](https://www.apuebook.com/) — reference for `fork`, `execve`, `pipe`, `dup2`, signal handling
- [Linux man pages](https://man7.org/linux/man-pages/) — `signal(7)`, `waitpid(2)`, `pipe(2)`, `execve(2)`, `dup2(2)`

### AI Usage

AI (Claude) was used during this project for:
- **Debugging and code review**: identifying edge cases in signal handling, heredoc flow, and pipe teardown
- **Behavioral reference**: clarifying how Bash handles specific corner cases (e.g., `$?` after `Ctrl+C`, export output format, unclosed quote detection)
- **README drafting**: generating the initial structure of this document

All AI-generated suggestions were reviewed, tested, and adapted manually before inclusion in the project.
