#
# spec file for package aceunit
#

Name:           aceunit
Version:        3.0.0
Release:        0
Summary:        The Advanced C and Embedded Unit test framework
License:        BSD-3-Clause
URL:            https://github.com/christianhujer/${name}
Source0:        https://github.com/christianhujer/${name}/archive/refs/tags/v%{version}.tar.gz
#BuildRequires:  
#Requires:       

%description
AceUnit is a comfortable (test discovery!) unit test framework for C,
in the best tradition of xUnit frameworks (like JUnit). Its target
audience are developers using the C programming language to develop
firmware, drivers, operating systems, and other C programs, like
command line programs. It is tiny and thus suitable even for extremely
resource-constraint environments.


%prep
%setup -q

%build
make %{?_smp_mflags}

%install
%make_install DESTDIR=%{buildroot} PREFIX=/usr

%post
ls /usr/share/doc/aceunit/

%files
/usr/bin/aceunit
/usr/include/aceunit.h
/usr/include/aceunit.mk
/usr/lib/libaceunit-abort.a
/usr/lib/libaceunit-fork.a
/usr/lib/libaceunit-setjmp.a
/usr/lib/libaceunit-simple.a
/usr/share/aceunit/nm.ac
/usr/share/aceunit/objdump.ac
/usr/share/aceunit/readelf.ac

%doc /usr/share/man/man1/aceunit.1.gz
%doc /usr/share/man/man3/aceunit.3.gz

%license /usr/share/doc/aceunit/copyright

%doc AUTHORS

%changelog
