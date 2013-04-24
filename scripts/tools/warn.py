#!/usr/bin/env python
#encoding: utf-8	

from waflib.Configure import conf

FLAGTEST="""
int main(void) { return 0; }
"""

"""
warn_all(ctx,*k,**kw)

Add CFLAG to emit all warnings

If requested, cause this warning to be treated as an error
"""

def options(ctx):
	pass

def configure(ctx):
	pass

def get_lang(lang):
	lmap={ 'C': 'C', 'C++':'CXX', 'CXX':'CXX' }
	if isinstance(lang,str):
		lang=lang.split()
	if isinstance(lang,list):
		for i in range(len(lang)):
			l=lang[i].upper()
			if l in lmap:
				lang[i]=lmap[l]
	return lang

@conf
def warn_all(ctx,*k,**kw):
	suffix=''
	lang='c c++'
	if 'error' not in kw:
		kw['error']=False
	if 'uselib_store' in kw:
		suffix='_%s'%kw['uselib_store']
	if 'lang' in kw:
		lang=kw['lang']
	lang=get_lang(lang)
	
	for p in lang:
		if not ctx.env[p+'FLAGS'+suffix]: ctx.env[p+'FLAGS'+suffix]=[]
	ctx.start_msg('emit all warnings?')
	flags=[]
	st='no'
	if not kw['error']:
		flags=['-Wall', '/Wall']
	else:
		flags=['-Werror=all','/Wall /WX']
	for f in flags:
		if ctx.check(fragment=FLAGTEST,cflags=f,mandatory=False):
			st='error' if kw['error'] else 'yes'
			for p in lang:
				ctx.env[p+'FLAGS'+suffix].append(f)
			break
	ctx.end_msg(st,'YELLOW')

@conf
def warn_extra(ctx,*k,**kw):
	suffix=''
	lang='c c++'
	if 'error' not in kw:
		kw['error']=False
	if 'uselib_store' in kw:
		suffix='_%s'%kw['uselib_store']
	if 'lang' in kw:
		lang=kw['lang']
	lang=get_lang(lang)
	for p in lang:
		if not ctx.env[p+'FLAGS'+suffix]: ctx.env[p+'FLAGS'+suffix]=[]
	ctx.start_msg('emit extra warnings?')
	flags=[]
	st='no'
	if not kw['error']:
		flags=['-Wextra']
	else:
		flags=['-Werror=extra']
	for f in flags:
		if ctx.check(fragment=FLAGTEST,cflags=f,mandatory=False):
			st='error' if kw['error'] else 'yes'
			for p in lang:
				ctx.env[p+'FLAGS'+suffix].append(f)
			break
	ctx.end_msg(st,'YELLOW')

"""
decl_after_stmt(ctx,*k,**kw)

Add -Wdeclaration-after-statement (on GCC-ish compilers)

If requested, cause this warning to be treated as an error
"""
@conf
def decl_after_stmt(ctx,*k,**kw):
	suffix=''
	if 'error' not in kw:
		kw['error']=False
	if 'uselib_store' in kw:
		suffix='_%s'%kw['uselib_store']
	if not ctx.env['CFLAGS'+suffix]: ctx.env['CFLAGS'+suffix]=[]
	ctx.start_msg('warn on declaration-after-statement?')
	flags=[]
	st='no'
	if not kw['error']:
		flags=['-Wdeclaration-after-statement']
	else:
		flags=['-Werror=declaration-after-statement']
	for f in flags:
		if ctx.check(fragment=FLAGTEST,cflags=f,mandatory=False):
			st='error' if kw['error'] else 'yes'
			ctx.env['CFLAGS'+suffix].append(f)
			break
	ctx.end_msg(st,'YELLOW')

