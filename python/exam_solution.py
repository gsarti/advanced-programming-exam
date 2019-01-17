"""
Author: Giulia Franco
Date: January 17, 2019
Description: Module containing PostcardList class.
"""

from datetime import datetime


class PostcardList:
	"""
	Class to read/write postcard messages from/to a properly
	formatted file (date: $(DATE); from: $(SENDER); to: $(RECEIVER);)
	"""
	def __init__(self):
		# File name from which the postcards were taken.
		self._file = ""
		# List of postcards read from file.
		self._postcards = []
		# A dictionary date,index for all postcard dates.
		self._date = {}
		# A dictionary string, index for all postcard senders.
		self._from = {}
		# A dictionary string, index for all postcard receivers.
		self._to = {}

	def writeFile(self, filename):
		"""
		Writes all the recorded postcards to a file.
		filename -> The name of the file to be written.
		"""
		file = open(filename, "w")
		for postcard in self._postcards:
			file.write(postcard)
		file.close()

	def readFile(self, new_file):
		"""
		Sets a new file, read and parse all postcards from it.
		filename -> The name of the new file.
		"""
		self._postcards = []
		self._file = new_file
		file = open(self._file, "r")
		for line in file:
			self._postcards.append(line)
		file.close()
		self.parsePostcards()

	def parsePostcards(self):
		"""
		Updates all dictonaries from current postcards.
		"""
		for i in range(0, len(self._postcards)):
			date, sender, receiver = self._postcards[i].split(" ")
			# Remove extra characters from strings.
			date = date[5:15]
			sender = sender[5:-1]
			receiver = receiver[3:-2]
			date = datetime.strptime(date, "%Y-%m-%d")
			if date not in self._date:
				self._date[date] = []
			self._date[date].append(i)
			if sender not in self._from:
				self._from[sender] = []
			self._from[sender].append(i)
			if receiver not in self._to:
				self._to[receiver] = []
			self._to[receiver].append(i)

	def updateFile(self, filename):
		"""
		Updates a file appending the current postcards to it.
		filename -> The name of the file.
		"""
		file = open(filename, "a")
		for postcard in self._postcards:
			file.write(postcard)
		file.close()

	def updateLists(self, new_file):
		"""
		Updates the list of postcards from new file
		without resetting it and parses it.
		new_file -> The new file to be used for updates.
		"""
		self._file = new_file
		file = open(self._file, "r")
		for line in file:
			self._postcards.append(line)
		file.close()
		self.parsePostcards()

	def getNumberOfPostcards(self):
		"""
		Prints the current number of postcards.
		"""
		return len(self._postcards)

	def getPostcardsByDateRange(self, date_range):
		"""
		Collect postcards within a date range, returning a list.
		date_range -> A tuple of dates.
		"""
		postcards_by_date = []
		for i in self._date:
			if date_range[0] <= i <= date_range[1]:
				for j in self._date[i]:
					postcards_by_date.append(self._postcards[j])
		return postcards_by_date

	def getPostcardsBySender(self, sender):
		"""
		Collect postcards for a specific sender, returning a list.
		sender -> The name of the sender to be used as filter.
		"""
		postcards_by_sender = []
		if sender in self._from:
			for i in self._from[sender]:
				postcards_by_sender.append(self._postcards[i])
		return postcards_by_sender

	def getPostcardsByReceiver(self, receiver):
		"""
		Collect postcards for a specific receiver, returning a list.
		receiver -> The name of the receiver to be used as filter.
		"""
		postcards_by_receiver = []
		if receiver in self._to:
			for i in self._to[receiver]:
				postcards_by_receiver.append(self._postcards[i])
		return postcards_by_receiver
