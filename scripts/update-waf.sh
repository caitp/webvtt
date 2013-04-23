#!/bin/sh

#Update 'waf' script
#
#Usage:   waf-update.sh <Git Repo> <Rev/Branch>
#       | waf-update.sh

#Perl scripts used for waf-tools parsing
gettools=$( cat <<EOF
\$have=0;
while(<STDIN>) {
  chomp;
  \$_ =~ s/^\s+//;
  \$_ =~ s/\s+\$//;
  \$_ =~ s/\s*#.*//;
  if( length(\$_) ) {
    \$_ = ",\$_" unless !\$have;
    \$have = 1;
    print \$_;
  }
}
EOF
)
getprelude=$( cat <<EOF
\$have=0;
while(<STDIN>) {
  chomp;
  \$_ =~ s/\s+\$//;
  \$_ =~ s/\s*#.*//;
  \$_ =~ s/\\t/\\\\t/g;
  \$_ =~ s/^!//;
  if( length(\$_) ) {
    \$_ = "\\\\n\$_" unless !\$have;
    \$have = 1;
    print \$_;
  }
}
EOF
)

if [ "$1" = "--help" ]; then
  echo "Update Waf script"
  echo "Usage: waf-update.sh [<git repo/url>] [<rev/branch>]"
  echo "       (Arguments in square-brackets are optional)"
  exit 0
fi

#Ensure that git is present on the system
git --version 2>&1 >/dev/null
if [ $? -ne 0 ]; then
  echo "Git does not seem to be installed. Aborting."
  exit 1
fi

start=$PWD
script=$(cd $(dirname $0) && pwd)
root=$(cd $script/.. && pwd)
cd $script

#These should really not be needed ...
tempify() {
  rm -rf $root/waf-*
  rm -rf $root/.lock-waf*
  rm $root/waf
  rm $root/waf.bat
  mv $root/wscript $root/wscript$$
}

untempify() {
  mv $root/wscript$$ $root/wscript
}

die() {
  untempify
  exit 1
}

tempify

url=https://code.google.com/p/waf/
rev=
abslocal=

if [ $# -gt 0 ]; then
  if [ $# -gt 1 ]; then
# Repo and Revision
    url="$1"
    rev="$2"
    if [ [ "$1" != *://*] -a !-d "$1"  ]; then
      rev="$1"
      url="$2"
    fi
  else
    if [[ $1 == *://* ]]; then
      if [ -d "$1" ]; then
# Default revision from local
        url=$1
      else
# Revision $1 from default remote
        rev=$1
      fi
    else
# Default revision from remote
      url=$1
    fi
  fi
fi

# Get absolute path of local repository
if [ -d "$url" ]; then
  abslocal=$(cd "$url" && pwd && cd $script)
fi

#use HEAD revision by default
if [ "x$rev" = x ]; then
  rev=HEAD
fi

# Try to get it:
temp=$script/waf
if [ "x$abslocal" = "x$temp" ]; then
  echo "error: can't use '$temp' as a repo location."
  cd $start
  die
fi

echo "Repository: $url"
if [ -n "$rev" ]; then
  echo "Revision:   $rev"
fi

# remote temp directory if it exists
if [ -d $temp ]; then
  rm -rf $temp || die
fi
if [ "x$abslocal" = x ]; then
  mkdir $temp || die
  (git archive --remote=$url $rev | tar -C $temp -xf -) 2>/dev/null
  if [ $? -ne 0 ]; then
#   Maybe archive operation was not supported by remote.
    temp2=$temp$$
    git clone $url $temp2
    if [ $? -ne 0 ]; then
      cd $start
      rm -rf $temp
      rm -rf $temp2
      die
    fi
    cd $temp2 && git archive --format=tar $rev | tar -C $temp -xf -
    if [ $? -ne 0 ]; then
      cd $start
      rm -rf $temp
      rm -rf $temp2
      die
    fi
    cd $start
    rm -rf $temp2
  fi
else
  mkdir $temp || die
  cd $url && git archive $rev | tar -C $temp -xf -
  if [ $? -ne 0 ]; then
    cd $start
    rm -rf $temp
    die
  fi
  cd $start
fi

cd $temp

waftools=
wafprelude=
#Read extras to build with from file:
if [ -f $script/waf-tools ]; then
    perl --version 2>&1 >/dev/null
    if [ $? -ne 0 ]; then
      echo "Perl not found: can't process $script/waf-tools"
    else
      echo "Reading $script/waf-tools"
      waftools=$(grep -v '^[!#\n]' $script/waf-tools | perl -e "$gettools" )
      wafprelude=$(grep '^!' $script/waf-tools | perl -e "$getprelude" )
    fi
fi

wt=
wp=
if [ "x$waftools" != x ]; then
  wt="--tools=$waftools"
  if [ "x$wafprelude" != x ]; then
    wp="--prelude=$'$wafprelude'"
  fi
fi

./waf-light --make-waf --make-batch $wt $wp 2>/dev/null
if [ $? -ne 0 ]; then
  die
fi

cd $start

#Copy script into root directory
cp $temp/waf $root/
cp $temp/waf.bat $root/

chmod --version 2>&1 >/dev/null
if [ $? -eq 0 ]; then 
chmod +x $root/waf
fi

#Delete the 'waf' directory, though...
rm -rf $temp

untempify
