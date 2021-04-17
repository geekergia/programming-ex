import random

class Node(object):
	#to implement node
	def __init__(self, key, level):
		self.key = key
		self.next = [None]*(level+1)

class SkipList(object):
	#to implement skip list
	def __init__(self, maxlvl, p):
		self.max_lvl = maxlvl
		self.p = p 	#fraction of nodes with level
		self.header = self.createNode(self.max_lvl, -1)	#header node with key = -1
		self.level = 0	#current level 

	def createNode(self, lvl, key):
		n = Node(key,lvl)
		return n

	def randomLvl(self):
		lvl = 0
		while random.random() < self.p and lvl < self.maxlvl:
			lvl += 1

		return lvl

	def insert(self, key):
		update = [None]*(self.maxlvl+1)
		current = self.header

		#move forward while nodes value are less than key
		for i in range(self.level, -1, -1):
			while current.next[i] and current.next[i].key < key:
				current = current.next[i]

			#otherwise, move a level down until it is found
			update[i] = current

		current = current.forward[0]	#reached level 0

		if current == None or current.key != key:
			randlvl = self.randomLvl()

			if randlvl > self.level:
				for i in range(self.level+1, randlvl+1):
					update[i] = self.header
				self.level = randlvl

			#create new node with randlvl
			n = self.createNode(randlvl, key)

			#insert node by rearranging ref
			for i in range(randlvl+1):
				n.next[i] = update[i].next[i]
				update[i].next[i] = n


	def display(self):
		head = self.header
		for i in range(self.level+1):
			print("Level {}: ".format(lvl), end="")
			node = head.next[lvl]
			#print each node in list
			while(node!=None):
				print(node.key, end="")
				node = node.next[lvl]
			print("")

def main():
    lst = SkipList(3, 0.5) 
    lst.insert(3) 
    lst.insert(6) 
    lst.insert(7) 
    lst.insert(9) 
    lst.insert(12) 
    lst.insert(19) 
    lst.insert(17) 
    lst.insert(26) 
    lst.insert(21) 
    lst.insert(25) 
    lst.display() 

main()