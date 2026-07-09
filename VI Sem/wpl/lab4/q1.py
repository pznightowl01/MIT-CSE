#Write a python program to reverse a content a file and store it in another file.
def reverse_file(inp_f, out_f):
with open(inp_f, "r", encoding="utf-8") as f:
content = f.read()
with open(out_f, "w", encoding="utf-8") as f:
f.write(content[::-1])
def main():
inp_f = "inp_f.txt"
out_f = "out.txt"
reverse_file(inp_f, out_f)
if __name__ == "__main__":
main()
