from ctypes import *
import sys

class Lib:
	""" Initialize the object by loading either the system default library, 
		or the one passed in libpath """
	def __init__(self,libpath=None):
		self.load(libpath)
		
	""" Try to load the shared library """
	def load(self,libpath=None):
		if sys.version_info >= (3,0):
			if isinstance(libpath,str):
				self.load(libpath)
		else:
			if isinstance(libpath,basestring):
				self.load(libpath)