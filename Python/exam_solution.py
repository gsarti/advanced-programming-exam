import datetime
import numpy as np


# filein can be either a path or name of file: defined as a string!!

class PostcardList:
	def __init__(self,filein):
		self._file=filein   ##list or just name??
		try:
			f=open(self._file,"r")
			self._postcards=f.readlines()	
			f.close()
			self._date={}
			self._from={}
			self._to={}
			for i in range(0,len(self._postcards)):
				d,f,t=self._postcards[i].split(" ")
				d=d[5:15]
				f=f[5:-1]
				t=t[3:-2]
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
		except FileNotFoundError:
			print("Wrong file or file path: initializing empty objects")
			self._postcards=[]
			self._date={}
			self._from={}
			self._to={}
			

	def writeFile(self):
		f=open(self._file,"w")
		for i in range(0,len(self._postcards)):
			f.write(self._postcards[i])
		f.close()
	

	def readFile(self):
		f=open(self._file,"r")
		filein=f.readlines()
		f.close()
		print("Reading "+self._file+": \n")
		for i in range(0,len(filein)):
			print(filein[i])
		del filein
	

	def parsePostcards(self):
		for i in range(0,len(self._postcards)):
			d,f,t=self._postcards[i].split(" ")
			d=d[5:15]
			f=f[5:-1]
			t=t[3:-2]
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


	def updateFile(self,newfile):
		self._file=newfile

	def updateLists(self):
		f=open(self._file,"r")
		new=f.readlines()
		f.close()
		self._postcards=self._postcards+new
		self.parsePostcards()		


	def getNumberOfPostcards(self):
		print("Amount of postcards: "+str(len(self._postcards))+"\n")


	#def getPostcardsByDateRange(self,date_range):

	def getPostcardsBySender(self, sender):
		
		print("Printing postcards from "+sender+": \n")
		for i in self._from[sender]:
			print(self._postcards[i])

	def getPostcardsByReceiver(self, receiver):

                print("Printing postcards to "+receiver+": \n")
                for i in self._to[receiver]:
                        print(self._postcards[i])


