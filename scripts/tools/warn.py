#!/usr/bin/env python
#encoding: utf-8	

from waflib.Configure import conf
MSVC_COMPILERS=['msvc','msvc2008','msvs','msvs2008']
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
	ret=[]
	lmap={ 'C': 'C', 'C++':'CXX', 'CXX':'CXX' }
	if isinstance(lang,str):
		lang=lang.split()
	if isinstance(lang,list):
		for i in range(len(lang)):
			l=lang[i].upper()
			if l in lmap:
				ret.append(lmap[l])
	return ret

@conf
def test_wflags(ctx,*k,**kw):
	x=kw
	suffix=''
	lang=['C','CXX']
	flags=[]
	x['msg']=x['okmsg']=x['errmsg']=''
	x['mandatory']=False
	if 'error' not in kw:
		kw['error']=False
	if 'uselib_store' in kw:
		suffix='_%s'%kw['uselib_store']
		del x['uselib_store']
	if 'lang' in kw:
		lang=get_lang(kw['lang'])
		del x['lang']
	if 'flags' in x:
		flags=x['flags']
		if isinstance(flags,str):
			flags=flags.split()
		if not isinstance(flags,list):
			raise 'flags parameter must be a list'
		del x['flags']
	def compiler_name(p):
		return '%s_NAME' %('CC' if p is 'C' else p)
	for f in flags:
		have=False
		for p in lang:
			if f.startswith('-W') and ctx.env[compiler_name(p)] in MSVC_COMPILERS:
				continue
			if ((f.startswith('/wd') or f.startswith('/wo') 
				or f.startswith('/we')) and ctx.env[compiler_name(p)] 
				not in MSVC_COMPILERS):
				continue
			msg='no'
			name='%sFLAGS%s'%(p,suffix)
			if name not in ctx.env: ctx.env[name]=[]
			ctx.env[name].append(f)
			ctx.start_msg('Checking %s in %sFLAGS'%(f,p))
			ret=ctx.check(**x)
			if ret:
				msg='yes'
				have=True
			ctx.end_msg(msg,'GREEN' if msg is 'yes' else 'YELLOW')
		if have: break

@conf
def warn_all(ctx,*k,**kw):
	error=False
	if 'error' in kw:
		del kw['error']
		error=kw['error']
	flags=None
	if not error:
		flags=['-Wall', '/Wall']
	else:
		flags=['-Werror=all','/Wall /WX']
	kw['flags']=flags
	ctx.test_wflags(**kw)

@conf
def warn_extra(ctx,*k,**kw):
	error=False
	if 'error' in kw:
		del kw['error']
		error=kw['error']
	flags=None
	if not error:
		flags=['-Wextra']
	else:
		flags=['-Werror=extra']
	kw['flags']=flags
	ctx.test_wflags(**kw)

"""
decl_after_stmt(ctx,*k,**kw)

Add -Wdeclaration-after-statement (on GCC-ish compilers)

If requested, cause this warning to be treated as an error
"""
@conf
def decl_after_stmt(ctx,*k,**kw):
	error=False
	if 'error' in kw:
		error=kw['error']
		del kw['error']
	flags=None
	if not error:
		flags=['-Wdeclaration-after-statement']
	else:
		flags=['-Werror=declaration-after-statement']
	kw['flags']=flags
	ctx.test_wflags(**kw)

@conf
def ignore_warning(ctx,*k,**kw):
	if 'warning' in kw:
		if isinstance(kw['warning'],str):
			kw['warning']=kw['warning'].split()
		if not isinstance(kw['warning'],list):
			return
		kw['flags']=kw['warning']
		del kw['warning']
	if 'flags' not in kw:
		return
	ctx.test_wflags(**kw)
