# Write a Python class which has two methods get_String and print_String. The
# get_String accept a string from the user and print_String print the string in upper
# case.
class String:
def __init__(self):
self.string = ""
def get_String(self):
self.string = input("enter a string: ")
def print_String(self):
print(self.string.upper())
def main():
processor = String()
processor.get_String()
processor.print_String()
if __name__ == "__main__":
main()
