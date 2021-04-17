import math    

student = [['202026108', 'Janet','Baker','18/12/2004','F'],['202046256','Darren','Kirk','19/12/2004','M'],
['202098353','Sophie','Meadows','20/12/2003','F'],['202037156','Ravi','Patel','21/12/2004','M'],
['202046231','Daisy','Rogers','22/12/2003','F'],['202081828','Tom','Rogers','22/12/2003','M'],
['202119030','Brett','Akers','11/10/2004','M'],['202139948','John','Deakin','03/12/2004','M'],
['202132477','Celia','Fisher','20/02/2005','F'],['202144585','Leo','Harris','21/09/2004','M'],
['202116573','Shan','Patel','14/06/2005','F'],['202131784','Laura','Ross','11/09/2005','F'],
['202125066','Jay','Harker','16/06/2005','M'],['202280420','Sally','Brown','18/12/2005','F'],
['202259013','Jane','Carter','12/09/2005','F'],['202287054','Paul','Edwards','20/04/2006','M'],
['202277456','Rachael','Harris','11/12/2005','F'],['202256394','Martin','Lampton','02/04/2006','M'],
['202266686','Kelly','Sharp','23/07/2006','F'],['202218749','Marc','Levine','12/11/2006','M']]

table=[]

#This function returns the key of the record in "table" hash table at index 'j'.
def KEY(alpha,j):
	return alpha[j][0]

#This function initializes the chained hash table to be used.
def chain_init(m):
	for i in range(m):
		table.append([])

#This function returns the hash function of the record by using the multiplicative method.
def chain_func(k):
	theta = 0.6180339887
	m = 16

	value = m*(int(student[k][0])*theta%1)
	hk = math.floor(value)

	return hk

#This function inserts the record in the hash table at the given hash function. Collisions are resolved by chaining. 
#If a duplicate of the record is found, the operations is aborted. 
def chain_insert(k):
	i = chain_func(k)
	alpha = table[i]
	j = 0

	while alpha==True:
		if student[i][0] in alpha:
			print("Duplicate key found.")
			return
		else:
			j+=1

	alpha.append([])
	alpha[j].insert(0, student[k][0])
	alpha[j].insert(1, student[k][1])
	alpha[j].insert(2, student[k][2])
	alpha[j].insert(3, student[k][3])
	alpha[j].insert(4, student[k][4])

	return i

#This function prints the chained hash table.
def printchain(m):
	print()

	for i in range(m):
		for j in range(len(table[i])):
			if table[i][j] != []:
				print(i+1, end="")
				print(": ", end="")
				for k in range(len(table[i][j])):
					if k%5==0 and k!=0:
						print(" -> ", end ="")
					print(table[i][j][k], end = "")
					print("|",end="")
					
		print()
					
	print()



