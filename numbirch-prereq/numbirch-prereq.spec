Name: numbirch-prereq
Version: 0.0.0
Release: 1
Summary: Prerequisites for NumBirch
Vendor: Lawrence Murray <lawrence@indii.org>
License: BSD-2-Clause
Group: Development/Libraries/C and C++
URL: https://birch.sh
Source0: %{name}-%{version}.tar.gz

BuildRequires: gcc-c++ autoconf automake libtool

%description
Prerequisites for NumBirch, including custom jemalloc build and compiler wrapper.
This package is meant for development purposes only.

%package devel
Summary: Development files for numbirch-prereq
%description devel
Development files for for numbirch-prereq.

%package devel-static
Summary: Static libraries for for numbirch-prereq
%description devel-static
Static libraries for for numbirch-prereq.

%if 0%{?suse_version}
%debug_package
%else
%global debug_package %{nil}
%endif

%prep
%setup -n %{name}-%{version}

%build

# tweaks to link-time optimization flags to avoid RPM lint errors on static
# library builds
%define _lto_cflags -flto -ffat-lto-objects

%if 0%{?mageia} == 7
%configure2_5x --disable-assert --disable-shared --enable-static
%else
%configure --disable-assert --disable-shared --enable-static
%endif
%make_build

%install
%make_install

%files devel
%{_includedir}/jemalloc/jemalloc_numbirch.h
%{_bindir}/dpcpp_wrapper
%{_bindir}/nvcc_wrapper

%files devel-static
%{_libdir}/libjemalloc_numbirch.a
%{_libdir}/libjemalloc_numbirch_pic.a

%exclude %{_bindir}/jemalloc-config
%exclude %{_bindir}/jemalloc.sh
%exclude %{_bindir}/jeprof
%exclude %{_libdir}/pkgconfig/jemalloc.pc

%attr(644, -, -) %{_libdir}/libjemalloc_numbirch.a
%attr(644, -, -) %{_libdir}/libjemalloc_numbirch_pic.a

%changelog
* Tue Dec 5 2022 Lawrence Murray <lawrence@indii.org> - 1:0.0.0-1
Initial setup.
