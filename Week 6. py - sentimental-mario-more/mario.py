# TODO

def main():

	height = 0
	while  0 >= height or height > 8:
		try:
			height = int(input("height: "))
		except:
			height = 0


	for i in range(1,height+1):
		spaces(height-i)
		hashes(i)
#----------------------------------

def spaces(n):
	print(" " *n, end="")
#----------------------------------

def hashes(n):

	print("#"*n, end="")
	print("  ", end="")
	print("#"*n, end="")
	print("")

main()
