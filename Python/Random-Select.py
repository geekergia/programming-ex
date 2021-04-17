import random

inputarr = [2,4,40,13,50,14,31,15,20,8,9,10,11,5]

def partition(arr, low, high):
	pivot = arr[high]
	i = low-1

	print("paritioning arr:",arr)
	print("Pivot: ", str(pivot))

	for j in range(low, high):
		if arr[j]<=pivot:
			i+=1
			arr[i], arr[j] = arr[j], arr[i]

	arr[high], arr[i+1] = arr[i+1], arr[high]

	print("arr: ", arr)
	return i+1

def rand_part(arr, p, q):
	i = random.randint(p, q)
	arr[q], arr[i] = arr[i], arr[q]
	print(arr)
	print("rand_part i: ", i)
	return partition(arr, p, q)

def rand_select(arr, p, q, i):
	print("p,q: ", p, q)
	if p==q:
		return arr[p]

	r = rand_part(arr, p, q) #rank of pivot element
	print("r: ",r)
	k = r-p+1
	print("k: ",k)
	print("i: ",i)

	if i==k:
		return arr[r]

	if i<k:
		return rand_select(arr, p, r-1, i)
	else:
		return rand_select(arr, r+1, q, i-k)

ans = rand_select(inputarr, 0, len(inputarr)-1, min(inputarr))
print("ans:",ans)

