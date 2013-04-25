#!/bin/env python
import sys, os, shutil
from waflib.Configure import conf
from waflib.Build import BuildContext, CleanContext
from waflib.Build import InstallContext, UninstallContext
from waflib.extras.msvs import msvs_generator, msvs_2008_generator
from waflib.Utils import unversioned_sys_platform
from waflib import Logs, Options, Context, Node
from waflib.TaskGen import after

APPNAME='webvtt'
VERSION='0.4'
subdirs=['src','test','demos']
builds=['debug','release']

#Location of local waf tools
local=os.path.abspath(os.path.join('scripts','tools'))

def options(ctx):
	ctx.load('compiler_c compiler_cxx waf_unit_test xcode msvs make eclipse')
	ctx.load('pthread', tooldir=local)
	ctx.load('warn', tooldir=local)
	ctx.add_option('--show-all',dest='show_all', default=False,
				  action='store_true',
				  help='Print full output of unit tests')
	g=ctx.add_option_group('GNU Utilities')
	g.add_option('--gcov',dest='gcov', default=False,
  							action='store_true',
								help='Build with code coverage analysis support (GCC only)')
	g.add_option('--gprof',dest='gprof', default=False,
								action='store_true',
								help='Build with GNU profiling support (GCC only)')
	g=ctx.add_option_group('Options')
	g.add_option('--debug',dest='debug', default=False,
								action='store_true',
								help='Build with debug symbols')
	g.add_option('--enable-valgrind',dest='valgrind', default=False,
								action='store_true', help='Run tests through Valgrind')

@conf
def get_sources(ctx,path,skip=[]):
	ext=['.cpp','.cc','.c']
	src=[]
	ctxpath=os.path.join(ctx.path.abspath(), '')
	for ent in os.listdir(path):
		if ent not in skip:
			full=os.path.abspath(os.path.join(path,ent))
			if os.path.isdir(full):
				src.extend(ctx.get_sources(full))
			elif os.path.isfile(full):
				for x in ext:
					if ent.endswith(x):
						full=full.replace(ctxpath,'')
						src.append(full)
						break
	return src

def configure(ctx):
	ctx.load('compiler_c compiler_cxx waf_unit_test xcode msvs make eclipse pthread')
	ctx.load('pthread', tooldir=local)
	ctx.load('warn', tooldir=local)
	build='debug' if ctx.options.debug else'release'
	# Generate {OS}-{ARCH}-{VARIANT} build name
	V='%s-%s-%s'% (ctx.env.DEST_OS,ctx.env.DEST_CPU,build)
	ctx.setenv(V,ctx.env.derive())
	ctx.variant=V

	ctx.warn_all(lang='c') # Try to enable reporting all warnings
	ctx.warn_extra(lang='c') # Try to enable reporting extra warnings
	ctx.decl_after_stmt(error=True) # Try to make declaration-after-statement an error
	#Disable some silly MSVC warnings:
	ctx.ignore_warning(flags='/wd4820 /wd4996 /wd4267')

	if ctx.env.CXX_NAME is 'msvc':
		# Can disable extensions (in MSVC) with by uncommenting here
		# ctx.env.CXXFLAGS.extend(['/D_HAS_EXCEPTIONS=0','/wd4355'])
		if ctx.options.debug:
      			# If it's a debug build, add /Zi and /debug
			ctx.env.CXXFLAGS.extend(['/Zi'])
			ctx.env.LINKFLAGS.extend(['/debug'])
	elif ctx.env.CXX_NAME in ['g++','clang']:
		if ctx.options.debug:
			# If we're dealing with g++/clang, add '-g' for debugging
			ctx.env.CXXFLAGS.extend(['-g'])
			ctx.env.CFLAGS.extend(['-g'])
		if ctx.env.CC_NAME is 'gcc':
			if ctx.options.gprof:
				ctx.env.CXXFLAGS_PROFILER.extend(['-p'])
				ctx.env.CFLAGS_PROFILER.extend(['-p'])
			if ctx.options.gcov:
				ctx.env.CXXFLAGS_COVERAGE.extend(['-fprofile-arcs','-ftest-coverage'])
				ctx.env.CFLAGS_COVERAGE.extend(['-fprofile-arcs','-ftest-coverage'])

	ctx.check(header_name='stdint.h',define_name='WEBVTT_HAVE_STDINT',mandatory=False)
	ctx.check_pthread()
	ctx.write_config_header(os.path.join(V,'include','webvtt','webvtt-config.h'),
	                        guard='__WEBVTT_CONFIG_H__', top=True)
	#Update variants
	set_variant(V)

def build(ctx):
	if ctx.cmd is 'check': ctx.recurse(['src','test'])
	elif ctx.cmd is 'demos': ctx.recurse(['src','demos'])
	else: ctx.recurse(subdirs)

def set_variant(V):
	for y in (BuildContext, CleanContext, InstallContext, UninstallContext,
            msvs_generator, msvs_2008_generator):
		class tmp(y):
			variant=V
	#Extra "commands"
	for y in 'check demos'.split():
		class tmp(BuildContext):
			cmd=y
			fun='build'
			variant=V

def init(ctx):
	try: set_variant(Context.variant)
	except: pass
