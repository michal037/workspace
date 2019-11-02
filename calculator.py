while True:
    print("Options:")
    print("  Enter + to add two numbers")
    print("  Enter - to subtract two numbers")
    print("  Enter * to multiply two numbers")
    print("  Enter / to divide two numbers")
    print("  Enter % to modulo two numbers")
    print("  Enter 'quit' to end the program")

    user_input = input(": ")

    try:
        if user_input == "quit":
            break;

        if user_input in ["+", "-", "*", "/", "%"]:
            num1 = float(input("Enter a number: "))
            num2 = float(input("Enter a number: "))

        else:
            print("Unknown input\n")
            continue

        if user_input == "+":
            output = str(num1 + num2)

        elif user_input == "-":
            output = str(num1 - num2)

        elif user_input == "*":
            output = str(num1 * num2)

        elif user_input == "/":
            output = str(num1 / num2)

        elif user_input == "%":
            output = str(num1 % num2)

        print("Result: " + output + "\n")

    except ValueError:
        print("Not a number\n")

    except ZeroDivisionError:
        if num1 == 0:
            print("Result: 0.0\n")
        else:
            print("Result: infinity\n")
