# first-CLI
a normal CLI application, on my journey on how to make CLIs 

## pyc - Python Basic Calculator CLI

`pyc` is a basic calculator command-line tool written in Python. It allows you to perform basic arithmetic operations (addition, subtraction, multiplication, and division) directly from your terminal.

### Installation

To install `pyc` locally, navigate to the repository directory and run:

```bash
pip install -e .
```

This will install the CLI in editable mode, making the `pyc` command available in your environment.

### Usage

The `pyc` command follows this syntax:

```bash
pyc <operation> <number1,number2>
```

#### Supported Operations
- `add`: Addition
- `sub`: Subtraction
- `mul`: Multiplication
- `div`: Division

#### Examples

Addition:
```bash
$ pyc add 1,2
3
```

Subtraction:
```bash
$ pyc sub 5.5,2
3.5
```

Multiplication:
```bash
$ pyc mul 3,4
12
```

Division:
```bash
$ pyc div 10,2
5
```
