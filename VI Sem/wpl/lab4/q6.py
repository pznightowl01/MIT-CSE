# Write a Python class to implement pow(x, n).
class Power:
def __init__(self, base, exp):
self.base = base
self.exp = exp
def calculate_power(self):
return self._pow(self.base, self.exp)
def _pow(self, x, n):
if n == 0:
return 1
if n < 0:
return 1 / self._pow(x, -n)
half_power = self._pow(x, n // 2)
if n % 2 == 0:
return half_power * half_power
else:
return half_power * half_power * x
def main():
base = float(input("Enter base: "))
exp = int(input("Enter exponent: "))
calculator = Power(base, exp)
result = calculator.calculate_power()
print("Answer:", result)
if __name__ == "__main__":
main()
