import datetime
import numpy as np

class PostcardList:
	def __init__(self):
		self._file="filein"   
		self._postcards=[]
		self._date={}
		self._from={}	
		self._to={}
			

	def writeFile(self):				#write to self._file all the current postCards recorded
		f=open(self._file,"w")
		for i in range(0,len(self._postcards)):
			f.write(self._postcards[i])
		f.close()
	

	def readFile(self,p): 				#read filein and update objects
		self.updateFile(p)

	def parsePostcards(self):			#update all dictonaries with new postcards added
		for i in range(0,len(self._postcards)):
			d,f,t=self._postcards[i].split(" ")
			d=d[5:15]
			f=f[5:-1]
			t=t[3:-2]
			d=datetime.datetime.strptime(d, "%Y-%m-%d")
			if d not in self._date:
				self._date[d]=[]
			self._date[d].append(i)
			if f not in self._from:
				self._from[f]=[]
			self._from[f].append(i)
			if t not in self._to:
				self._to[t]=[]
			self._to[t].append(i)
		del d,f,t


	def updateLists(self):				#update list of postcards
		f=open(self._file,"r")
		new=f.readlines()
		f.close()
		self._postcards=self._postcards+new
		self.parsePostcards()		

	def updateFile(self,newfile):                   
		self._file=newfile
		self.updateLists()

	def getNumberOfPostcards(self): 		#print current number of postcards
		return len(self._postcards)


	def getPostcardsByDateRange(self,date_range):      #collect postcards within a date_range returning a list	
		ris=[]				
		for i in self._date:
			if date_range[0]<= i <=date_range[1]:	
				for j in self._date[i]:
					ris.append(self._postcards[j])
		return ris
		

	def getPostcardsBySender(self, sender):
		#collect postcards for a sender returning a list
		ris=[]
		if sender in self._from:
			for i in self._from[sender]:
				ris.append(self._postcards[i])
		return ris
		


	def getPostcardsByReceiver(self, receiver):		#collect postcards for a receiver returning a list
		ris=[]
		if receiver in self._to:
			for i in self._to[receiver]:
				ris.append(self._postcards[i])
		return ris


