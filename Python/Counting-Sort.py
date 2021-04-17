#Python3 for implementation

def countSort():
	text = [['hello', 'world', 'my', 'name', 'is'],['Gianna'], ['I', 'live', 'in', 'a', 'castle', 'blab', '123'],['123'], ['hi','yo','bye']]
	numword = [0,0,0,0,0]

	for i in range(len(text)):
		for j in range(len(text[i])):
			numword[i]+=1

	print("Array T: ", text)
	print("Input Array: ", numword)

	maxi = max(numword)
	mini = min(numword)
	n = len(numword)

	temp = []

	for i in range(maxi+1):
		temp.append(0)

	for j in range(n):
		temp[numword[j]]+=1

	print("Count List: ",temp)

	for i in range(1, maxi+1):
		temp[i] = temp[i] + temp[i-1]

	print("Sum of Count List: ", temp)

	sort = []

	for i in range(n+1):
		sort.append(0)

	for j in range(n-1, -1, -1):
		sort[temp[numword[j]]] = text[j]
		temp[numword[j]] = temp[numword[j]] - 1	
	
	print('Sorted Array T: ')
	for i in range(1, len(sort)):
		print(sort[i])

countSort()