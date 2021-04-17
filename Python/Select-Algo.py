import random

inputarr = [2,4,40,13,50,14,31,15,20,8,9,10,11,5,55,56,6, 12, 100, 212, 22, 44, 959, 688, 423, 123, 858,663,687,386,905,776]


def bubble(arr):
	n = len(arr)

	for i in range(n):
		for j in range(n-1):
			if arr[j] > arr[j+1]:
				arr[j], arr[j+1] = arr[j+1], arr[j]

def partition(arr, low, high):	
	pivot = arr[high]
	i = low-1

	for j in range(low, high):
		if arr[j]<=pivot:
			i+=1
			arr[i], arr[j] = arr[j], arr[i]

	arr[high], arr[i+1] = arr[i+1], arr[high]

	print("Resulting array after partition() on pivot", pivot)
	print(arr)

	return i+1	

def rand_part(arr, p, q):
	i = random.randint(p, q)
	arr[q], arr[i] = arr[i], arr[q]
	return partition(arr, p, q)

def sort(arr, n):
	medianlist = []
	j=0
	num = n//5	

	for i in range(num):
		count=0
		temparr = []
		for k in range(5):
			count+=1
			temparr.append(arr[j])
			j+=1
		bubble(temparr)
		print("group: ",temparr)
		if len(temparr)%2==0:
			medianlist.append(temparr[len(temparr)//2-1])
		else:
			medianlist.append(temparr[len(temparr)//2])
		
	return medianlist

def SELECT(arr, i, n):
	if n<5:
		bubble(arr)
		print("median of medians: ", arr)
		pivot = arr[len(arr)//2]

		return 0

	else:			
		medianlist = sort(arr, n)
		print("medians: ", medianlist)

		m = len(medianlist)
		pivot = SELECT(medianlist, (m+1//5)//2-1, m) 

		for i in range(len(arr)):
			if arr[i] == pivot:
				arr[0],arr[i] = arr[i], arr[0]
				return 0

		k = rand_part(arr, 0, len(arr)-1)

		if i==k:
			return arr[k]

		if i<k:
			return SELECT(arr, i, len(arr))
		else:
			return SELECT(arr, i-k, len(arr))

SELECT(inputarr, min(inputarr), len(inputarr))
