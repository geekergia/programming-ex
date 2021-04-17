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

table = []

#This function returns the key of the record in "table" hash table.
def KEY(i):
	return int(table[i][0][0])

#This function initializes the open address hash table to be used.
def open_init(m):
	for i in range(m):
		table.append([])
		for j in range(2):
			table[i].append([0])

#This function returns the hash function of the record.
def open_func(k,m):
	hk = int(student[k][0])%m
	return hk

#This function inserts the record in the hash table at the given hash function. Collisions are resolved by linear probing. 
#If a duplicate of the record is found, the operations is aborted. 
def open_insert(k,n,m):
	if n == m-1:
		print("Table is full")
		return 

	i = open_func(k,m)
	s = 1

	print('%s tries to first insert at position %d' %(student[k][1],i+1))

	while(True):
		if student[k][0] in table[i]:
			print("Duplicate key found")
			break

		elif KEY(i) > 0:
			print('%s collides with %s at position %d' %(student[k][1],KEY(i),i+1))
			i-=s
			if i<0:
				i+=m

			printopen(m)

		elif KEY(i) == 0:
			print('%s inserts at position %d' %(student[k][1],i+1))
			table[i][0].pop()
			table[i][1].pop()
			table[i][0].append(student[k][0])
			table[i][1].append(student[k][1])
			table[i][1].append(student[k][2])
			table[i][1].append(student[k][3])
			table[i][1].append(student[k][4]) 
			n+=1
			break 

	printopen(m)

#This function prints the open address hash table.
def printopen(m):
	print("Open Address Hash Table.....")

	for i in range(m):
		print(i+1,end="")
		print(": ",end="")
		if 0 in table[i][1] and table[i][0]:
			print("NULL")
		else:
			print(table[i][0][0], end = "")
			print("|", end = "")
			for j in range(len(table[i][1])):
				print(table[i][1][j],end = "")
				print("|", end = "")
			print()

	print()















