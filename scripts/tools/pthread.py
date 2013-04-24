#!/usr/bin/env python
#encoding: utf-8

from os import environ
from waflib.Configure import conf

PTHREAD_SIMPLE="""
#include <pthread.h>
int main(void) {
	pthread_t th;
	pthread_join(th, 0);
	pthread_attr_init(0);
	pthread_cleanup_push(0,0);
	pthread_create(0,0,0,0);
	pthread_cleanup_pop(0);
}

"""
PTHREAD_ATTR="""
#include <pthread.h>
int main(void) {
  int attr=%s;
  return attr;
}
"""

def options(ctx):
	pass

def configure(ctx):
	pass

@conf
def check_pthread(ctx,*k,**kw):
	ctx.start_msg('Checking for pthread')
	have_pthread='no'

	envlibs=environ.get('PTHREAD_LIBS',None)
	envflags=environ.get('PTHREAD_CFLAGS',None)
	ret=None
	# If the user has set any of the PTHREAD_LIBS, etcetera environment
	# variables, and if threads linking works using them:
	if (envlibs or envflags):
		ctx.env.extend_unique('LINKFLAGS_pthread',envlibs)
		ctx.env.extend_unique('CFLAGS_pthread',envflags)
		ret=ctx.check(function_name='pthread_join', use='pthread',
									 mandatory=False)
		if not ret:
			ctx.env['LINKFLAGS_pthread']=[]
			ctx.env['CFLAGS_pthread']=[]

	flags=['pthreads',None,'thread','-pthread',
				'-pthreads','-mthreads', 'pthread', '--thread-safe', '-mt',
				'pthread-config','-Kthread','-kthread']

	if 'sunos' is ctx.env.HOST_OS:
		# libc on Solaris (sometimes) contains stubbed versions of pthread
		# routines -- which will result in false positives for linker tests
		# Look for -pthreads and -lpthread first:
		flags[0:0]=['-pthreads','pthread','-mt','-pthread']
	for f in flags:
		cf=None
		lf=None
		if f is None:
			# Try without adding any flags
			pass
		elif f.startswith('-'):
			# Try with CFLAG
			cf=f
		elif f is 'pthread-config':
			# Try to use 'pthread-config' program to get cflags/ldflags
			try:
				p=subprocess.Popen(['pthread-config','--cflags'],stdout=PIPE)
				o=p.communicate()
				if len(o): cf=o
				p=subprocess.Popen(['pthread-config','--ldflags'],stdout=PIPE)
				o=p.communicate()
				if len(o): lf[0]=o
				p=subprocess.Popen(['pthread-config','--libs'],stdout=PIPE)
				o=p.communicate()
				if len(o): lf[1]=o
				lf=' '.join(lf)
			except: next
		else:
			lf='-l%s'%f

		if cf:
			ret=ctx.check(cflags=cf, mandatory=False,use='pthread',
										)
		if lf:
			ret=ctx.check(linkflags=lf,mandatory=False,use='pthread',
										)
		if ret:
			have_pthread='yes'
			if cf: ctx.env.append_unique('CFLAGS_pthread',cf)
			if cf: ctx.env.append_unique('CXXFLAGS_pthread',cf)
			if lf: ctx.env.append_unique('LINKFLAGS_pthread',lf)
			break

	# Various other checks:
	if have_pthread is 'yes':
		attr_name='unknown'
		for attr in ['PTHREAD_CREATE_JOINABLE','PTHREAD_CREATE_UNDETACHED']:
			if ctx.check(fragment=PTHREAD_ATTR%attr, mandatory=False,
										use='pthread'):
				attr_name=attr
				break
		# If we have a non-standard name for PTHREAD_CREATE_JOINABLE
		# Store the nonstandard flag in the configuration header.
		if attr_name is not 'PTHREAD_CREATE_JOINABLE':
			ctx.env.append_unique('CPPFLAGS_pthread','-DPTHREAD_CREATE_JOINABLE=%s'%attr)

		flag=None
		if ctx.env.DEST_OS in ['aix','freebsd','darwin']:
			flag='-DTHREAD_SAFE'
		elif ctx.env.DEST_OS in ['sunos','hpux']:
			flag='-D_REENTRANT'
		if flag is not None:
			ctx.env.append_unqiue('CPPFLAGS_pthread',flag)

		# More AIX lossage: must compile with xlc_r or cc_r
		if ctx.env.DEST_OS in ['aix']:
			if ctx.env.CC not in ['gcc','xlc_r', 'cc_r']:
				have_pthread='no'

		# We might need to use '-pthread' for LINKFLAGS too
		if ('-pthread' in ctx.env['CFLAGS_pthread']
				and '-pthread' not in ctx.env['LINKFLAGS_pthread']):
			if not ctx.check(fragment=PTHREAD_SIMPLE,use='pthread',mandatory=False):
				ctx.env.append_unique('LINKFLAGS_pthread','-pthread')

	ctx.end_msg(have_pthread,'RED' if have_pthread is 'no' else 'GREEN')

