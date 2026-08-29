import argparse
import sys

def format_result(val):
    if val.is_integer():
        return int(val)
    return val

def add(a, b):
    return a + b

def sub(a, b):
    return a - b

def mul(a, b):
    return a * b

def div(a, b):
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b

def main():
    parser = argparse.ArgumentParser(description="A basic calculator CLI")
    parser.add_argument("operation", choices=["add", "sub", "mul", "div"], help="The operation to perform (add, sub, mul, div)")
    parser.add_argument("numbers", help="Comma-separated numbers (e.g., 1,2)")

    args = parser.parse_args()

    try:
        nums = [float(x.strip()) for x in args.numbers.split(',')]
        if len(nums) != 2:
            print("Error: Please provide exactly two comma-separated numbers (e.g., 1,2)", file=sys.stderr)
            sys.exit(1)
        a, b = nums[0], nums[1]

        if args.operation == "add":
            result = add(a, b)
        elif args.operation == "sub":
            result = sub(a, b)
        elif args.operation == "mul":
            result = mul(a, b)
        elif args.operation == "div":
            result = div(a, b)

        print(format_result(result))

    except ValueError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
