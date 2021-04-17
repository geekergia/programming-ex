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

#This function returns the primary hash function of the record.
def primary(k,m):
	hk = int(student[k][0])%m

	return hk

#This function returns the secondary hash function of the record.
def secondary(k,m):
	hk = 1+ math.floor(int(student[k][0])/m)%(m-2)

	return hk

#CHECK!!!!
#This function returns the probe decrement value of the record.
def probedec(prim, sec, m, i):
	pk = (prim - i*sec)%m

	return pk

#This function initializes the ordered hash table to be used.
def order_init(m):
	for i in range(m):
		table.append([])
		for j in range(2):
			table[i].append([0])

#This function inserts the record in the hash table at the given hash function. Collisions are resolved by double hashing. 
#If a duplicate of the record is found, the operations is aborted. 
def order_insert(k,n,m):
	if n == m - 1:
		print("Table is full")
		return

	i = primary(k,m)
	sec = secondary(k,m)

	print('%s tries to first insert at position %d' %(student[k][1],i+1))

	while(True):
		if student[k][0] in table[i]:
			print("Duplicate key found")
			break

		elif KEY(i) > 0:
			if KEY(i) < int(student[k][0]):
				print('%s swaps positions with %s at position %d' %(student[k][1],table[i][1][0],i+1))
				table[i][0][0], student[k][0] = student[k][0], table[i][0][0]
				table[i][1][0], student[k][1] = student[k][1], table[i][1][0]
				table[i][1][1], student[k][2] = student[k][2], table[i][1][1]
				table[i][1][2], student[k][3] = student[k][3], table[i][1][2]
				table[i][1][3], student[k][4] = student[k][4], table[i][1][3]

				printorder(m)

			i = probedec(i,sec,m)
			if i < 0:
				i+=m

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
			return

	printorder(m)

#This function prints the ordered hash table.
def printorder(m):
	for i in range(m):
		print(i+1,end="")
		print(": ",end="")
		if 0 in table[i][1] and table[i][0]:
			print("NULL")
		else:
			print(table[i][0][0], end = "")
			print("|",end = "")
			for j in range(len(table[i][1])):
				print(table[i][1][j],end = "")
				print("|",end = "")
			print()

	print()

















