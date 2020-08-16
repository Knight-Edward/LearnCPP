
class A:
	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.area = x * y

	def getArea(self):
		return self.area

	def printA(self):
		print('this is a rectangle!')
		print('x is : ', self.x)
		print('y is : ', self.y)
	def __mul__(self, other):
		return A(self.x * other, self.y * other)

class B(A):
	def __init__(self, x, y, z):
		super().__init__(x,y)
		self.z = z
		self.volume = z * self.getArea()
	def getVolume(self):
		return self.volume	

def main():
	print('Hello world')
	a = A(3,4)
	a.printA()
	mulA = a * 2;
	mulA.printA()
	
	b = B(3, 4, 5)
	print(b.getVolume())

if __name__ == '__main__':
	main()

