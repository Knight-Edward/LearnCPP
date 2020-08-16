class A:
	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.area = x * y
	
	def printA(self):
		print('this is a rectangle')
		print('x is:', self.x)
		print('y is:', self.y)

class B(A):
	def __init__(self, x, y, z):
		super().__init__(x, y)
		self.z = z
		self.volume = z * self.area
	def getVolume(self):
		return self.volume

def main():
	print('Hello world')
	# class 类
	# object 实例
	a = A(3,4)  # 矩阵
	a.printA()
	# result = a * 3
	b = B(3, 4, 5)
	vol = b.getVolume()
	print('vol: ',vol) 

if __name__ == '__main__':
	main()
